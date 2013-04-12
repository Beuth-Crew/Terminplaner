
#include "tools.h"
#include "dateutils.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


/*
    Statische Funktion, die einen Fehlertext in der Konsole ausgibt.
*/
static void printErrorMessage()
{
    printf("Ungueltige Eingabe\n");
}

/*
    Prüft, ob das übergebene Jahr ein Schaltjahr nach dem Gregorianischen Kalender ist.
    Schaltjahre sind entweder durch 400 teilbar oder durch 4 aber nicht durch 100 teilbar.

    Gibt 1 zurück, falls es ein Schaltjahr ist, andernfalls 0.
*/
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
    Prüft, ob das übergebene Datum gültig ist (ob es tatsächlich existiert).

    Gibt 1 zurück, falls das Datum gültig ist, andernfalls 0.
*/
int isDateValid(int tag, int monat, int jahr)
{
    if (tag < 1)
        return 0;

    if (jahr < 1582)
        return 0; // Der Gregorianische Kalender geht erst ab dem Jahr 1582 los.

    switch (monat)
    {
    case 2:
        if (isLeapYear(jahr) == 1)
        {
            if (tag > 29)
                return 0;
        }
        else
        {
            if (tag > 28)
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
        if (tag > 31)
            return 0;
        break;

    case 4:
    case 6:
    case 9:
    case 11:
        // Monate mit 30 Tagen
        if (tag > 30)
            return 0;

        break;

    default:
        return 0; // Ungültiger Monat
    }

    return 1;
}

/*
    Parst ein Datum aus einer Zeichenkette.

    Gibt 1 zurück, falls ein GÜLTIGES Datum geparst werden kann, andernfalls 0.

    Die Parameter int *tag, int *monat, int *jahr enthalten im Erfolgsfall das geparste Datum.

    Hinweis: Die übergebene Zeichenkette wird in der Funktion verändert.
*/
int getDateFromString(char *datum, int *tag, int *monat, int *jahr)
{
    char *cTag = NULL, *cMonat = NULL, *cJahr = NULL; // Tag, Monat, Jahr als Teilstring von datum
    int d, m, y; // Tag, Monat, Jahr
    unsigned short anzPunkte = 0; // Es dürfen maximal zwei Punkte vorkommen

    while (*datum != '\0')
    {
        if (*datum >= '0' && *datum <= '9')
        {
            if (cTag == NULL)
                cTag = datum; // Der Tag ist noch nicht gesetzt. Er kommt als erstes.
            else if (cMonat == NULL)
                cMonat = datum; // Der Monat ist noch nicht gesetzt. Er kommt als zweites.
            else if (cJahr == NULL)
                cJahr = datum; // Das Jahr ist noch nicht gesetzt. Es kommt als letztes.
            else
                return 0;

            while ((*(datum + 1) >= '0' && *(datum + 1) <= '9') && *(datum + 1) != '\0') // Die Zahl bis zum Ende durchlaufen
                ++datum;
        }
        else if (*datum == '.')
        {
            ++anzPunkte;
            *datum = '\0'; // Punkte werden durch \0 ersetzt.
        }
        else
            return 0; // Es ist ein ungŸltiges Zeichen enthalten.

        ++datum;
    }

    if (cTag == NULL || cMonat == NULL || cJahr == NULL)
        return 0; // Tag, Monat und Jahr müssen im Datum enthalten sein.

    if (anzPunkte != 2)
        return 0; // Es müssen genau zwei Punkte vorkommen

    d = atoi(cTag);     if (errno != 0) return 0;
    m = atoi(cMonat);   if (errno != 0) return 0;
    y = atoi(cJahr);    if (errno != 0) return 0;

    if (isDateValid(d, m, y) == 0)
        return 0;

    *tag    = d;
    *monat  = m;
    *jahr   = y;

    return 1;
}

/*
    Gibt die übergebene Zeichenkette auf dem Bildschirm aus und liest dann ein Datum vom Benutzer ein.

    Die Parameter int *tag, int *monat, int *jahr enthalten im falle einer korrekten Benutzereingabe eingegebene Datum.

    Gibt bei korrekter Datumseingabe 1 zurück, andernfalls 0.

    Hinweis: Das Datum muss tatsächlich existieren.
*/
int getDate(char const *aufforderung, int *tag, int *monat, int *jahr)
{
    char eingabe[11];
    int anzEingelesen; // Anzahl richtig eingelesener Werte
    int d, m, y; // Tag, Monat, Jahr
    int weiter = 1;

    do
    {
        printf("\n%s", aufforderung);
        anzEingelesen = scanf("%10[^\n]", eingabe);
        clearBuffer();

        if (anzEingelesen == 1)
        {
            if (getDateFromString(eingabe, &d, &m, &y) == 1)
            {
                weiter = 0; // Die Schleife verlassen
                *tag = d;
                *monat = m;
                *jahr = y;
            }
            else
                printErrorMessage();
        }
    } while (weiter == 1);

    return 1;
}
