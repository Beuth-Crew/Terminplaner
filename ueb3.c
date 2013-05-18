
#include "Menu.h"
#include "tools.h"
#include "calendar.h"
#include "dateutils.h"
#include <stdio.h>
#include <string.h>

int main()
{
    int MenuSelection;
    char const * const MenuTitle = "Terminverwaltung V 0.03";

    unsigned short const nOfMenuPoints = 7;
    char const * MenuOptions[nOfMenuPoints];
    MenuOptions[0] = "Neuen Termin anlegen";
    MenuOptions[1] = "Termin bearbeiten";
    MenuOptions[2] = "Termin loeschen";
    MenuOptions[3] = "Termin suchen";
    MenuOptions[4] = "Termine sortieren";
    MenuOptions[5] = "Termine auflisten";
    MenuOptions[6] = "Programm beenden";

    do
    {
        MenuSelection = Menu(MenuTitle, MenuOptions, nOfMenuPoints);

        switch(MenuSelection)
        {
            case 1: createAppointment();                    break;
            case 2: editAppointment();                      break;
            case 3: deleteAppointment();                    break;
            case 4: searchAppointment();                    break;
            case 5: sortCalendar();                         break;
            case 6: listCalendar();                         break;
            case 7: printf("Das Programm wird beendet");    break;
        }

    } while(MenuSelection != 7);

    return 0;
}
