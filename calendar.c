
#include "calendar.h"
#include "tools.h"
#include "datastructure.h"
#include <stdio.h>
#include <stdlib.h>

// Globale Variablen (pfui)
unsigned short AppointmentCount = 0;
TAppointment Calendar[MAX_APPOINTMENTS];

// todo implementieren
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

// todo implementieren
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

void freeCalendar()
{
    TAppointment *curApp;
    unsigned short i;
    for (i = 0, curApp = Calendar; i < AppointmentCount; ++i, ++curApp)
    {
        freeAppointment(curApp);
        curApp = NULL;
    }
}
