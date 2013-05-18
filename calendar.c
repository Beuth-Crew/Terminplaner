
#include "calendar.h"
#include "tools.h"
#include "datastructure.h"
#include "dateutils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Globale Variablen (pfui)
unsigned short AppointmentCount = 0;
TAppointment Calendar[MAX_APPOINTMENTS];

void createAppointment()
{
    TAppointment tmpAppointment;

    char const *Title = "Erfassung eines neuen Termins";
    char const *DatePrompt           = "Datum         :";
    char const *TimePrompt           = "Uhrzeit       :";
    char const *DescriptionPrompt    = "Beschreibung  :";
    char const *LocationPrompt       = "Ort           :";
    char const *DurationPrompt       = "Dauer         :";

    printf(Title);
    printf("\n");
    printLine('=', strlen(Title)); //& war nicht da
    printf("\n");

// todo Schleife
    if (getDate(DatePrompt, &tmpAppointment.date) == 0)
        printf("Alter das Datum ist falsch! >:|");
//    tmpAppointment->date = tmpDate;
    do
    {
        getTime(TimePrompt, &tmpAppointment.time);
    }while(isTimeValid(tmpAppointment.time));
//    tmpAppointment->time = tmpTime;

    getText(DescriptionPrompt, 50, &tmpAppointment.description);

    getText(LocationPrompt, 50, &tmpAppointment.location);

    getTime(DurationPrompt, &tmpAppointment.time);


    Calendar[AppointmentCount] = tmpAppointment;                             //Uebergabe des erstellten Termins an den Calendar-String
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
    printLine('=', strlen(Headline));

    for(i = 0; i < AppointmentCount; i++)
    {
        printf("------------------------------------------------------------------------------------");
        printDate(Calendar[i].date);
        printf("------------------------------");
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
