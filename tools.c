
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
   printf("Ungueltige UserInput");
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
   int ReadSuccessfully;
   char UserInput;

   do
   {
      printf("Moechten Sie noch einmal (j/n)? ");

      // BenutzerUserInput einlesen
      ReadSuccessfully = scanf("%c", &UserInput); // Ein Zeichen einlesen
      if (UserInput != '\n')
         clearBuffer();

      // UserInput überprüfen
      if (ReadSuccessfully != 1)
         printErrorMessage(); // Fehlermeldung hinter dem Eingabecursor ausgeben
      else
      {
         // Gültige Antworten auf die Frage sind 'j', 'J', 'n' und 'N'.
         switch (UserInput)
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

    printf("\nBitte Eingabetaste(Enter) druecken ...");
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
    char *UserInput = calloc(maxLen + 1, sizeof(char));

    if (UserInput)
    {
        sprintf(format, "%%%hu[^\n]", maxLen);
        do
        {
            printf(prompt);
            scanRet = scanf(format, UserInput);
            clearBuffer(); // Notwendig?
            if (scanRet == 1)
            {
                len = strlen(UserInput);
                if (len > 0)
                {
                    // Für den String wird genau so viel Speicher reserviert, wie nötig ist.
                    *str = calloc(len + 1, sizeof(char));
                    if (*str)
                        strcpy(*str, UserInput); // Benutzereingabe in das "zurückzugebende" Argumgent kopieren
                    else
                    {
                        free(UserInput);
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

    free(UserInput);
    return 1; // Alles ok
}

int askPolarQuestion(char * Prompt)
{
    int ReadSuccessfully;
    char UserInput;

    do
    {
        printf(Prompt);

// Benutzereingabe einlesen

    ReadSuccessfully = scanf("%c", &UserInput); // Ein Zeichen einlesen
    if (UserInput != '\n')
    {
        clearBuffer();
    }

// UserInput überprüfen
    if (ReadSuccessfully != 1)
    {
        printErrorMessage(); // Fehlermeldung hinter dem Eingabecursor ausgeben
    }else
    {
// Gültige Antworten auf die Frage sind 'j', 'J', 'n' und 'N'.
        switch (UserInput)
        {
            case 'j':
            case 'J':
               return 1;

            case 'n':
            case 'N':
               return 0;

            default:
               printErrorMessage(); // Fehlermeldung hinter dem UserInputcursor ausgeben
         }
      }
    }while (1);

   // Wird nie erreicht:
   return 0; // Nur um den Compiler zu beruhigen
}
