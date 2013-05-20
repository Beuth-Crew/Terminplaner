#ifndef CALENDAR_H_INCLUDED
#define CALENDAR_H_INCLUDED

#include "datastructure.h"

int readFilesAtStartup();

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

void quitCalendar();

#endif // CALENDAR_H_INCLUDED
