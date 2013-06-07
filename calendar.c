
#include "calendar.h"
#include "tools.h"
#include "datastructure.h"
#include <stdio.h>
#include <stdlib.h>

// Globale Variablen (pfui)
unsigned short AppointmentCount = 0;
TAppointment Calendar[MAX_APPOINTMENTS];

void createAppointment()
{
    printf("createAppointment()\n\n");
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
    SAFE_FREE(appointment->time);
    SAFE_FREE(appointment->description);
    SAFE_FREE(appointment->date);
    SAFE_FREE(appointment->duration);
    SAFE_FREE(appointment->location);
}
