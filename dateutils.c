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

/*
int iszeitValid(Tzeit const *zeit)
{
    if (zeit->hour < 0 || zeit->hour > 24)
        return 0;

    if (zeit->minute < 0 || zeit->minute > 59)
        return 0;

    return 1;
}
*/

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
        return 0; // Ungültiger Monat
    }

    return 1;
}


int getDateFromString(char const *datum, TDate *date)
{
    char *cTag = NULL, *cMonat = NULL, *cJahr = NULL; // Tag, Monat, Jahr als Teilstring von datum
    TDate tmpDate; // Damit das übergebene Datum im Fehlerfall nicht verändert werden muss.
    unsigned short anzPunkte = 0; // Es dürfen maximal zwei Punkte vorkommen
    char *locDate; // lokales Datum ( = datum-Parameter)
    char *p; // Iterator

    // Datum kopieren, damit der datum-Parameter nicht verändert werden muss.
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
            return 0; // Es ist ein ungŸltiges Zeichen enthalten.
        }

        ++p;
    }

    if (cTag == NULL || cMonat == NULL || cJahr == NULL)
        return 0; // Tag, Monat und Jahr müssen im Datum enthalten sein.

    if (anzPunkte != 2)
        return 0; // Es müssen genau zwei Punkte vorkommen

    // Die Typecast (int -> unsigned short) sollten immer funktionieren,
    // da für Tag, Monat und Jahr eh nur kleine positive Zahlen zulässig sind.
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


int getzeitFromString(char const *zeit1, Tzeit *zeit2)
{

    char *cHour = NULL, *cMinute = NULL;                                                // Stunden, Minuten als Teilstring von Zeit
    Tzeit tmpzeit;                                                                      // Damit das übergebene Datum im Fehlerfall nicht verändert werden muss.
    unsigned short nOfColons = 0;                                                       // Es darf maximal ein Doppelpunkt vorkommen
    char *loczeit;                                                                      // lokale Zeit in der Funktion ( = Zeit-Parameter)
    char *p;                                                                            // Iterator

    loczeit = calloc(strlen(zeit1) + 1, sizeof(char));
    if (loczeit == NULL)
        return 0;                                                                       // Speicher kann nicht reserviert werden.

    p = loczeit;
    strcpy(loczeit, zeit1);

    while (*p != '\0')
    {
        if (*p >= '0' && *p <= '9')
        {
            if (cHour == NULL)
            {
                cHour = p;                                                              // Der Tag ist noch nicht gesetzt. Er kommt als erstes.
            }
            else if (cMinute == NULL)
            {
                cMinute = p;                                                            // Der Monat ist noch nicht gesetzt. Er kommt als zweites.
            }
            else
            {
                free(loczeit);
                return 0;
            }
            while ((*(p + 1) >= '0' && *(p + 1) <= '9') && *(p + 1) != '\0')            // Die Zahl bis zum Ende durchlaufen
            {
                ++p;
            }
        }

        else if (*p == '.')
        {
            ++nOfColons;
            *p = '\0';                                                                  // Punkte werden durch \0 ersetzt.
        }
        else
        {
            free(loczeit);
            return 0;                                                                   // Es ist ein ungueltiges Zeichen enthalten.
        }

        ++p;
    }

    if (cHour == NULL || cMinute == NULL)
        return 0;                                                                       // Stunden und Mintuen müssen in der Uhrzeit enthalten sein.

    if (anzPunkte != 1)
        return 0;                                                                       // Es muss genau ein Doppelpunkt vorkommen


    // Die Typecast (int -> unsigned short) sollten immer funktionieren,
    // da für Stunden und Minuten eh nur kleine positive Zahlen zulässig sind.
    tmpzeit.Hour   = atoi(cHour);     if (errno != 0) return 0;
    tmpzeit.Minute = atoi(cMinute);   if (errno != 0) return 0;

    // Zur Sicherheit
    assert(tmpzeit.Hour <= 24);
    assert(tmpzeit.Minute <= 60);

 /*   if (iszeitValid(&tmpzeit) == 0)
    {
        return 0;
    }
*/

    zeit2->Hour = tmpzeit.Hour;
    zeit2->Minute = tmpzeit.Minute;

    free(loczeit);
    return 1;
}


int getDate(char const *aufforderung, TDate **date)
{
    char eingabe[12];
    int anzEingelesen; // Anzahl richtig eingelesener Werte
    short korrektur; // Schaltjahreskorrektur, für die Berechnung des Wochentages
    unsigned short monatsziffer = 0; // Für die Berechnung des Wochentages
    TDate tmpDate; // Damit das übergebene Datum im Fehlerfall nicht verändert wird.

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

                // http://de.wikipedia.org/wiki/Wochentagsberechnung
                switch ((*date)->month)
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
                        assert(0); // Andere Werte dürfen hier nicht auftreten!
                }

                if ((*date)->month <= 2 && isLeapYear((*date)->year))
                    korrektur = -1;
                else
                    korrektur = 0;

                (*date)->dayOfWeek = (
                                       ((*date)->day % 7) // Tagesziffer
                                     + (monatsziffer) // Monatsziffer
                                     + ( ( ((*date)->year % 100) + ((*date)->year % 100 / 4) ) % 7 ) // Jahresziffer
                                     + ( ( 3 - ( ((*date)->year / 100) % 4 ) ) * 2 ) // Jahrhundertziffer
                                     + (korrektur) // Schaltjahreskorrektur
                                     ) % 7;

                return 1; // Everything fine
            }
            else
                return 0; // Speicher konnte nicht reserviert werden.
        }
    }

    return 0;
}


/*int getzeit(char const *aufforderung, Tzeit **zeit)
{
    char eingabe[5];
    int anzEingelesen; // Anzahl richtig eingelesener Werte


    printf("\n%s", aufforderung);
    anzEingelesen = scanf("%5[^\n]", eingabe);
    clearBuffer();

    if (anzEingelesen == 1)
    {
        if (getzeitFromString(eingabe, &tmpzeit) == 1)
        {
            *date = malloc(sizeof(Tzeit));
            if (*zeit)
            {
                (*zeit)->hour = tmpzeit.hour;
                (*zeit)->minute = tmpzeit.minute;

                // http://de.wikipedia.org/wiki/Wochentagsberechnung
                switch ((*date)->hour)
                {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:    break;

                    default:
                        assert(0); // Andere Werte dürfen hier nicht auftreten!
                }
        }
    }

    return 0;
}

*/
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

/*int printzeit

int printDate
*/
