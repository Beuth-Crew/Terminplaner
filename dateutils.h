#ifndef DATEUTILS_H_INCLUDED
#define DATEUTILS_H_INCLUDED

#include "datastructure.h"

int isLeapYear(int jahr);
/******************************************************
 * FUNCTION:                isLeapYear
 *-----------------------------------------------------
 * DESCRIPTION:             Prueft, ob das uebergebene Jahr ein Schaltjahr
 *                          nach dem Gregorianischen Kalender ist.
 *                          Schaltjahre sind entweder durch 400 teilbar
 *                          oder durch 4 aber nicht durch 100 teilbar.
 * FIELD OF APPLICATION:    Local
 * PARAMETER:               int jahr
 * TYP OF RESULT:           int
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        0 (keine Schaltjahr)
 *                          1 (Schaltjahr)
 *   -> FAULT  CASE:        -
 *-----------------------------------------------------
 * DEVELOPED BY:            Seven Hallmann
 *           AT:            2013-04-13
 * CHANGES     :            -
 ******************************************************/

int isDateValid(TDate const *date);
/******************************************************
 * FUNCTION:                isDateValid
 *-----------------------------------------------------
 * DESCRIPTION:             PrŸft, ob das Ÿbergebene Datum gŸltig ist.
 * FIELD OF APPLICATION:    Local
 * PARAMETER:               int tag
 *                          int monat
 *                          int jahr
 * TYP OF RESULT:           int
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        0 (Datum unguelig)
 *                          1 (Datum gueltig)
 *   -> FAULT CASE:         -
 *-----------------------------------------------------
 * DEVELOPED BY:            Seven Hallmann
 *           AT:            2013-04-13
 * CHANGES     :            -
 ******************************************************/

int isTimeValid(TTime const *date);
/******************************************************
 * FUNCTION:                isTimeValid
 *-----------------------------------------------------
 * DESCRIPTION:             Prueft, ob die uebergebene Zeit gueltig ist.
 * FIELD OF APPLICATION:    Local
 * PARAMETER:               -
 * TYP OF RESULT:           int
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        0 (Time unguelig)
 *                          1 (Time gueltig)
 *   -> FAULT CASE:         -
 *-----------------------------------------------------
 * DEVELOPED BY:            Martin Ortel
 *           AT:            2013-04-13
 * CHANGES     :            -
 ******************************************************/

int getDateFromString(char const *datum, TDate *date);
/******************************************************
 * FUNCTION:                getDateFromString
 *-----------------------------------------------------
 * DESCRIPTION:             Parst ein Datum aus einer Zeichenkette.
 * FIELD OF APPLICATION:    Local
 * PARAMETER:               char const *datum
 *                          TDate *date
 * TYP OF RESULT:           int
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        1 (Datum richtig geparst & Datum existiert)
 *   -> FAULT  CASE:        0 (Datum konnte nicht geparst werden oder Datum existiert nicht)
 *-----------------------------------------------------
 * DEVELOPED BY:            Seven Hallmann
 *           AT:            2013-04-13
 * CHANGES     :            -
 ******************************************************/

 int getTimeFromString(char const *Time1, TTime *Time2); //-- WORK IN PROGRESS --
/******************************************************
 * FUNCTION:                getTimeFromString
 *-----------------------------------------------------
 * DESCRIPTION:             Parst eine Uhrzeit aus einer Zeichenkette.
 * FIELD OF APPLICATION:    Local
 * PARAMETER:               char const *Time1
 *                          TTime *Time2
 * TYP OF RESULT:           int
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        1 (Uhrzeit richtig geparst & Uhrzeit existiert)
 *   -> FAULT  CASE:        0 (Uhrzeit konnte nicht geparst werden oder Uhrzeit existiert nicht)
 *-----------------------------------------------------
 * DEVELOPED BY:            Martin Ortel
 *           AT:            2013-05-07
 * CHANGES     :            -
 ******************************************************/

int getDate(char const *prompt, TDate **date);
/******************************************************
 * FUNCTION:                getDate
 *-----------------------------------------------------
 * DESCRIPTION:             Gibt die Ÿbergebene Zeichenkette auf dem
 *                          Bildschirm aus und liest dann ein Datum
 *                          vom Benutzer ein.
 * FIELD OF APPLICATION:    Local
 * PARAMETER:               char const *prompt
 *                          date - enthält im falle einer korrekten
 *                          Benutzereingabe das eingegebene Datum.
 * TYP OF RESULT:           int
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        1 (Datum richtig geparst & Datum existiert)
 *   -> FAULT CASE:         0 (Datum konnte nicht geparst werden)
 *-----------------------------------------------------
 * DEVELOPED BY:            Seven Hallmann
 *           AT:            2013-04-13
 * CHANGES     :            -
 ******************************************************/

/*
    Rückgabe:
    - bei 0: "Sonntag"
    - bei 1: "Monatag"
    - bei 2: "Dienstag"
    ... usw ...

    Parameter:
        str             Zeichenkette, in welche der Wochentag geschrieben wird.
        dayOfWeek       Wochentag in Form einer Ziffer 0 -> So, 1 -> Mo, usw.
        shortForm       0 - bedeutet, dass lange Bezeichnungen zurückgegeben werden.
                        1 - bedeutet, dass kurze Bezeichnungen zurückgegeben werden,
                            also z.B. "Mo" anstatt "Montag"
*/


 int getTime(char const *prompt, TTime **Time);  //-- WORK IN PROGRESS --
/******************************************************
 * FUNCTION:                getTime
 *-----------------------------------------------------
 * DESCRIPTION:             Gibt die Uebergebene Zeichenkette auf dem
 *                          Bildschirm aus und liest dann eine Uhrzeit
 *                          vom Benutzer ein.
 * FIELD OF APPLICATION:    Local
 * PARAMETER:               char const *prompt
 *                          Time - enthält im falle einer korrekten
 *                          Benutzereingabe das eingegebene Datum.
 * TYP OF RESULT:           int
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        1 (Datum richtig geparst & Datum existiert)
 *   -> FAULT CASE:         0 (Datum konnte nicht geparst werden)
 *-----------------------------------------------------
 * DEVELOPED BY:            Martin Ortel
 *           AT:            2013-05-07
 * CHANGES     :            -
 ******************************************************/

void weekDayToStr(char *str, unsigned short dayOfWeek, unsigned short shortForm);

void printDate();

void printTime();

#endif // DATEUTILS_H_INCLUDED
