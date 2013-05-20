
#include "calendar.h"
#include "tools.h"
#include "datastructure.h"
#include "dateutils.h"
#include "tools.h"
#include "files.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Globale Variablen (pfui)
unsigned short AppointmentCount = 0;
TAppointment Calendar[MAX_APPOINTMENTS];

void createAppointment()
{
    TAppointment TmpAppointment;

    char const *Title = "Erfassung eines neuen Termins";
    char const *DatePrompt           = "Datum         :";
    char const *TimePrompt           = "Uhrzeit       :";
    char const *DescriptionPrompt    = "Beschreibung  :";
    char const *LocationPrompt       = "Ort           :";
    char const *DurationPrompt       = "Dauer         :";

    int j = 0;

// Ausgabe der Ueberschrift

    printf(Title);
    printf("\n");
    printLine('=', strlen(Title));
    printf("\n");

// Einlesen des Datums

    while(getDate(DatePrompt, &TmpAppointment.date) == 0)
    {
        printf("Das Datum konnte nicht interpretiert werden.\nBitte versuchen Sie es noch einmal.\n");
    }


// Einlesen der Zeit

    while(getTime(TimePrompt, &TmpAppointment.time) == 0)
    {
        printf("Die Uhrzeit konnte nicht interpretiert werden.\nBitte versuchen Sie es noch einmal.\n");
    }


// Einlesen der Beschreibung

    while(j != 1)
    {
        switch(getText(DescriptionPrompt, 100, &TmpAppointment.description))
        {
            case 1: j = 1;                                                                                                                                          break;
            case 2: j = askPolarQuestion("Sie haben keine Beschreibung eingegeben.\nMöchten Sie dieses Feld frei lassen(Ja) oder die Eingabe wiederholen(Nein)?");   break;
            case 3: j = 0;  printf("Ihre Eingabe ist zu lang.\nBitte beschraenken Sie sich auf 100 Zeichen.");                                                       break;
        }
    }

    j = 0;

// Einlesen des Orts

    while(j != 1)
    {
        switch(getText(LocationPrompt, 15, &TmpAppointment.location))
        {
            case 1: j = 1;                                                                                                                                          break;
            case 2: j = askPolarQuestion("Sie haben keineb Ort eingegeben.\nMöchten Sie dieses Feld frei lassen(Ja) oder die Eingabe wiederholen(Nein)?");           break;
            case 3: j = 0;  printf("Ihre Eingabe ist zu lang.\nBitte beschraenken Sie sich auf 15 Zeichen.");                                                        break;
        }
    }

// Einlesen der Dauer

    while(getTime(DurationPrompt, &TmpAppointment.time) == 0)
    {
        printf("Die Dauer konnte nicht interpretiert werden.\nBitte versuchen Sie es noch einmal.\n");
    }

//Uebergabe des erstellten Termins an den Calendar-String

    Calendar[AppointmentCount] = TmpAppointment;
    AppointmentCount++;

    printf("Termin wurde gespeichert!");

    waitForEnter();
}

void editAppointment()
{
    printf("editAppointment()\n\n");
    waitForEnter();
}

void deleteAppointment()
{
    printf("deleteAppointment()\n\n");

	-- AppointmentCount;

    waitForEnter();
}

void searchAppointment()
{
    printf("searchAppointment()\n\n");
    waitForEnter();
}

void sortCalendar()
{
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
        printf(Headline);
        printf("\n");
        printLine('=', strlen(Headline));
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


        printAppointment(Calendar[i], DoPrintDate);

    }

    waitForEnter();
}

void freeAppointment(TAppointment *appointment)
{
    free(appointment->time);
    free(appointment->description);
    free(appointment->date);
    free(appointment->duration);
    free(appointment->location);
}

void quitCalendar()
{
    saveCalendar(Calendar, AppointmentCount);
    printf("Das Programm wird beendet");
}
