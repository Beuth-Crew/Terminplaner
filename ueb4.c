
#include "calendar.h"
#include "files.h"
#include "tools.h"
#include "menu.h"
#include "animation.h"
#include <stdio.h>
#include <assert.h>

int main()
{
    char const *dbFile = "calendar.txt";
    unsigned short i; // Zählvariable
    int selection; // Menüauswahl
    char const * const title = "Terminverwaltung V 0.02";

    unsigned short const numMenuPoints = 7;
    char const * menuPoints[numMenuPoints];
    menuPoints[0] = "Neuen Termin anlegen";
    menuPoints[1] = "Termin bearbeiten";
    menuPoints[2] = "Termin loeschen";
    menuPoints[3] = "Termin suchen";
    menuPoints[4] = "Termine sortieren";
    menuPoints[5] = "Termine auflisten";
    menuPoints[6] = "Programm beenden";

    // Kalender mit 0-Werten füllen
    for (i = 0; i < MAX_APPOINTMENTS; ++i)
    {
        Calendar[i].date = NULL;
        Calendar[i].time = NULL;
        Calendar[i].description = NULL;
        Calendar[i].duration = 0;
        Calendar[i].location = NULL;
    }

    // Termine aus DB laden
    if (loadCalendar(dbFile) == 0)
    {
        printf("Fehler: Die vorhandenen Termine konnten nicht aus der Datenbank geholt werden.\n");
        waitForEnter();
    }

    do
    {
        selection = Menu(title, menuPoints, numMenuPoints);

        switch(selection)
        {
            case 1: createAppointment();                            break;
            case 2: editAppointment();                              break;
            case 3: deleteAppointment();                            break;
            case 4: searchAppointment();                            break;
            case 5: sortCalendar();                                 break;
            case 6: listCalendar();                                 break;
            case 7: animi_out("Das Programm wird beendet", 30);     break;
        }

    } while(selection != 7);

    // Termine speichern
    // todo remove
    switch (saveCalendar("calendar.txt"))
    //switch (saveCalendar(dbFile))
    {
        case 0: // Speichern erfolgreich!
            break;

        case 1: // Datei nicht gespeichert.
            printf("Fehler: Die Termine konnten nicht gespeichert werden.\n");
            waitForEnter();
            break;

        case 2: // Bei der Speicherung sind Probleme aufgetreten.
            printf("Warnung: Die Termine wurden möglicherweise nicht richtig gespeichert.\n");
            waitForEnter();

        default:
            assert(0); // Das darf nicht passieren
    }

    // Speicher freigeben
    for (i = 0; i < AppointmentCount; ++i)
        freeAppointment(Calendar + i);

    return 0;
}
