#include "tools.h"
#include "dateutils.h"
#include "datastructure.h"
#include "calendar.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


int isLeapYear(int year)
{

    if (year % 400 == 0)
        return 1;
    else if (year % 4 == 0 && year % 100 != 0)
        return 1;
    else
        return 0;

}


int isDateValid(TDate const *date)
{
    // Tag Untergrenze überprüfen
    if (date->day < 1)
        return 0;

    // Jahr überprüfen
    if (date->year < 1582)
        return 0; // Der Gregorianische Kalender geht erst ab dem Jahr 1582 los.

    // Monat überprüfen
    switch (date->month)
    {
        case 2:
        {
            if (isLeapYear(date->year) == 1)
            {
                if (date->day > 29)
                    return 0;
            }
            else
            {
                if (date->day > 28)
                    return 0;
            }

            break;
        }

        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
        {
            // Monate mit 31 Tagen
            if (date->day > 31)
                return 0;

            break;
        }

        case 4:
        case 6:
        case 9:
        case 11:
            // Monate mit 30 Tagen
            if (date->day > 30)
                return 0;

            break;

        default:
            return 0; // Ungültiger Monat
    }

    return 1;
}

int getDateFromString(char const *datum, TDate *date)
{
    char *cTag = NULL, *cMonat = NULL, *cJahr = NULL;                       // Tag, Monat, Jahr als Teilstring von datum
    TDate tmpDate;                                                          // Damit das übergebene Datum im Fehlerfall nicht verändert werden muss.
    unsigned short anzPunkte = 0;                                           // Es dürfen maximal zwei Punkte vorkommen
    char *locDate;                                                          // lokales Datum ( = datum-Parameter)
    char *p;                                                                // Iterator

    assert(date != NULL);
    assert(datum != NULL);

    // Datum kopieren, damit der datum-Parameter nicht verändert werden muss.
    locDate = calloc(strlen(datum) + 1, sizeof(char));
    if (locDate == NULL)
        return 0; // Speicher kann nicht reserviert werden.

    p = locDate;
    strcpy(locDate, datum);

    while (*p != '\0')
    {
        if (*p >= '0' && *p <= '9')
        {
            if (cTag == NULL)
                cTag = p;                                                   // Der Tag ist noch nicht gesetzt. Er kommt als erstes.
            else if (cMonat == NULL)
                cMonat = p;                                                 // Der Monat ist noch nicht gesetzt. Er kommt als zweites.
            else if (cJahr == NULL)
                cJahr = p;                                                  // Das Jahr ist noch nicht gesetzt. Es kommt als letztes.
            else
            {
                free(locDate);
                return 0;
            }

            while ((*(p + 1) >= '0' && *(p + 1) <= '9') && *(p + 1) != '\0')// Die Zahl bis zum Ende durchlaufen
                ++p;
        }
        else if (*p == '.')
        {
            ++anzPunkte;
            *p = '\0';                                                      // Punkte werden durch \0 ersetzt.
        }
        else
        {
            free(locDate);
            return 0;                                                       // Es ist ein ungŸltiges Zeichen enthalten.
        }

        ++p;
    }

    if (cTag == NULL || cMonat == NULL || cJahr == NULL)
    {
        free(locDate);
        return 0; // Tag, Monat und Jahr müssen im Datum enthalten sein.
    }

    if (anzPunkte != 2)
    {
        free(locDate);
        return 0; // Es müssen genau zwei Punkte vorkommen
    }

    // Die Typecast (int -> unsigned short) sollten immer funktionieren,
    // da für Tag, Monat und Jahr eh nur kleine positive Zahlen zulässig sind.
    tmpDate.day   = atoi(cTag);     if (errno != 0) return 0;
    tmpDate.month = atoi(cMonat);   if (errno != 0) return 0;
    tmpDate.year  = atoi(cJahr);    if (errno != 0) return 0;

    // Zur Sicherheit

    if (isDateValid(&tmpDate) == 0)
    {
        free(locDate);
        return 0;
    }

    assert(tmpDate.day <= 31);
    assert(tmpDate.month <= 12);

    date->day = tmpDate.day;
    date->month = tmpDate.month;
    date->year = tmpDate.year;
    date->dayOfWeek = calculateDayOfWeek(date);

    free(locDate);
    return 1;
}


DayOfWeek calculateDayOfWeek(TDate const *date)
{
    short korrektur; // Schaltjahreskorrektur, für die Berechnung des Wochentages
    unsigned short monatsziffer = 0; // Für die Berechnung des Wochentages

    assert(date); // Zur Sicherheit

    // http://de.wikipedia.org/wiki/Wochentagsberechnung
    switch (date->month)
    {
        case 1:
        case 10:
            monatsziffer = 0;
            break;

        case 5:
            monatsziffer = 1;
            break;

        case 8:
            monatsziffer = 2;
            break;

        case  2:
        case  3:
        case 11:
            monatsziffer = 3;
            break;

        case 6:
            monatsziffer = 4;
            break;

        case  9:
        case 12:
            monatsziffer = 5;
            break;

        case 4:
        case 7:
            monatsziffer = 6;
            break;

        default:
            assert(0); // Andere Werte dürfen hier nicht auftreten!
    }

    if (date->month <= 2 && isLeapYear(date->year))
        korrektur = -1;
    else
        korrektur = 0;

    return (
            (date->day % 7) // Tagesziffer
          + (monatsziffer) // Monatsziffer
          + ( ( (date->year % 100) + (date->year % 100 / 4) ) % 7 ) // Jahresziffer
          + ( ( 3 - ( (date->year / 100) % 4 ) ) * 2 ) // Jahrhundertziffer
          + (korrektur) // Schaltjahreskorrektur
           ) % 7;
}


int getTimeFromString(char const *UserInput, TTime *time)
{
    char* LocalTime;
    TTime tmpTime;
    char LocalHours[3];
    char LocalMinutes[3];

    assert(UserInput != NULL);
    assert(time != NULL);

    LocalTime = calloc(strlen(UserInput) + 1, sizeof(char));
    if (LocalTime == NULL)
        return 0; // Speicher kann nicht reserviert werden.

    strcpy(LocalTime, UserInput);

    LocalHours[0] = LocalTime[0];
    LocalHours[1] = LocalTime[1];
    LocalHours[2] = '\0';
    LocalMinutes[0] = LocalTime[3];
    LocalMinutes[1] = LocalTime[4];
    LocalMinutes[2] = '\0';

    free(LocalTime);

    if(LocalHours[0] >= '0' && LocalHours [0] <= '9' /*&& atoi(LocalHours) == 0*/)
    {
        tmpTime.hour = atoi(LocalHours);
        tmpTime.minute = atoi(LocalMinutes);

        if (isTimeValid(&tmpTime) == 1)
        {
            time->hour = tmpTime.hour;
            time->minute = tmpTime.minute;
            return 1;
        }
        else
            return 0;

        assert(0); // Sollte nie erreicht werden.
        return 1;
    }
    else
        return 0;

    assert(0); // Sollte nie erreicht werden.
    return 0;
}

int getDate(char const *aufforderung, TDate **date)
{
    char eingabe[12];
    int anzEingelesen; // Anzahl richtig eingelesener Werte
    TDate * tmpDate; // Damit das übergebene Datum im Fehlerfall nicht verändert wird.

    printf("\n%s", aufforderung);
    anzEingelesen = scanf("%11[^\n]", eingabe);
    clearBuffer();

    if (anzEingelesen == 1)
    {
        tmpDate = malloc(sizeof(TDate));

        if (getDateFromString(eingabe, tmpDate) == 1)
        {
            *date = malloc(sizeof(TDate));
            if (*date != NULL)
            {
                (*date)->day        = (*tmpDate).day;
                (*date)->month      = (*tmpDate).month;
                (*date)->year       = (*tmpDate).year;
                (*date)->dayOfWeek  = (*tmpDate).dayOfWeek;

                free(tmpDate);

                return 1; // Everything fine
            }
            else
                return 0; // Speicher konnte nicht reserviert werden.
        }
    }

    return 0;
}


int getTime(char const *Prompt, TTime **Time)
{
    char UserInput[7];
    int ReadSuccessfully;
    TTime tmpTime;

// Usereingabe

    printf("%s", Prompt);
    ReadSuccessfully = scanf("%6[^\n]", UserInput);
    clearBuffer();

// Parsen der Usereingabe in eine gueltige(!) Zeit

    if (ReadSuccessfully)
    {
        if (getTimeFromString(UserInput, &tmpTime) == 1)
        {
            *Time = malloc(sizeof(TTime));
            if (*Time)
            {
                (*Time)->hour = tmpTime.hour;
                (*Time)->minute = tmpTime.minute;
                return 1;
            }
            else
            {
                return 0; //Speicherplatz konnte nicht reserviert werden!
            }
        }
        else
        {
            return 0; // Keine gültige Zeit eingegeben
        }
    }
    else
        return 0; // Konnte nicht eingelesen werden

    assert(0); // sollte nie erreicht werden
    return 1;
}

char* weekDayToStr(char *str, unsigned short dayOfWeek, unsigned short shortForm)
{
    switch (dayOfWeek)
    {
        case So:
            strcpy(str, shortForm ? "So" : "Sonntag");
            break;

        case Mo:
            strcpy(str, shortForm ? "Mo" : "Montag");
            break;

        case Di:
            strcpy(str, shortForm ? "Di" : "Dienstag");
            break;

        case Mi:
            strcpy(str, shortForm ? "Mi" : "Mittwoch");
            break;

        case Do:
            strcpy(str, shortForm ? "Do" : "Donnerstag");
            break;

        case Fr:
            strcpy(str, shortForm ? "Fr" : "Freitag");
            break;

        case Sa:
            strcpy(str, shortForm ? "Sa" : "Samstag");
            break;

        default:
            assert(0); // Das darf nicht passieren!
    }

    return str;
}

void printTime(TTime const *time)
{
    assert(time);
    printf("%02hu:%02hu", time->hour, time->minute);
}

unsigned short printDate(TDate const *date)
{
    char weekStr[11];

    assert(date);

    return printf("%s, der %02hu.%02hu.%04hu:\n", weekDayToStr(weekStr, date->dayOfWeek, 0),
                  date->day,
                  date->month,
                  date->year);
}

void printAppointment(TAppointment const *app)
{
    TTime endTime; // Endzeitpunkt, wird errechnet mittels addTime(...)

    assert(app);
    assert(app->date);
    assert(app->description);

    if (app->time)
        printTime(app->time);
    else
        printf("     "); // Platzhalter

    printf(" - "); // optischer Trenner

    addTime(app->time, app->duration, &endTime);
    printTime(&endTime);

    printf(" -> "); // optischer Trenner

    if(app->location)
        printf("%-15s", app->location);
    else
        printf("               "); // Platzhalter

    printf(" | "); // optischer Trenner

    if(app->description)
    {
        printf("%-39s", app->description);
        if(strlen(app->description) > 39)
            printf("...");
    }

    printf("\n");
}

int isTimeValid(TTime const *time)
{
    assert(time);

    if(time->hour > 23 || time->minute > 60)
        return 0;

    return 1;
}


unsigned short addTime(TTime const *time1, TTime const *time2, TTime *result)
{
    assert(result);

    if (time1 == NULL)
    {
        if (time2 == NULL)
            result->hour = result->minute = 0;
        else
        {
            result->hour   = time2->hour;
            result->minute = time2->minute;
        }
    }
    else
    {
        if (time2 == NULL)
        {
            result->hour   = time1->hour;
            result->minute = time1->minute;
        }
        else
        {
            // Die beiden Zeiten zusammenrechnen
            result->minute = time1->minute + time2->minute;
            result->hour   = time1->hour   + time2->hour;
            if (result->minute > 59)
            {
                // Übertrag auf die Stunden
                ++result->hour;
                result->minute -= 60;
            }

            if (result->hour >= 24)
            {
                result->hour -= 24;
                return 1; // Ergebnis geht über 24h hinaus.
            }
        }
    }

    return 0; // Ergebnis hat die 24h-Grenze nicht überschritten.
}

void swapAppointments(TAppointment *a1, TAppointment *a2)
{
    TDate *tmpDate;
    TTime *tmpTime;
    char *tmpStr;

    assert(a1);
    assert(a2);

    tmpDate = a1->date;
    a1->date = a2->date;
    a2->date = tmpDate;

    tmpTime = a1->time;
    a1->time = a2->time;
    a2->time = tmpTime;

    tmpTime = a1->duration;
    a1->duration = a2->duration;
    a2->duration = tmpTime;

    tmpStr = a1->description;
    a1->description = a2->description;
    a2->description = tmpStr;

    tmpStr = a1->location;
    a1->location = a2->location;
    a2->location = tmpStr;
}

short cmpDates(TDate const *d1, TDate const *d2)
{
    short diffMonths;
    short diffYears;

    assert(d1);
    assert(d2);

    diffYears = d1->year - d2->year;
    if (diffYears == 0)
    {
        // Jahre sind gleich
        diffMonths = d1->month - d2->month;
        if (diffMonths == 0)
            return d1->day - d2->day; // Jahr und Monate sind gleich, vergleiche Tage.
        else
            return diffMonths; // Monate sind unterschiedlich
    }

    return diffYears; // Jahre sind unterschiedlich
}

short cmpTimes(TTime const *t1, TTime const *t2)
{
    short diffHours;

    if (t1 == NULL)
    {
        if (t2 == NULL)
            return 0;
        else
            return -t2->hour;
    }
    else
    {
        if (t2 == NULL)
            return t1->hour;
        else
            diffHours = t1->hour - t2->hour;
    }

    // An dieser Stelle sollte keiner der beiden TTime-Zeiger NULL sein.
    if (diffHours == 0)
        return t1->minute - t2->minute; // Stunden sind gleich, vergleiche Minuten.

    return diffHours; // Stunden sind unterschiedlich
}

short cmpApps_DateTime(TAppointment const *a1, TAppointment const *a2)
{
    short diffDates;

    assert(a1);
    assert(a2);

    diffDates = cmpDates(a1->date, a2->date);

    if (diffDates == 0)
        return cmpTimes(a1->time, a2->time); // Datum ist gleich, vergleiche Zeit

    return diffDates;
}

short cmpApps_DurDateTime(TAppointment const *a1, TAppointment const *a2)
{
    short diffDurations;

    assert(a1);
    assert(a2);

    diffDurations = cmpTimes(a1->duration, a2->duration);

    if (diffDurations == 0)
        return cmpApps_DateTime(a1, a2); // Dauer ist gleich, vergleiche Datum und Zeit

    return diffDurations;
}

short cmpApps_DescDateTime(TAppointment const *a1, TAppointment const *a2)
{
    short diffDescs;

    assert(a1);
    assert(a2);
    assert(a1->description);
    assert(a2->description);

    diffDescs = stricmp(a1->description, a2->description); // Vergleiche Beschreibungsn, case insensitive

    if (diffDescs == 0)
        return cmpApps_DateTime(a1, a2); // Beschreibungen sind gleich, vergleiche Datum und Zeit

    return diffDescs;
}

short cmpApps_LocDateTime(TAppointment const *a1, TAppointment const *a2)
{
    short diffLocations;

    assert(a1);
    assert(a2);

    if (a1->location == NULL)
    {
        if (a2->location == NULL)
            diffLocations = 0;
        else
            diffLocations = -(*(a2->location));
    }
    else
    {
        if (a2->location == NULL)
            diffLocations = *(a1->location);
        else
            diffLocations = stricmp(a1->location, a2->location); // Vergleiche Orte, case insensitive
    }

    if (diffLocations == 0)
        return cmpApps_DateTime(a1, a2); // Orte sind gleich, vergleiche Datum und Zeit

    return diffLocations;
}
