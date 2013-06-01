
#include "Menu.h"
#include "tools.h"
#include "calendar.h"
#include "dateutils.h"
#include "datastructure.h"
#include <stdio.h>
#include <string.h>


int main()
{

// Hauptmenu: Konstanten und Variablen
    
    int MenuSelection;
    char const * const MenuTitle = "Terminverwaltung  Ver. 0.4.3";

    unsigned short const nOfMenuPoints = 8;
    char const * MenuOptions[nOfMenuPoints];
    MenuOptions[0] = "Neuen Termin anlegen";
    MenuOptions[1] = "Termin bearbeiten";
    MenuOptions[2] = "Termin loeschen";
    MenuOptions[3] = "Termin suchen";
    MenuOptions[4] = "Termine sortieren";
    MenuOptions[5] = "Termine auflisten";
    MenuOptions[6] = "Programm beenden";
    MenuOptions[7] = "Programm beenden OHNE zu speichern";
    
    
// Array der die Termine haelt
    
    TAppointment Calendar[100];
    unsigned short AppointmentCount = 0;
    
    
// Initialisieren des Calender-Arrays mit NULL-Pointer
    
    int i;

    for(i = 0; i < 100; ++i)
    {
        Calendar[i].date = NULL;
        Calendar[i].time = NULL;
        Calendar[i].description = NULL;
        Calendar[i].location = NULL;
        Calendar[i].duration = NULL;
    }
    
    
// Einlesen des Calendar-Files
    
    readFilesAtStartup(Calendar, &AppointmentCount);

    
// Ausgabe des Hauptmenues
    
    do
    {
        MenuSelection = menu(MenuTitle, MenuOptions, nOfMenuPoints);

        
// Aufrufen der ausgewaehlten Funktion
        
        switch(MenuSelection)
        {
            case 1: createAppointment(Calendar, &AppointmentCount);                     break;
            case 2: editAppointment(Calendar, &AppointmentCount);                       break;
            case 3: deleteAppointment(Calendar, &AppointmentCount);                     break;
            case 4: searchAppointment(Calendar, AppointmentCount);                      break;
            case 5: sortCalendar(Calendar, AppointmentCount);                           break;
            case 6: listCalendar(Calendar, AppointmentCount);                           break;
            case 7: quitCalendar(Calendar, AppointmentCount);                           break;
            case 8:                                                                     break;
        }

    } while(MenuSelection != 7 && MenuSelection != 8);

// Programm Beenden
    
    return 0;
}
