#ifndef FILES_H_INCLUDED
#define FILES_H_INCLUDED

#include "datastructure.h"
#include <stdio.h>

/*
    Speichert die Elemente des Calendar-Arrays in der angegebenen XML-Datei.
    Die Datei wird neu geschrieben.
    Return values:
       0 - alles OK
       1 - Kalender konnte nicht gespeichert werden, Kalender-Datei wird gelšscht.
       2 - Bei der Speicherung sind Fehler aufgetreten. Datei wurde trotzdem gespeichert.
*/
int saveCalendar(char const * filename);

/*
    Die Ÿbergebene XML-Datei wird eingelesen.
    Werden Fehler im XML-Code entdeckt, wird das Laden abgebrochen und die bereits eingelesenen Termine gelšscht.
*/
int loadCalendar(char const * filename);

#endif // FILES_H_INCLUDED
