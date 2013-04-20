
#include "Menu.h"
#include "tools.h"
#include <stdio.h>
#include <string.h>

int main()
{
    unsigned short const numMenuPoints = 7;
    int selection;
    char const * const title = "Terminverwaltung V 0.01";
    char const * menuPoints[numMenuPoints];
    menuPoints[0] = "Neuen Termin anlegen";
    menuPoints[1] = "Termin bearbeiten";
    menuPoints[2] = "Termin loeschen";
    menuPoints[3] = "Termin suchen";
    menuPoints[4] = "Termine sortieren";
    menuPoints[5] = "Termin auflisten";
    menuPoints[6] = "Programm beenden";

    do
    {
        selection = Menu(title, menuPoints, numMenuPoints);

        switch(selection)
        {
            case 1: printf("createAppointment");            break;
            case 2: printf("editAppointment");              break;
            case 3: printf("deleteAppointment");            break;
            case 4: printf("searchAppointment");            break;
            case 5: printf("sortAppointments");             break;
            case 6: printf("listAppointments");             break;
            case 7: printf("Das Programm wird beendet");    break;
        }

        printf("\n\n");
        waitForEnter();

    } while(selection != 7);



    //printf("\nDu hast \"%s\" ausgewaehlt.", menuPoints[selection-1]);

    return 0;
}
