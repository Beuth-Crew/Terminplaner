
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

// Globale Variablen (pfui)
unsigned short AppointmentCount = 0;
TAppointment Calendar[MAX_APPOINTMENTS];

void createAppointment()
{
    TAppointment TmpAppointment;                                            // local Appointment to work with

    char const *Title                = "Erfassung eines neuen Termins";     // Arrays used for prompts
    char const *DatePrompt           = "Datum         :";
    char const *TimePrompt           = "Uhrzeit       :";
    char const *DescriptionPrompt    = "Beschreibung  :";
    char const *LocationPrompt       = "Ort           :";
    char const *DurationPrompt       = "Dauer         :";

    int j = 0;


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

    while(j != 1)
    {
        switch(getText(DescriptionPrompt, 100, &TmpAppointment.description))
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
    }

    j = 0;


// read in location

    while(j != 1)
    {
        switch(getText(LocationPrompt, 15, &TmpAppointment.location))
        {
            case 0:
                j = 0;
                printf("Ungueltige Eingabe.");
                break;

            case 1: j = askPolarQuestion("Sie haben keineb Ort eingegeben.\nMoechten Sie dieses Feld frei lassen(Ja) oder die Eingabe wiederholen(Nein)?");
                break;

            // case 3: j = 0;  printf("Ihre Eingabe ist zu lang.\nBitte beschraenken Sie sich auf 15 Zeichen.");
            //    break;

            default:
                assert(0);
        }
    }


// read in duration

    while(getTime(DurationPrompt, &TmpAppointment.duration) == 0)
    {
        printf("Die Dauer konnte nicht interpretiert werden.\nBitte versuchen Sie es noch einmal.\n");
    }



// hand over tempAppointment to Calendar-Array

    Calendar[AppointmentCount] = TmpAppointment;


// increase the AppointmentCount by one

    ++AppointmentCount;

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
	++AppointmentCount;
	printf("Termin geloescht\n\n");
    waitForEnter();
}



void searchAppointment()
{
    printf("searchAppointment()\n\n");
    waitForEnter();
}



void sortCalendar()
{
    int MenuSelection;
    char const * const MenuTitle = "Sortieren  Ver. 0.0.1";

    unsigned short const nOfMenuPoints = 9;
    char const * MenuOptions[nOfMenuPoints];
    MenuOptions[0] = "Kalender aufwaerts nach Datum und Uhrzeit sortieren";
    MenuOptions[1] = "Kalender abwaerts nach Datum und Uhrzeit sortieren";
    MenuOptions[2] = "Kalender aufwaerts nach Beschreibung, Datum und Uhrzeit sortieren";
    MenuOptions[3] = "Kalender abwaerts nach Beschreibung, Datum und Uhrzeit sortieren";
    MenuOptions[4] = "Kalender aufwaerts nach Ort, Datum und Uhrzeit sortieren";
    MenuOptions[5] = "Kalender abwaerts nach Ort, Datum und Uhrzeit sortieren";
    MenuOptions[6] = "Kalender aufwaerts nach Dauer, Datum und Uhrzeit sortieren";
    MenuOptions[7] = "Kalender abwaerts nach Dauer, Datum und Uhrzeit sortieren";
    MenuOptions[8] = "zurueck zum Hauptmenue";


    // Ausgabe des Sortiermenus

    do
    {
        MenuSelection = menu(MenuTitle, MenuOptions, nOfMenuPoints);


        // Aufrufen der ausgewaehlten Funktion

        /*
        switch(MenuSelection)
        {
            case 1: createAppointment(Calendar, &AppointmentCount);                     break;
            case 2: editAppointment(Calendar, &AppointmentCount);                       break;
            case 3: deleteAppointment(Calendar, &AppointmentCount);                     break;
            case 4: searchAppointment(Calendar, AppointmentCount);                      break;
            case 5: sortCalendar(Calendar, AppointmentCount);                           break;
            case 6: listCalendar(Calendar, AppointmentCount);                           break;
            case 7: quitCalendar(Calendar, AppointmentCount);                           break;
            case 8:                                                                     break;

        }
         */

    } while(MenuSelection != 9);



    printf("sortCalendar()\n\n");
    waitForEnter();
}


void listCalendar()

{
    unsigned short i;
    char const * Headline = "Liste der Termine";
    int DoPrintDate;

// Ausgabe der Ueberschrift
    if(AppointmentCount)
    {
        printf("%s", Headline);
        printf("\n");
        printLine('=', strlen(Headline));
        printf("\n");
    }else
    {
        printf("Es wurden noch keine Termine angelegt.");
    }

// Ueberpruefung ob der letzde Termin am gleichen Tag ist wie der aktuelle Termin
// und setzt die Uebergabevariable fuer printAppointment: 0 ^= Datum nicht ausgeben

    for(i = 0; i < AppointmentCount; i++)
    {
        if(i)
        {
            if(compareIntegers(Calendar[i-1].date->day, Calendar[i].date->day) == 0)
            {
                if(compareIntegers(Calendar[i-1].date->month, Calendar[i].date->month) == 0)
                {
                    if(compareIntegers(Calendar[i-1].date->year, Calendar[i].date->year) == 0)
                    {
                        DoPrintDate = 0;
                    }else
                    {
                        DoPrintDate = 1;
                    }
                }else
                {
                    DoPrintDate = 1;
                }
            }else
            {
                DoPrintDate = 1;
            }
        }else
        {
            DoPrintDate = 1;
        }

        if(DoPrintDate) printf("------------------------------------------------------------------------------------\n");

        printAppointment(Calendar[i], DoPrintDate);


    }

    printf("------------------------------------------------------------------------------------\n");

    waitForEnter();
}


void freeAppointment(TAppointment *appointment)
{
    SAFE_FREE(appointment->time);
    SAFE_FREE(appointment->description);
    SAFE_FREE(appointment->date);
    SAFE_FREE(appointment->duration);
    SAFE_FREE(appointment->location);
}


void freeCalendar()
{
    unsigned short i;
    for (i = 0; i < AppointmentCount; ++i)
        freeAppointment(Calendar + i);
}
