
#include "tools.h"
#include "dateutils.h"
#include "datastructure.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int isLeapYear(int jahr)
{
    if (jahr % 400 == 0)
        return 1;
    else if (jahr % 4 == 0 && jahr % 100 != 0)
        return 1;
    else
        return 0;
}

int isDateValid(TDate const *date)
{
    if (date->day < 1)
        return 0;

    if (date->year < 1582)
        return 0; // Der Gregorianische Kalender geht erst ab dem Jahr 1582 los.

    switch (date->month)
    {
    case 2:
        if (isLeapYear(date->year) == 1)
        {
            if (date->day > 29)
                return 0;
        }
        else
        {
            if (date->day > 28)
                return 0;
        }

        break;

    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        // Monate mit 31 Tagen
        if (date->day > 31)
            return 0;
        break;

    case 4:
    case 6:
    case 9:
    case 11:
        // Monate mit 30 Tagen
        if (date->day > 30)
            return 0;

        break;

    default:
        return 0; // Ung�ltiger Monat
    }

    return 1;
}

int getDateFromString(char const *datum, TDate *date)
{
    char *cTag = NULL, *cMonat = NULL, *cJahr = NULL; // Tag, Monat, Jahr als Teilstring von datum
    TDate tmpDate; // Damit das �bergebene Datum im Fehlerfall nicht ver�ndert werden muss.
    unsigned short anzPunkte = 0; // Es d�rfen maximal zwei Punkte vorkommen
    char *locDate; // lokales Datum ( = datum-Parameter)
    char *p; // Iterator

    // Datum kopieren, damit der datum-Parameter nicht ver�ndert werden muss.
    locDate = calloc(strlen(datum) + 1, sizeof(char));
    if (locDate == NULL)
        return 0; // Speicher kann nicht reserviert werden.

    p = locDate;
    strcpy(locDate, datum);

    while (*p != '\0')
    {
        if (*p >= '0' && *p <= '9')
        {
            if (cTag == NULL)
                cTag = p; // Der Tag ist noch nicht gesetzt. Er kommt als erstes.
            else if (cMonat == NULL)
                cMonat = p; // Der Monat ist noch nicht gesetzt. Er kommt als zweites.
            else if (cJahr == NULL)
                cJahr = p; // Das Jahr ist noch nicht gesetzt. Es kommt als letztes.
            else
            {
                free(locDate);
                return 0;
            }

            while ((*(p + 1) >= '0' && *(p + 1) <= '9') && *(p + 1) != '\0') // Die Zahl bis zum Ende durchlaufen
                ++p;
        }
        else if (*p == '.')
        {
            ++anzPunkte;
            *p = '\0'; // Punkte werden durch \0 ersetzt.
        }
        else
        {
            free(locDate);
            return 0; // Es ist ein ung�ltiges Zeichen enthalten.
        }

        ++p;
    }

    if (cTag == NULL || cMonat == NULL || cJahr == NULL)
        return 0; // Tag, Monat und Jahr m�ssen im Datum enthalten sein.

    if (anzPunkte != 2)
        return 0; // Es m�ssen genau zwei Punkte vorkommen

    // Die Typecast (int -> unsigned short) sollten immer funktionieren,
    // da f�r Tag, Monat und Jahr eh nur kleine positive Zahlen zul�ssig sind.
    tmpDate.day   = atoi(cTag);     if (errno != 0) return 0;
    tmpDate.month = atoi(cMonat);   if (errno != 0) return 0;
    tmpDate.year  = atoi(cJahr);    if (errno != 0) return 0;

    // Zur Sicherheit
    assert(tmpDate.day <= 31);
    assert(tmpDate.month <= 12);

    if (isDateValid(&tmpDate) == 0)
        return 0;

    date->day = tmpDate.day;
    date->month = tmpDate.month;
    date->year = tmpDate.year;

    free(locDate);
    return 1;
}

DayOfWeek calculateDayOfWeek(TDate const *date)
{
    short korrektur; // Schaltjahreskorrektur, f�r die Berechnung des Wochentages
    unsigned short monatsziffer = 0; // F�r die Berechnung des Wochentages

    assert(date); // Zur Sicherheit

    // http://de.wikipedia.org/wiki/Wochentagsberechnung
    switch (date->month)
    {
        case 1:
        case 10:
            monatsziffer = 0;
            break;

        case 5:
            monatsziffer = 1;
            break;

        case 8:
            monatsziffer = 2;
            break;

        case  2:
        case  3:
        case 11:
            monatsziffer = 3;
            break;

        case 6:
            monatsziffer = 4;
            break;

        case  9:
        case 12:
            monatsziffer = 5;
            break;

        case 4:
        case 7:
            monatsziffer = 6;
            break;

        default:
            assert(0); // Andere Werte d�rfen hier nicht auftreten!
    }

    if (date->month <= 2 && isLeapYear(date->year))
        korrektur = -1;
    else
        korrektur = 0;

    return (
            (date->day % 7) // Tagesziffer
          + (monatsziffer) // Monatsziffer
          + ( ( (date->year % 100) + (date->year % 100 / 4) ) % 7 ) // Jahresziffer
          + ( ( 3 - ( (date->year / 100) % 4 ) ) * 2 ) // Jahrhundertziffer
          + (korrektur) // Schaltjahreskorrektur
           ) % 7;
}

int getDate(char const *aufforderung, TDate **date)
{
    char eingabe[12];
    int anzEingelesen; // Anzahl richtig eingelesener Werte
    TDate tmpDate; // Damit das �bergebene Datum im Fehlerfall nicht ver�ndert wird.

    printf("\n%s", aufforderung);
    anzEingelesen = scanf("%11[^\n]", eingabe);
    clearBuffer();

    if (anzEingelesen == 1)
    {
        if (getDateFromString(eingabe, &tmpDate) == 1)
        {
            *date = malloc(sizeof(TDate));
            if (*date)
            {
                (*date)->day = tmpDate.day;
                (*date)->month = tmpDate.month;
                (*date)->year = tmpDate.year;

                // todo Wochentag berechnen
                (*date)->dayOfWeek = calculateDayOfWeek(*date);

                return 1; // Everything fine
            }
            else
                return 0; // Speicher konnte nicht reserviert werden.
        }
    }

    return 0;
}

void weekDayToStr(char *str, unsigned short dayOfWeek, unsigned short shortForm)
{
    switch (dayOfWeek)
    {
        case So:
            strcpy(str, shortForm ? "So" : "Sonntag");
            break;

        case Mo:
            strcpy(str, shortForm ? "Mo" : "Montag");
            break;

        case Di:
            strcpy(str, shortForm ? "Di" : "Dienstag");
            break;

        case Mi:
            strcpy(str, shortForm ? "Mi" : "Mittwoch");
            break;

        case Do:
            strcpy(str, shortForm ? "Do" : "Donnerstag");
            break;

        case Fr:
            strcpy(str, shortForm ? "Fr" : "Freitag");
            break;

        case Sa:
            strcpy(str, shortForm ? "Sa" : "Samstag");
            break;

        default:
            assert(0); // Das darf nicht passieren!
    }
}

// todo implementieren
int isTimeValid(TTime const *time)
{
    return 1;
}
