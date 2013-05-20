#ifndef FILES_H_INCLUDED
#define FILES_H_INCLUDED
#include "datastructure.h"
#include <stdio.h>

int loadCalendar(TAppointment * Calendar, unsigned short AppointmentCount);
/******************************************************
 * FUNCTION:                loadCalendar
 *-----------------------------------------------------
 * DESCRIPTION:             reads the database file "calendar.db" and stores
 *                          its content in an given Array of TAppointments.
 *                          The number of stored TAppointments is stored in
 *                          in the given unsigned short variable.
 * FIELD OF APPLICATION:    ???
 * PARAMETER:               TAppointment *
 *                          unsigned short *
 * TYP OF RESULT:           int
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        1   (datebase file was recognized as such)
 *   -> FAULT  CASE:        0   (file could not be opened/created, file opened
 *                               is no database file)
 *-----------------------------------------------------
 * DEVELOPED BY:            Martin Ortel
 *           AT:            2013-05-20
 * CHANGES     :            -
 ******************************************************/


int saveCalendar(TAppointment * Calendar, unsigned short AppointmentCount);
/******************************************************
 * FUNCTION:                saveCalendar
 *-----------------------------------------------------
 * DESCRIPTION:             writes the content of an given Array of
 *                          TAppointments in the database file "calendar.db".
 * FIELD OF APPLICATION:    ???
 * PARAMETER:               TAppointment *
 *                          unsigned short
 * TYP OF RESULT:           int
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        1   (datebase file was written)
 *   -> FAULT  CASE:        0   (file could not be opened/created)
 *-----------------------------------------------------
 * DEVELOPED BY:            Martin Ortel
 *           AT:            2013-05-20
 * CHANGES     :            -
 ******************************************************/


int checkForCharacteristic(FILE *CalendarFileStream, unsigned int DataPointer, char* Characteristic);
/******************************************************
 * FUNCTION:                checkForCharacteristic
 *-----------------------------------------------------
 * DESCRIPTION:             compares a given string to a string
 *                          read from a given data stream
 * FIELD OF APPLICATION:    ???
 * PARAMETER:               FILE *
 *                          char *
 * TYP OF RESULT:           int
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        0   (both strings are identical)
 *   -> FAULT  CASE:        1   (strings are not identical)
 *-----------------------------------------------------
 * DEVELOPED BY:            Martin Ortel
 *           AT:            2013-05-20
 * CHANGES     :            -
 ******************************************************/


int numberOFLinesInFile(FILE *CalendarFileStream);
/******************************************************
 * FUNCTION:                numberOFLinesInFile
 *-----------------------------------------------------
 * DESCRIPTION:             counts the number of Lines in a given file stream
 * FIELD OF APPLICATION:    ???
 * PARAMETER:               FILE *
 *
 * TYP OF RESULT:           int
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        0...9001   (number of lines in given file)
 *   -> FAULT  CASE:        -
 *-----------------------------------------------------
 * DEVELOPED BY:            Martin Ortel
 *           AT:            2013-05-20
 * CHANGES     :            -
 ******************************************************/


int copyLinesInStrings(char ** DataAsString, FILE * CalendarFileStream);
/******************************************************
 * FUNCTION:                copyLinesInStrings
 *-----------------------------------------------------
 * DESCRIPTION:             read each line of a given file stream storing
 *                          it in a given Array of Strings
 * FIELD OF APPLICATION:    ???
 * PARAMETER:               FILE *
 *                          char **
 * TYP OF RESULT:           int
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        0...9001   (number of strings created)
 *   -> FAULT  CASE:        -
 *-----------------------------------------------------
 * DEVELOPED BY:            Martin Ortel
 *           AT:            2013-05-20
 * CHANGES     :            -
 ******************************************************/

#endif
