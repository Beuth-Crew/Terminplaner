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

// Pr�ft, ob die Stunden- und Minutenzahlen plausible Werte enthalten.
// Gibt 1 bei g�ltiger Zeit zur�ck,
// andernfalls 0.
int isTimeValid(TTime const *time);

int isDateValid(TDate const *date);
/******************************************************
 * FUNCTION:                isDateValid
 *-----------------------------------------------------
 * DESCRIPTION:             Pr�ft, ob das �bergebene Datum g�ltig ist.
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


 int getTimeFromString(char const *UserInput, TTime *time);
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
 * DESCRIPTION:             Gibt die �bergebene Zeichenkette auf dem
 *                          Bildschirm aus und liest dann ein Datum
 *                          vom Benutzer ein.
 * FIELD OF APPLICATION:    Local
 * PARAMETER:               char const *prompt
 *                          date - enth�lt im falle einer korrekten
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





 int getTime(char const *prompt, TTime **Time);  //-- WORK IN PROGRESS --
/******************************************************
 * FUNCTION:                getTime
 *-----------------------------------------------------
 * DESCRIPTION:             Gibt die Uebergebene Zeichenkette auf dem
 *                          Bildschirm aus und liest dann eine Uhrzeit
 *                          vom Benutzer ein.
 * FIELD OF APPLICATION:    Local
 * PARAMETER:               char const *prompt
 *                          Time - enth�lt im falle einer korrekten
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

/*
  Untersucht das Datum, also Tag, Monat und Jahr und berechnet daraus
  den Wochentag.
  Gibt den Wochentag als Zahl zur�ck.
  R�ckgabe ist ein Wert der DayOfWeek-Aufz�hlung.
*/
DayOfWeek calculateDayOfWeek(TDate const *date);

/*
    R�ckgabe:
    - bei 0: "Sonntag"
    - bei 1: "Monatag"
    - bei 2: "Dienstag"
    ... usw ...

    Parameter:
        str             Zeichenkette, in welche der Wochentag geschrieben wird.
        dayOfWeek       Wochentag in Form einer Ziffer 0 -> So, 1 -> Mo, usw.
        shortForm       0 - bedeutet, dass lange Bezeichnungen zur�ckgegeben werden.
                        1 - bedeutet, dass kurze Bezeichnungen zur�ckgegeben werden,
                            also z.B. "Mo" anstatt "Montag"
*/
char* weekDayToStr(char *str, unsigned short dayOfWeek, unsigned short shortForm);

/*
  Gibt in einer Zeile einen Termin aus, mit Startzeitpunkt, Endzeitpunkt, Ort und Beschreibung
  Das Datum des Termins wird nicht ausgegeben.
*/
void printAppointment();

/*
  Gibt die �bergebene Zeit auf dem Bildschirm aus.
*/
void printTime(TTime const *time);

/*
  Gibt das Datum im Format "Freitag, der 01.01.2001" aus.
  Gibt die Anzahl der ausgegebenen Zeichen zur�ck.
*/
unsigned short printDate(TDate const *date);

/*
  Addiert die beiden �bergebenen Zeiten
  und speichert das Ergebnis in der TTime-Struktur, auf die *result zeigt.
  Es werden nur g�ltige Ergebnis-Zeiten von 00:00 bis 23:59 erzeugt.

  Parameter:
    - result muss auf eine TTime-Struktur zeigen
    - time1 darf NULL sein
    - time2 darf auch NULL sein

  Returns:
    0 - Wenn die beiden Zeiten zusammengerechnet innerhalb der Tagesgrenze 23:59 sind.
    1 - Wenn die beiden Zeiten zusammengerechnet die 24 Stunden sprengen.
*/
unsigned short addTime(TTime const *time1, TTime const *time2, TTime *result);

/*
  Tauscht die Werte der beiden �bergebenen TAppointments-Structs.
*/
void swapAppointments(TAppointment *a1, TAppointment *a2);

short cmpDates(TDate const *d1, TDate const *d2);
short cmpTimes(TTime const *t1, TTime const *t2);
short cmpApps_DateTime(TAppointment const *a1, TAppointment const *a2);
short cmpApps_DurDateTime(TAppointment const *a1, TAppointment const *a2);
short cmpApps_DescDateTime(TAppointment const *a1, TAppointment const *a2);
short cmpApps_LocDateTime(TAppointment const *a1, TAppointment const *a2);

#endif // DATEUTILS_H_INCLUDED
