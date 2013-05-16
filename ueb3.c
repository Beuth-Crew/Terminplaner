
#include "Menu.h"
#include "tools.h"
#include "calendar.h"
#include "dateutils.h"
#include <stdio.h>
#include <string.h>

int main()
{
    int selection;
    char const * const title = "Terminverwaltung V 0.03";

    unsigned short const numMenuPoints = 7;
    char const * menuPoints[numMenuPoints];
    menuPoints[0] = "Neuen Termin anlegen";
    menuPoints[1] = "Termin bearbeiten";
    menuPoints[2] = "Termin loeschen";
    menuPoints[3] = "Termin suchen";
    menuPoints[4] = "Termine sortieren";
    menuPoints[5] = "Termine auflisten";
    menuPoints[6] = "Programm beenden";

    do
    {
        selection = Menu(title, menuPoints, numMenuPoints);

        switch(selection)
        {
            case 1: createAppointment();                    break;
            case 2: editAppointment();                      break;
            case 3: deleteAppointment();                    break;
            case 4: searchAppointment();                    break;
            case 5: sortCalendar();                         break;
            case 6: listCalendar();                         break;
            case 7: printf("Das Programm wird beendet");    break;
            case 8: getTime("Yo, test123");                 break;
            case 9: getDate("Svens getDate")
        }

    } while(selection != 7);

    return 0;
}
