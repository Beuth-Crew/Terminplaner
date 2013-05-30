#ifndef CALENDAR_H_INCLUDED
#define CALENDAR_H_INCLUDED

#include "datastructure.h"

int readFilesAtStartup(TAppointment * Calendar, unsigned short * AppointmentCount);

void createAppointment(TAppointment * Calendar, unsigned short * AppointmentCount);
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

void editAppointment(TAppointment * Calendar, unsigned short * AppointmentCount);
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

void deleteAppointment(TAppointment * Calendar, unsigned short * AppointmentCount);
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

void searchAppointment(TAppointment * Calendar, unsigned short AppointmentCount);
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

void sortCalendar(TAppointment * Calendar, unsigned short AppointmentCount);
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

 void listCalendar(TAppointment * Calendar, unsigned short AppointmentCount);
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

void quitCalendar(TAppointment * Calendar, unsigned short AppointmentCount);

#endif // CALENDAR_H_INCLUDED
