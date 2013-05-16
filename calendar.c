
#include "calendar.h"
#include "tools.h"
#include "datastructure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Globale Variablen (pfui)
unsigned short AppointmentCount = 0;
TAppointment Calendar[MAX_APPOINTMENTS];

void createAppointment()
{
    TAppointment *tmpAppointment = NULL;
    TAppointment*Item = malloc(sizeof(TAppointment));
    TDate tmpDate;
    TTime tmpTime;
    TTime tmpDuration;
    
    char const Title = "Erfassung eines neuen Termins";
    char const DatePrompt           = "Datum         :";
    char const TimePrompt           = "Uhrzeit       :";
    char const DescriptionPrompt    = "Beschreibung  :";
    char const LocationPrompt       = "Ort           :";
    char const DurationPrompt       = "Dauer         :";


    printLine('=', strlen(&Title)); //& war nicht da
    printf("\n");


    getDate(&DatePrompt, tmpDate);

    getTime(&TimePrompt, tmpTime);

    getText(&DescriptionPrompt, 50, &tmpAppointment->description);

    getText(&LocationPrompt, 50, &tmpAppointment->location);

    getTime(&DurationPrompt, tmpDuration);

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
    printf("listCalendar()\n\n");
    waitForEnter();
}

void freeAppointment(TAppointment *appointment)
{
    free(appointment->time);
    free(appointment->description);
    free(appointment->date);
    free(appointment->duration);
    free(appointment->location);
    free(appointment);
}
