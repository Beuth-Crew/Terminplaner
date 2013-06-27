#ifndef CALENDAR_H_INCLUDED
#define CALENDAR_H_INCLUDED

#include "datastructure.h"

// todo MAX_APPOINTMENTS kann gelöscht werden. Entsprechend müssen alle Vorkommen dieser Konstante beseitigt werden.
#define MAX_APPOINTMENTS 100

// todo kann (muss aber nicht) bestehen bleiben.
extern unsigned short AppointmentCount;

// wird ersetzt durch
// extern TAppointment *First, *Last;
extern TAppointment Calendar[MAX_APPOINTMENTS];

extern TAppointment *First;
extern TAppointment *Last;
/*
    Fügt den übergebenen Termin in den Kalender ein.
    Die Speicherbereiche der Daten des übergebenen Termins werden nicht kopiert, sondern sie werden referenziert.
    D.h. der Termin, der dann im Kalender drin ist, benutzt die bereits angelegten Speicherbereiche.
    Der Speicherbereich für den Termin selbst (TAppointment*) wird aber nicht genutzt und kann nach dieser
    Funktion theoretisch freigegeben werden.

    Nachdem der Termin in den Kalender eingefügt wurde, wird der Kalender nach der (evt.) ausgewählten Sortierung neu sortiert,
    damit der neue Termin, der am Ende des Kalenders eingefügt wird, an die richtige Stelle kommt.
*/
void addAppToCalendar(TAppointment *const app);

void createAppointment();
/******************************************************
 * FUNCTION:                createAppointment
 *-----------------------------------------------------
 * DESCRIPTION:             ...
 * FIELD OF APPLICATION:    Local
 * PARAMETER:               -
 * TYP OF RESULT:           void
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        -
 *   -> FAULT  CASE:        -
 *-----------------------------------------------------
 * DEVELOPED BY:            -
 *           AT:            -
 * CHANGES     :            -
 ******************************************************/



void editAppointment();
/******************************************************
 * FUNCTION:                editAppointment
 *-----------------------------------------------------
 * DESCRIPTION:             ...
 * FIELD OF APPLICATION:    Local
 * PARAMETER:               -
 * TYP OF RESULT:           void
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        -
 *   -> FAULT  CASE:        -
 *-----------------------------------------------------
 * DEVELOPED BY:            -
 *           AT:            -
 * CHANGES     :            -
 ******************************************************/



void deleteAppointment();
/******************************************************
 * FUNCTION:                deleteAppointment
 *-----------------------------------------------------
 * DESCRIPTION:             ...
 * FIELD OF APPLICATION:    Local
 * PARAMETER:               -
 * TYP OF RESULT:           void
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        -
 *   -> FAULT  CASE:        -
 *-----------------------------------------------------
 * DEVELOPED BY:            -
 *           AT:            -
 * CHANGES     :            -
 ******************************************************/



void searchAppointment();
/******************************************************
 * FUNCTION:                searchAppointment
 *-----------------------------------------------------
 * DESCRIPTION:             ...
 * FIELD OF APPLICATION:    Local
 * PARAMETER:               -
 * TYP OF RESULT:           void
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        -
 *   -> FAULT  CASE:        -
 *-----------------------------------------------------
 * DEVELOPED BY:            -
 *           AT:            -
 * CHANGES     :            -
 ******************************************************/



void sortCalendar();
/******************************************************
 * FUNCTION:                sortCalendar
 *-----------------------------------------------------
 * DESCRIPTION:             ...
 * FIELD OF APPLICATION:    Local
 * PARAMETER:               -
 * TYP OF RESULT:           void
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        -
 *   -> FAULT  CASE:        -
 *-----------------------------------------------------
 * DEVELOPED BY:            -
 *           AT:            -
 * CHANGES     :            -
 ******************************************************/



void listCalendar();
/******************************************************
 * FUNCTION:                listCalendar
 *-----------------------------------------------------
 * DESCRIPTION:             ...
 * FIELD OF APPLICATION:    Local
 * PARAMETER:               -
 * TYP OF RESULT:           void
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        -
 *   -> FAULT  CASE:        -
 *-----------------------------------------------------
 * DEVELOPED BY:            -
 *           AT:            -
 * CHANGES     :            -
 ******************************************************/



/*
    Befreit den Termin.
 */
void freeAppointment(TAppointment *appointment);

/*
  Befreiung fŸr den Kalender
*/
void freeCalendar();


#endif // CALENDAR_H_INCLUDED
