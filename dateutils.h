#ifndef DATEUTILS_H_INCLUDED
#define DATEUTILS_H_INCLUDED

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

int isDateValid(int tag, int monat, int jahr);
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

int getDateFromString(char const *datum, int *tag, int *monat, int *jahr);
/******************************************************
 * FUNCTION:                getDateFromString
 *-----------------------------------------------------
 * DESCRIPTION:             Parst ein Datum aus einer Zeichenkette.
 * FIELD OF APPLICATION:    Local
 * PARAMETER:               char const *datum
 *                          int *tag
 *                          int *monat
 *                          int *jahr
 * TYP OF RESULT:           int
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        1 (Datum richtig geparst)
 *   -> FAULT  CASE:        0 (Datum konnte nicht geparst werden)
 *-----------------------------------------------------
 * DEVELOPED BY:            Seven Hallmann
 *           AT:            2013-04-13
 * CHANGES     :            -
 ******************************************************/

int getDate(char const *prompt, int *tag, int *monat, int *jahr);
/******************************************************
 * FUNCTION:                getDate
 *-----------------------------------------------------
 * DESCRIPTION:             Gibt die Ÿbergebene Zeichenkette auf dem
 *                          Bildschirm aus und liest dann ein Datum
 *                          vom Benutzer ein.
 * FIELD OF APPLICATION:    Local
 * PARAMETER:               char const *prompt
 *                          int *tag
 *                          int *monat
 *                          int *jahr
 * TYP OF RESULT:           int
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        1 (Datum richtig geparst)
 *   -> FAULT CASE:         0 (Datum konnte nicht geparst werden)
 *-----------------------------------------------------
 * DEVELOPED BY:            Seven Hallmann
 *           AT:            2013-04-13
 * CHANGES     :            -
 ******************************************************/

#endif // DATEUTILS_H_INCLUDED
