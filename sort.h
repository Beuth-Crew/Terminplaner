//
//  sort.h
//  Terminplaner
//
//  Created by Martin on 01.06.13.
//  Copyright (c) 2013 orTel. All rights reserved.
//

#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

typedef enum
{
    Sort_None, Sort_DateTime, Sort_DescDateTime, Sort_LocDateTime, Sort_DurDateTime
} Sortierung;

extern Sortierung sortierung;

/*
    Sortiert das Calendar-Array mit dem Quicksort-Algorithmus.

    Parameter:
        - compare - Vergleichsfunktion, die bestimmt, in welcher Reihenfolge die Termine sortiert werden.
                    Die Vergleichsfunktion muss zwei TAppointments-Structs vergleichen und
                    einen Wert > 0 zurückgeben, falls der erste Termin weiter hinten einsortiert werden soll, als der zweite,
                    einen Wert < 0 zurückgeben, falls der erste Termin weiter vorne  einsortiert werden soll, als der zweite
                    und einen Wert = 0, wenn die Reihenfolge unter den beiden Terminen egal ist.
*/
void quickSortCalendar(short (*compare)(TAppointment const*, TAppointment const*));

#endif // FILES_H_INCLUDED
