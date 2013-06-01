#ifndef CALENDAR_H_INCLUDED
#define CALENDAR_H_INCLUDED

#include "datastructure.h"

int readFilesAtStartup(TAppointment * Calendar, unsigned short * AppointmentCount);
/******************************************************
 *
 * FUNCTION:                readFilesAtStartup
 *-----------------------------------------------------
 * DESCRIPTION:             calls funktion loadCalendar and returns its value of result
 *
 * FIELD OF APPLICATION:    Local
 *
 * PARAMETER:               TAppointment * Calendar
 *                          unsigned short * AppointmentCount
 *
 * TYP OF RESULT:           int
 *
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        1   -   loadCalender could open a Calendar-File
 *   -> FAULT  CASE:        0   -   loadCalendar could NOT open a Calendar-File
 *
 *-----------------------------------------------------
 *
 * DEVELOPED BY:            Maritn Ortel
 *           AT:            -
 * CHANGES     :            -
 *
 ******************************************************/



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
