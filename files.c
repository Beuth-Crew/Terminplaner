
#include "files.h"
#include "calendar.h"
#include "dateutils.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

static unsigned short const maxLen = 255; // Maximale erlaubte Länge für einen XML-Bezeichner.

/*
    Gibt 1 zurück, falls der String geschrieben werden konnte,
    andernfalls 0.
*/
static int fwriteStr(FILE *handle, char const *str)
{
    int ret = fprintf(handle, str); // String schreiben.
    return ret == strlen(str); // Prüfen, ob der String vollständig geschrieben werden konnte.
}

static int saveAppointment(FILE *handle, TAppointment const *appointment)
{
    char tmpStr[100]; // for strings to be written to file
    int ret = 1; // Return value of this function, is set to 0 if error occurs

    // Diese Werte dürfen nicht auftreten
    assert(appointment);
    assert(appointment->date);
    assert(appointment->date->day);
    assert(appointment->date->month);
    assert(appointment->date->year);
    assert(appointment->description);
    assert(strcmp(appointment->description, "") != 0);

    // Start-Tag schreiben
    if (fwriteStr(handle, "\t<Appointment>\n") == 0)
        return 0; // Dieser Fehler ist

    // Datum ist ein MUSS-Wert und wird immer gespeichert
    sprintf(tmpStr, "\t\t<Date>%02hu.%02hu.%04hu</Date>\n",
                    appointment->date->day,
                    appointment->date->month,
                    appointment->date->year);
    if (fwriteStr(handle, tmpStr) != 0)
    {
        // Beschreibung wird immer gespeichert, denn das ist ein MUSS-Wert
        sprintf(tmpStr, "\t\t<Description>%s</Description>\n", appointment->description);
        if (fwriteStr(handle, tmpStr) != 0)
        {
            // Zeit nur speichern, wenn auch was zum speichern da ist
            if (appointment->time != NULL)
            {
                sprintf(tmpStr, "\t\t<Time>%02hu:%02hu</Time>\n",
                                appointment->time->hour,
                                appointment->time->minute);
                if (fwriteStr(handle, tmpStr) == 0)
                    ret = 0;
            }

            // Dauer nur speichern, wenn auch was zum speichern da ist
            if (appointment->duration != NULL)
            {
                sprintf(tmpStr, "\t\t<Duration>%02hu:%02hu</Duration>\n",
                                appointment->duration->hour,
                                appointment->duration->minute);
                if (fwriteStr(handle, tmpStr) == 0)
                    ret = 0;
            }

            // Ort nur speichern, wenn auch was zum speichern da ist
            if (appointment->location != NULL && strcmp(appointment->location, "") != 0)
            {
                sprintf(tmpStr, "\t\t<Location>%s</Location>\n", appointment->location);
                if (fwriteStr(handle, tmpStr) == 0)
                    ret = 0;
            }
        }
        else
            ret = 0;
    }
    else
    {
        ret = 0;
    }

    // End-Tag schreiben
    if (fwriteStr(handle, "\t</Appointment>\n") == 0)
        return 0;

    return ret; // ret ist 0, wenn ein Fehler aufgetreten ist
}

int saveCalendar(char const * filename)
{
    char tmpStr[100]; // for strings to be written to file
    FILE *handle;
    unsigned short i; // Zählvariable
    unsigned short fehler; // 0 - kein Fehler, 1 - Nicht alle Termine gespeichert

    handle = fopen(filename, "wt");
    if (handle != NULL)
    {
        if (fwriteStr(handle, "<Calendar>\n") == 0)
        {
            fclose(handle);
            remove(filename); // Datei ist fehlerhaft -> löschen
            return 1;
        }

        sprintf(tmpStr, "\t<AppointmentCount>%hu</AppointmentCount>\n", AppointmentCount);
        if (fwriteStr(handle, tmpStr) == 0)
        {
            fclose(handle);
            remove(filename); // Datei ist fehlerhaft -> löschen
            return 1;
        }

        // Termine speichern
        for (i = 0; i < AppointmentCount; ++i)
        {
            if (saveAppointment(handle, Calendar + i) == 0)
                fehler = 1;
        }

        if (fwriteStr(handle, "</Calendar>\n") == 0)
        {
            fclose(handle);
            remove(filename);
            return 1;
        }
    }
    else
        return 1;

    fclose(handle);

    if (fehler == 1)
        return 2; // Nicht alle Termine konnten gespeichert werden
    else
        return 0; // Kalender erfolgreich gespeichert
}

/*
  Liest einen Bezeichner aus einer XML-Datei ein.
  Hinweise: Die Cursor-Position des File-Handles muss genau vor Bezeichner sein.
            Leerzeichen am Anfang werden ignoriert.
            Jedes Zeichen, das kein Buchstabe oder Unterstrich ist, beendet den Bezeichner.
  Parameter:
    handle - Datei-Handle
    str - Enthält nach Funktionsaufruf den Bezeichner
    maxLen - maximale Länge des einzulesenden Bezeichners
  Returns 1 on success
          0 on failure
*/
int readIdentifier(FILE *handle, char *str)
{
    int result;
    char format[70];

    sprintf(format, " %%%hu[abcdefghijklmnopqrstuvwxyzABCDEFGHIFJKLMNOPQRSTUVWXYZ_]", maxLen);
    result = fscanf(handle, format, str);
    if (feof(handle) != 0 || ferror(handle) != 0 || result != 1)
        return 0;
    else
        return 1;

    assert(0); // Sollte nicht erreicht werden.
    return 0;
}

/*
  Hinweise:
    Die Cursor-Position im File-Handle muss genau hinter einem öffnenden <Appointment>-Tag liegen.

  Mögliche Ursachen, wenn die Funktion fehlschlägt:
    Lesefehler in der Datei,
    fehlerhaftes XML,
    Beschreibung oder Ort länger als 255 Zeichen,
    Heap-Speicher voll

  Parameter:
    handle - Datei, welche ausgelesen werden soll.
    appointment - enthält bei Erfolg

  Returns:
    0 on failure
    1 on success
*/
static int loadAppointment(FILE *handle, TAppointment *appointment)
{
    char str[maxLen + 1]; // Zum Einlesen variabler Werte
    char c; // Zum Einlesen variabler Werte
    int result; // Zum Prüfen von eingelesenen Werten oder Seek-Aufrufen
    TAppointment app; // Lokaler Termin, damit der appointment-Parameter erstmal nicht angetastet werden muss, bevor der Termin komplett eingelesen wurde.
    unsigned short numDateTags = 0, numTimeTags = 0, numDescriptionTags = 0, numLocationTags = 0, numDurationTags = 0;
    char format[15]; // format für sprintf

    app.date = NULL;
    app.time = NULL;
    app.description = NULL;
    app.duration = 0;
    app.location = NULL;

    // Das Appointment-Tag abarbeiten
    do
    {
        // Das nächste Tag suchen
        result = fscanf(handle, " <");
        if (feof(handle) != 0 || ferror(handle) != 0)
        {
            freeAppointment(&app);
            return 0; // Fehler oder Ende der Datei. Beides nicht erlaubt.
        }

        // Das Zeichen nach dem '<' einlesen
        result = fscanf(handle, " %c", &c);
        if (ferror(handle) != 0 || feof(handle) != 0 || result != 1)
        {
            freeAppointment(&app);
            return 0; // Fehler oder Ende der Datei. Beides nicht erlaubt.
        }

        // Wenn ein Slash folgt, muss es das schließende Appointment-Tag sein.
        if (c == '/')
        {
            result = fscanf(handle, " Appointment >");
            if (feof(handle) != 0 || ferror(handle) != 0)
            {
                freeAppointment(&app);
                return 0; // Fehler oder Ende der Datei. Beides nicht erlaubt.
            }

            // Es ist das schließende Appointment-Tag. Schleife verlassen.
            break;
        }
        else
        {
            // Ein Zeichen zurückspringen.
            result = fseek(handle, -1, SEEK_CUR);
            if (result == 0)
            {
                // Den Namen des Tags einnlesen. Dieser besteht aus Buchstaben und dem Unterstrich
                // und wird durch andere Zeichen beendet.
                result = readIdentifier(handle, str);
                if (result != 1)
                {
                    freeAppointment(&app);
                    return 0; // Fehler oder Ende der Datei. Beides nicht erlaubt.
                }

                // Das Tag-schließende Zeichen einlesen.
                result = fscanf(handle, " >");
                if (feof(handle) != 0 || ferror(handle) != 0)
                {
                    freeAppointment(&app);
                    return 0; // Fehler oder Ende der Datei. Beides nicht erlaubt.
                }

                // Prüfen, welches Tag es ist
                if (strcmp(str, "Date") == 0)
                {
                    if (numDateTags == 0)
                    {
                        ++numDateTags;
                        app.date = malloc(sizeof(TDate));
                        if (app.date != NULL)
                        {
                            result = fscanf(handle, " %2hu.%2hu.%4hu", &(app.date->day), &(app.date->month), &(app.date->year));
                            if (ferror(handle) != 0 || feof(handle) != 0 || result != 3)
                            {
                                freeAppointment(&app);
                                return 0; // Fehler oder Ende der Datei. Beides nicht erlaubt.
                            }

                            // Das einzige erlaubte Tag ist hier </Date>
                            result = fscanf(handle, " < / Date >");
                            if (feof(handle) != 0 || ferror(handle) != 0)
                            {
                                freeAppointment(&app);
                                return 0; // Fehler oder Ende der Datei. Beides nicht erlaubt.
                            }
                        }
                        else
                        {
                            freeAppointment(&app);
                            return 0; // Speicher konnte nicht reserviert werden
                        }
                    }
                    else
                    {
                        freeAppointment(&app);
                        return 0; // Tag darf nur einmal vorkommen
                    }
                }
                else if (strcmp(str, "Time") == 0)
                {
                    if (numTimeTags == 0)
                    {
                        ++numTimeTags;
                        app.time = malloc(sizeof(TTime));
                        if (app.time != NULL)
                        {
                            result = fscanf(handle, " %2hu:%2hu", &(app.time->hour), &(app.time->minute));
                            if (ferror(handle) != 0 || feof(handle) != 0 || result != 2)
                            {
                                freeAppointment(&app);
                                return 0; // Fehler oder Ende der Datei. Beides nicht erlaubt.
                            }

                            // Das einzige erlaubte Tag ist hier </Time>
                            result = fscanf(handle, " < / Time >");
                            if (feof(handle) != 0 || ferror(handle) != 0)
                            {
                                freeAppointment(&app);
                                return 0; // Fehler oder Ende der Datei. Beides nicht erlaubt.
                            }
                        }
                        else
                        {
                            freeAppointment(&app);
                            return 0;
                        }
                    }
                    else
                    {
                        freeAppointment(&app);
                        return 0; // Tag darf nur einmal vorkommen
                    }
                }
                else if (strcmp(str, "Location") == 0)
                {
                    if (numLocationTags == 0)
                    {
                        ++numLocationTags;

                        // Den Ort einlesen
                        sprintf(format, " %%%hu[^<\n]", maxLen);
                        result = fscanf(handle, format, str);
                        if (ferror(handle) != 0 || feof(handle) != 0 || result != 1)
                        {
                            freeAppointment(&app);
                            return 0; // Fehler oder Ende der Datei. Beides nicht erlaubt.
                        }

                        // Das einzige erlaubte Tag ist hier </Location>
                        result = fscanf(handle, " < / Location >");
                        if (feof(handle) != 0 || ferror(handle) != 0)
                        {
                            freeAppointment(&app);
                            return 0; // Fehler oder Ende der Datei. Beides nicht erlaubt.
                        }

                        app.location = calloc(strlen(str) + 1, sizeof(char));
                        if (app.time != NULL)
                            strcpy(app.location, str);
                        else
                        {
                            freeAppointment(&app);
                            return 0;
                        }
                    }
                    else
                    {
                        freeAppointment(&app);
                        return 0; // Tag darf nur einmal vorkommen
                    }
                }
                else if (strcmp(str, "Duration") == 0)
                {
                    if (numDurationTags == 0)
                    {
                        ++numDurationTags;
                        app.duration = malloc(sizeof(TTime));
                        if (app.duration != NULL)
                        {
                            result = fscanf(handle, " %2hu:%2hu", &(app.duration->hour), &(app.duration->minute));
                            if (ferror(handle) != 0 || feof(handle) != 0 || result != 2)
                            {
                                freeAppointment(&app);
                                return 0; // Fehler oder Ende der Datei. Beides nicht erlaubt.
                            }

                            // Das einzige erlaubte Tag ist hier </Time>
                            result = fscanf(handle, " < / Duration >");
                            if (feof(handle) != 0 || ferror(handle) != 0)
                            {
                                freeAppointment(&app);
                                return 0; // Fehler oder Ende der Datei. Beides nicht erlaubt.
                            }
                        }
                        else
                        {
                            freeAppointment(&app);
                            return 0;
                        }
                    }
                    else
                    {
                        freeAppointment(&app);
                        return 0; // Tag darf nur einmal vorkommen
                    }
                }
                else if (strcmp(str, "Description") == 0)
                {
                    if (numDescriptionTags == 0)
                    {
                        ++numDescriptionTags;

                        // Die Beschreibung einlesen
                        sprintf(format, " %%%hu[^<\n]", maxLen);
                        result = fscanf(handle, format, str);
                        if (ferror(handle) != 0 || feof(handle) != 0 || result != 1)
                        {
                            freeAppointment(&app);
                            return 0; // Fehler oder Ende der Datei. Beides nicht erlaubt.
                        }

                        // Das einzige erlaubte Tag ist hier </Description>
                        result = fscanf(handle, " < / Description >");
                        if (feof(handle) != 0 || ferror(handle) != 0)
                        {
                            freeAppointment(&app);
                            return 0; // Fehler oder Ende der Datei. Beides nicht erlaubt.
                        }

                        app.description = calloc(strlen(str) + 1, sizeof(char));
                        if (app.description != NULL)
                            strcpy(app.description, str);
                        else
                        {
                            freeAppointment(&app);
                            return 0;
                        }
                    }
                    else
                    {
                        freeAppointment(&app);
                        return 0; // Tag darf nur einmal vorkommen
                    }
                }
                else
                {
                    freeAppointment(&app);
                    return 0; // Es ist ein nicht erlaubtes Tag
                }
            }
            else
            {
                freeAppointment(&app);
                return 0; // Fehler bei fseek()
            }

        }
    } while (1); // Abgebrochen wird durch break

    // <Description> und <Date> müssen genau einmal vorkommen.
    if (numDescriptionTags == 1 && numDateTags == 1)
    {
        // Werte vom lokalen appointment in den übergebenen appointment-Parameter kopieren.
        if (isDateValid(app.date))
            appointment->date = app.date;
        else
        {
            freeAppointment(&app);
            return 0;
        }

        if (app.duration != NULL)
        {
            if (isTimeValid(app.duration))
                appointment->duration = app.duration;
            else
            {
                freeAppointment(&app);
                return 0;
            }
        }

        if (app.time != NULL)
        {
            if (isTimeValid(app.time))
                appointment->time = app.time;
            else
            {
                freeAppointment(&app);
                return 0;
            }
        }

        appointment->description = app.description;
        appointment->location = app.location;

        return 1; // Appointment richtig eingelesen.
    }
    else
    {
        freeAppointment(&app);
        return 0;
    }

    freeAppointment(&app);
    assert(0); // Sollte nie erreicht werden

    return 0; // Nur um den Compiler zu beruhigen
}

int loadCalendar(char const *filename)
{
    unsigned short i; // Zählvariable
    FILE *handle;
    int result; // Zum Prüfen von eingelesenen Werten oder Seek-Aufrufen
    short s; // Zum Einlesen variabler Werte
    short numAppointments; // Wird aus der XML-Datei gelesen
    TAppointment *appointments; // Appointments, lokal. Werden nach erfolgreichem Einlesen der Datei in das globale Calendar-Array kopiert. Speicher wird dynamisch alloziert.

    handle = fopen(filename, "rt");
    if (handle != NULL)
    {
        // Das erste Tag muss <Calendar> sein!
        fscanf(handle, " < Calendar >");
        if (feof(handle) != 0 || ferror(handle) != 0)
        {
            fclose(handle);
            return 0; // Fehler oder Ende der Datei. Beides nicht erlaubt.
        }

        // Nach <Calendar> kommt <AppointmentCount>
        result = fscanf(handle, " < AppointmentCount > %hd < / AppointmentCount >", &s);
        if (ferror(handle) != 0 || feof(handle) != 0 || result != 1)
        {
            fclose(handle);
            return 0;
        }

        // Wertebereich von AppointmentCount prüfen
        if (s >= 0)
        {
            numAppointments = s;

            appointments = calloc(numAppointments, sizeof(TAppointment));
            if (appointments != NULL)
            {
                // Termine einlesen
                for (i = 0; i < numAppointments; ++i)
                {
                    // Nun gucken, ob es ein Appointment-Tag ist (das einzige, was hier erlaubt ist).
                    result = fscanf(handle, " < Appointment >");
                    if (feof(handle) != 0 || ferror(handle) != 0)
                    {
                        fclose(handle);
                        free(appointments);
                        return 0; // Fehler oder Ende der Datei. Beides nicht erlaubt.
                    }

                    result = loadAppointment(handle, appointments + i);
                    if (result == 0)
                    {
                        fclose(handle);
                        free(appointments);
                        return 0; // Fehler beim Einlesen des Appointments
                    }
                } // for

                // Alle Appointments richtig eingelesen!
                // Jetzt folgt nur noch </Calendar>
                result = fscanf(handle, " < / Calendar >");
                if (feof(handle) != 0 || ferror(handle) != 0)
                {
                    fclose(handle);
                    free(appointments);
                    return 0; // Fehler oder Ende der Datei. Beides nicht erlaubt.
                }

                fclose(handle);

                // Datei ist in Ordnung!

                // Elemente der lokalen Termine in das globale Calendar-Array kopieren
                AppointmentCount = numAppointments;
                for (i = 0; i < AppointmentCount; ++i)
                {
                    (Calendar + i)->date        = (appointments + i)->date;
                    (Calendar + i)->description = (appointments + i)->description;
                    (Calendar + i)->duration    = (appointments + i)->duration;
                    (Calendar + i)->location    = (appointments + i)->location;
                    (Calendar + i)->time        = (appointments + i)->time;
                }

                free(appointments);

                // Termine wurden geladen.
                return 1;
            }
            else
            {
                // Speicher konnte nicht alloziert werden
                fclose(handle);
                return 0;
            }
        }
        else
        {
            // AppointmentCount ist < 0, das darf nicht sein!
            fclose(handle);
            return 0;
        }
    }
    else
        return 0; // Datei konnte nicht geöffnet werden.

    assert(0); // Dieser Punkt sollte nie erreicht werden.
    return 0;
}
