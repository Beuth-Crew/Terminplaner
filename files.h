#ifndef FILES_H_INCLUDED
#define FILES_H_INCLUDED

#include "datastructure.h"
#include <stdio.h>

/*
    Return values:
       0 - alles OK
       1 - Kalender konnte nicht gespeichert werden
       2 - Bei der Speicherung sind Fehler aufgetreten. Datei wurde trotzdem gespeichert.
*/
int saveCalendar(char const * filename);

int loadCalendar(char const * filename);

#endif // FILES_H_INCLUDED
