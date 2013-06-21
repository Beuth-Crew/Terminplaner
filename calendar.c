
#include "calendar.h"
#include "tools.h"
#include "datastructure.h"
#include "dateutils.h"
#include "tools.h"
#include "files.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "sort.h"

// Globale Variablen (pfui)
unsigned short AppointmentCount = 0;
TAppointment Calendar[MAX_APPOINTMENTS];

// todo
// Funktionen anpassen
// (neuen Termin eingeben, Terminliste ausgeben und bei Programmende wieder alle Termine löschen)


void addAppToCalendar(TAppointment *const app)
{
    TAppointment *newApp = Calendar + AppointmentCount;

    assert(app);
    assert(app->date);
    assert(app->description);

    newApp->date        = app->date;
    newApp->description = app->description;

    if (app->duration != NULL) newApp->duration    = app->duration;
    if (app->location != NULL) newApp->location    = app->location;
    if (app->time != NULL)     newApp->time        = app->time;

    ++AppointmentCount;

    // Kalender neu sortieren mit dem neuen Element
    switch (sortierung)
    {
        case Sort_DateTime:
            quickSortCalendar(cmpApps_DateTime);
            break;

        case Sort_DescDateTime:
            quickSortCalendar(cmpApps_DescDateTime);
            break;

        case Sort_DurDateTime:
            quickSortCalendar(cmpApps_DurDateTime);
            break;

        case Sort_LocDateTime:
            quickSortCalendar(cmpApps_LocDateTime);
            break;

        case Sort_None:
            // Nichts sortieren
            break;

        default:
            assert(0);
    }
}

void createAppointment()
{
    TAppointment TmpAppointment;                                            // local Appointment to work with

    char const *Title                = "Erfassung eines neuen Termins";     // Arrays used for prompts
    char const *DatePrompt           = "Datum         :";
    char const *TimePrompt           = "Uhrzeit       :";
    char const *DescriptionPrompt    = "Beschreibung  :";
    char const *LocationPrompt       = "Ort           :";
    char const *DurationPrompt       = "Dauer         :";

    int j;


// prompt of title

    printf("%s", Title);
    printf("\n");
    printLine('=', strlen(Title));
    printf("\n");


// read in date

    while(getDate(DatePrompt, &TmpAppointment.date) == 0)
    {
        printf("Das Datum konnte nicht interpretiert werden.\nBitte versuchen Sie es noch einmal.\n");
    }


// read in time

    while(getTime(TimePrompt, &TmpAppointment.time) == 0)
    {
        printf("Die Uhrzeit konnte nicht interpretiert werden.\nBitte versuchen Sie es noch einmal.\n");
    }


// read in description

    do
    {
        j = getText(DescriptionPrompt, 100, &TmpAppointment.description, 0);
        /*
        switch(getText(DescriptionPrompt, 100, &TmpAppointment.description, 0))
        {
            case 0:
                j = 0;
                printf("Ungueltige Eingabe.");
                break;

            case 1:
                j = askPolarQuestion("Sie haben keine Beschreibung eingegeben.\nMoechten Sie dieses Feld frei lassen(Ja) oder die Eingabe wiederholen(Nein)?");
                break;

            // case 3:
                // j = 0;  printf("Ihre Eingabe ist zu lang.\nBitte beschraenken Sie sich auf 100 Zeichen.");
                // break;

            default:
                assert(0);
        }
        */
    } while(j != 1);


// read in location

    do
    {
        j = getText(LocationPrompt, 15, &TmpAppointment.location, 1);
        /*
        switch(getText(LocationPrompt, 15, &TmpAppointment.location, 1))
        {
            case 0:
                j = 0;
                printf("Ungueltige Eingabe.");
                break;

            case 1:
                j = 1;
                break;

            // case 3: j = 0;  printf("Ihre Eingabe ist zu lang.\nBitte beschraenken Sie sich auf 15 Zeichen.");
            //    break;

            default:
                assert(0);
        }
        */
    } while(j != 1);


// read in duration

    while(getTime(DurationPrompt, &TmpAppointment.duration) == 0)
    {
        printf("Die Dauer konnte nicht interpretiert werden.\nBitte versuchen Sie es noch einmal.\n");
    }



// hand over tempAppointment to Calendar-Array

    addAppToCalendar(&TmpAppointment);

    printf("\nTermin wurde gespeichert!");

    waitForEnter();
}


void editAppointment()
{
    printf("editAppointment()\n\n");
    waitForEnter();
}



void deleteAppointment()
{
	//--AppointmentCount;
	printf("deleteAppointment()\n\n");
    waitForEnter();
}


void searchAppointment()
{
    printf("searchAppointment()\n\n");
    waitForEnter();
}


void sortCalendar()
{
    int selection;
    char const * const title = "Sortieren  Ver. 0.0.1";
    unsigned short weiter = 1;

    unsigned short const numOptions = 5;
    char const * options[numOptions];
    options[0] = "Nach Datum und Uhrzeit sortieren";
    options[1] = "Nach Dauer, Datum und Uhrzeit sortieren";
    options[2] = "Nach Beschreibung, Datum und Uhrzeit sortieren";
    options[3] = "Nach Ort, Datum und Uhrzeit sortieren";
    options[4] = "Zurueck zum Hauptmenue";

    do
    {
        selection = menu(title, options, numOptions);

        // Aufrufen der ausgewaehlten Funktion
        switch (selection)
        {
            case 1:
                quickSortCalendar(cmpApps_DateTime);
                weiter = 0;
                break;

            case 2:
                quickSortCalendar(cmpApps_DurDateTime);
                weiter = 0;
                break;

            case 3:
                quickSortCalendar(cmpApps_DescDateTime);
                weiter = 0;
                break;

            case 4:
                quickSortCalendar(cmpApps_LocDateTime);
                weiter = 0;
                break;

            case 5:
                return; // Nichts sortieren

            default:
                printf("Ungueltige Auswahl.\n");
        }
    } while (weiter != 0);

    waitForEnter();
}


void listCalendar()
{
    unsigned short const lineLen = 79; // Länge einer Zeile, bestimmt Strichlänge
    char const *headline = "Termine";
    unsigned short ugApp; // Untergrenze einer Gruppe von Terminen. ugApp ist ein Index im Calendar-Array.
    unsigned short curApp; // Index, bei welchem Termin wir gerade sind. Für Iteration
    unsigned short numAppsPrinted = 0; // Wird zum Zählen verwendet. Nach je 15 Terminen wird waitForEnter() aufgerufen.
    unsigned short dateLen; // Zeichenlänge des ausgegebenen Datums, wird benötigt, um die Linie unter dem Datum genauso lang zu machen.

    clearScreen();
    printf("%s\n", headline);
    printLine('=', strlen(headline));

    switch (sortierung)
    {
        case Sort_DateTime:
            printf("Sortiert nach Datum -> Uhrzeit\n");
            break;

        case Sort_DurDateTime:
            printf("Sortiert nach Dauer -> Datum -> Uhrzeit\n");
            break;

        case Sort_LocDateTime:
            printf("Sortiert nach Ort -> Datum -> Uhrzeit\n");
            break;

        case Sort_DescDateTime:
            printf("Sortiert nach Beschreibung -> Datum -> Uhrzeit\n");
            break;

        case Sort_None:
            // Nichts ausgeben
            break;

        default:
            assert(0);
    }

    curApp = ugApp = 0; // Wir fangen beim 0. Element an.
    while (ugApp < AppointmentCount)
    {
        // Ausgabe des Datums
        printf("\n");
        printLine('-', lineLen); // Diese Zeile trennt die einzelnen Daten voneinander

        dateLen = printDate((Calendar + ugApp)->date);
        printLine('-', dateLen); // Unterstreichung für das Datum

        // Daten ausgeben, die zur Datumsgruppe gehören (bei 15 wird gestoppt)
        while (curApp < AppointmentCount)
        {
            // Wurden bereits 15 Termine ausgegeben?
            if (numAppsPrinted >= 15)
            {
                numAppsPrinted = 0; // Auf 0 zurücksetzen, damit der Zähler wieder bis 15 gehen kann.
                waitForEnter();
                break; // Die Gruppierung wird hiermit beendet.
            }

            if ( cmpDates((Calendar + ugApp)->date, (Calendar + curApp)->date) != 0 )
                break; // Daten sind nicht gleich

            // Termin ausgeben
            printf("   "); // Einrückung
            printAppointment(Calendar + curApp);

            ++numAppsPrinted;
            ++curApp;
        }

        ugApp = curApp;
    }

    printLine('-', lineLen);
    waitForEnter();
}


void freeAppointment(TAppointment *appointment)
{
    SAFE_FREE(appointment->date);
    SAFE_FREE(appointment->time);
    SAFE_FREE(appointment->description);
    SAFE_FREE(appointment->duration);
    SAFE_FREE(appointment->location);
}


void freeCalendar()
{
    unsigned short i;
    for (i = 0; i < AppointmentCount; ++i)
        freeAppointment(Calendar + i);
}
