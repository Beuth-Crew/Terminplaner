
#include "list.h"
#include "calendar.h"
#include "datastructure.h"
#include <stdio.h>

// todo
// insertInList (zum sortierten Einfügen in die verkettete Liste) sowie
// Die verkettete Liste soll immer nach Datum und Uhrzeit sortiert sein;
// hierfür kann die Vergleichsfunktion vom Sortieren nach Datum und Uhrzeit wiederverwendet werden.

TAppointment* removeFromList()
{
    TAppointment *rem = NULL; // Entferntes Listenelement

    if (First == NULL)
        return NULL; // Leere Liste

    rem = First;
    if (First == Last)
        First = Last = NULL; // Nur ein Element in der Liste
    else
        First = First->Next; // Mindestens zwei Elemente in der Liste

    return rem;
}
