
#include "OS.h"
#include <stdio.h>
#include "tools.h"
#include <stdlib.h>
#include <string.h>

/*
    Statische Funktion, die einen Fehlertext in der Konsole ausgibt.
*/
static void printErrorMessage()
{
   printf("Ungueltige Eingabe");
}

void clearScreen()
{
    #ifdef _WINDOWS_
        system("cls");
    #endif // _WINDOWS_

    #ifdef _LINUX_OSX_
        system("clear");
    #endif // _LINUX_
}

void clearBuffer()
{
   char x;
   do
      scanf("%c", &x);
   while (x != '\n');
}

int askAgain()
{
   int anzGelesen;
   char eingabe;

   do
   {
      printf("Moechten Sie noch einmal (j/n)? ");

      // Benutzereingabe einlesen
      anzGelesen = scanf("%c", &eingabe); // Ein Zeichen einlesen
      if (eingabe != '\n')
         clearBuffer();

      // Eingabe überprüfen
      if (anzGelesen != 1)
         printErrorMessage(); // Fehlermeldung hinter dem Eingabecursor ausgeben
      else
      {
         // Gültige Antworten auf die Frage sind 'j', 'J', 'n' und 'N'.
         switch (eingabe)
         {
            case 'j':
            case 'J':
               return 1;

            case 'n':
            case 'N':
               return 0;

            default:
               printErrorMessage(); // Fehlermeldung hinter dem Eingabecursor ausgeben
         }
      }
   } while (1);

   // Wird nie erreicht:
   return 0; // Nur um den Compiler zu beruhigen
}

void waitForEnter()
{
    char x[2]; // 1 Zeichen + '\0'

    printf("Bitte Eingabetaste druecken ...");
    scanf("%1[^\n]", x);
    clearBuffer();
}

void printLine(char printChar, int lineLength)
{
    int i;

    for(i = 0; i < lineLength; i++)
        printf("%c", printChar);

    printf("\n");
}

int getText(char const *prompt, unsigned short maxLen, char **str)
{
    char format[20]; // Inhalt sieht nachher beispielsweise so aus (bei maxLen = 15): "%15[^\n]"
    int scanRet;
    int len; // Länge der vom Benutzer eingegebenen Zeichenkette
    char *eingabe = calloc(maxLen + 1, sizeof(char));

    if (eingabe)
    {
        sprintf(format, "%%%hu[^\n]", maxLen);
        do
        {
            printf(prompt);
            scanRet = scanf(format, eingabe);
            clearBuffer(); // Notwendig?
            if (scanRet == 1)
            {
                len = strlen(eingabe);
                if (len > 0)
                {
                    // Für den String wird genau so viel Speicher reserviert, wie nötig ist.
                    *str = calloc(len + 1, sizeof(char));
                    if (*str)
                        strcpy(*str, eingabe); // Benutzereingabe in das "zurückzugebende" Argumgent kopieren
                    else
                    {
                        free(eingabe);
                        return 0; // Es konnte kein Speicher reserviert werden
                    }
                }
                else
                    scanRet = 0; // Der Benutzer hat nur die Eingabetaste gedrückt.
            }
        } while (scanRet != 1);
    }
    else
        return 0; // Speicher konnte nicht reserviert werden

    free(eingabe);
    return 1; // Alles ok
}
