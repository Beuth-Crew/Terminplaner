
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
    char const Title = "Erfassung eines neuen Termins";
    char const DatePrompt           = "Datum         :";
    char const TimePrompt           = "Uhrzeit       :";
    char const DescriptionPrompt    = "Beschreibung  :";
    char const LocationPrompt       = "Ort           :";
    char const DurationPrompt       = "Dauer         :";


    printLine('=', strlen(Title));
    printf("\n");


    getDate(&DatePrompt, TDate **date);

    getTime(&TimePrompt, TTime **time);

    getText(&DescriptionPrompt, 50, char **str);

    getText(&LocationPrompt, 50, char **str);

    getTime(&DurationPrompt, TTime **duration);

    printf("Termin wurde gespeichert!")
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
