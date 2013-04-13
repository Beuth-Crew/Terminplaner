
#include "tools.h"
#include "dateutils.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


/*
    Statische Funktion, die einen Fehlertext in der Konsole ausgibt.
*/
static void printErrorMessage()
{
    printf("Ungueltige Eingabe\n");
}

/*
    Pr�ft, ob das �bergebene Jahr ein Schaltjahr nach dem Gregorianischen Kalender ist.
    Schaltjahre sind entweder durch 400 teilbar oder durch 4 aber nicht durch 100 teilbar.

    Gibt 1 zur�ck, falls es ein Schaltjahr ist, andernfalls 0.
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
    Pr�ft, ob das �bergebene Datum g�ltig ist (ob es tats�chlich existiert).

    Gibt 1 zur�ck, falls das Datum g�ltig ist, andernfalls 0.
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
        return 0; // Ung�ltiger Monat
    }

    return 1;
}

/*
    Parst ein Datum aus einer Zeichenkette.

    Gibt 1 zur�ck, falls ein G�LTIGES Datum geparst werden kann, andernfalls 0.

    Die Parameter int *tag, int *monat, int *jahr enthalten im Erfolgsfall das geparste Datum.

    Hinweis: Die �bergebene Zeichenkette wird in der Funktion ver�ndert.
*/
int getDateFromString(char const *datum, int *tag, int *monat, int *jahr)
{
    char *cTag = NULL, *cMonat = NULL, *cJahr = NULL; // Tag, Monat, Jahr als Teilstring von datum
    int d, m, y; // Tag, Monat, Jahr
    unsigned short anzPunkte = 0; // Es d�rfen maximal zwei Punkte vorkommen
    char *date; // = datum (Parameter)

    // Datum kopieren, damit der �bergebene String nicht ver�ndert werden muss, sondern nur der lokale.
    date = malloc(sizeof(char) * strlen(datum));
    strcpy(date, datum);

    while (*date != '\0')
    {
        if (*date >= '0' && *date <= '9')
        {
            if (cTag == NULL)
                cTag = date; // Der Tag ist noch nicht gesetzt. Er kommt als erstes.
            else if (cMonat == NULL)
                cMonat = date; // Der Monat ist noch nicht gesetzt. Er kommt als zweites.
            else if (cJahr == NULL)
                cJahr = date; // Das Jahr ist noch nicht gesetzt. Es kommt als letztes.
            else
            {
                free(date);
                return 0;
            }

            while ((*(date + 1) >= '0' && *(date + 1) <= '9') && *(date + 1) != '\0') // Die Zahl bis zum Ende durchlaufen
                ++date;
        }
        else if (*date == '.')
        {
            ++anzPunkte;
            *date = '\0'; // Punkte werden durch \0 ersetzt.
        }
        else
        {
            free(date);
            return 0; // Es ist ein ung�ltiges Zeichen enthalten.
        }

        ++date;
    }

    if (cTag == NULL || cMonat == NULL || cJahr == NULL)
        return 0; // Tag, Monat und Jahr m�ssen im Datum enthalten sein.

    if (anzPunkte != 2)
        return 0; // Es m�ssen genau zwei Punkte vorkommen

    d = atoi(cTag);     if (errno != 0) return 0;
    m = atoi(cMonat);   if (errno != 0) return 0;
    y = atoi(cJahr);    if (errno != 0) return 0;

    if (isDateValid(d, m, y) == 0)
        return 0;

    *tag    = d;
    *monat  = m;
    *jahr   = y;

    free(date);
    return 1;
}

/*
    Gibt die �bergebene Zeichenkette auf dem Bildschirm aus und liest dann ein Datum vom Benutzer ein.

    Die Parameter int *tag, int *monat, int *jahr enthalten im falle einer korrekten Benutzereingabe eingegebene Datum.

    Gibt bei korrekter Datumseingabe 1 zur�ck, andernfalls 0.

    Hinweis: Das Datum muss tats�chlich existieren.
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
