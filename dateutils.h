#ifndef DATEUTILS_H_INCLUDED
#define DATEUTILS_H_INCLUDED

int isLeapYear(int jahr);
/******************************************************
 * FUNCTION:                isLeapYear
 *-----------------------------------------------------
 * DESCRIPTION:             ...
 * FIELD OF APPLICATION:    Local
 * PARAMETER:               int jahr
 * TYP OF RESULT:           int
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        -
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
 * DESCRIPTION:             ...
 * FIELD OF APPLICATION:    Local
 * PARAMETER:               int tag
 *                          int monat
 *                          int jahr
 * TYP OF RESULT:           int
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        -
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
 * DESCRIPTION:             ...
 * FIELD OF APPLICATION:    Local
 * PARAMETER:               char const *datum
 *                          int *tag
 *                          int *monat
 *                          int *jahr
 * TYP OF RESULT:           int
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        -
 *   -> FAULT  CASE:        -
 *-----------------------------------------------------
 * DEVELOPED BY:            Seven Hallmann
 *           AT:            2013-04-13
 * CHANGES     :            -
 ******************************************************/

int getDate(char const *prompt, int *tag, int *monat, int *jahr);
/******************************************************
 * FUNCTION:                getDate
 *-----------------------------------------------------
 * DESCRIPTION:             ...
 * FIELD OF APPLICATION:    Local
 * PARAMETER:               char const *prompt
 *                          int *tag
 *                          int *monat
 *                          int *jahr
 * TYP OF RESULT:           int
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        -
 *   -> FAULT CASE:         -
 *-----------------------------------------------------
 * DEVELOPED BY:            Seven Hallmann
 *           AT:            2013-04-13
 * CHANGES     :            -
 ******************************************************/

#endif // DATEUTILS_H_INCLUDED
