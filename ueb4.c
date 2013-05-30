
#include "Menu.h"
#include "tools.h"
#include "calendar.h"
#include "dateutils.h"
#include "datastructure.h"
#include <stdio.h>
#include <string.h>

int main()
{
    int MenuSelection;
    char const * const MenuTitle = "Terminverwaltung  Ver. 0.4.0";

    unsigned short const nOfMenuPoints = 7;
    char const * MenuOptions[nOfMenuPoints];
    MenuOptions[0] = "Neuen Termin anlegen";
    MenuOptions[1] = "Termin bearbeiten";
    MenuOptions[2] = "Termin loeschen";
    MenuOptions[3] = "Termin suchen";
    MenuOptions[4] = "Termine sortieren";
    MenuOptions[5] = "Termine auflisten";
    MenuOptions[6] = "Programm beenden";
    
    TAppointment Calendar[100];
    unsigned short AppointmentCount = 0;

// Einlesen des Calendar-Files

    readFilesAtStartup(Calendar, &AppointmentCount);

    do
    {
        MenuSelection = menu(MenuTitle, MenuOptions, nOfMenuPoints);

        switch(MenuSelection)
        {
            case 1: createAppointment(Calendar, &AppointmentCount);                     break;
            case 2: editAppointment(Calendar, &AppointmentCount);                       break;
            case 3: deleteAppointment(Calendar, &AppointmentCount);                     break;
            case 4: searchAppointment(Calendar, AppointmentCount);                      break;
            case 5: sortCalendar(Calendar, AppointmentCount);                           break;
            case 6: listCalendar(Calendar, AppointmentCount);                           break;
            case 7: quitCalendar(Calendar, AppointmentCount);                           break;
        }

    } while(MenuSelection != 7);

    return 0;
}
