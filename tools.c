
#include "OS.h"
#include <stdio.h>
#include "tools.h"
#include <stdlib.h>

/*
    Statische Funktion, die einen Fehlertext in der Konsole ausgibt.
*/
static void printErrorMessage()
{
   printf("Ungueltige Eingabe");
}

/*
    Macht das Konsolenfenster wieder sch�n leer.
*/
void clearScreen()
{
    #ifdef _WINDOWS_
        system("cls");
    #endif // _WINDOWS_

    #ifdef _LINUX_OSX_
        system("clear");
    #endif // _LINUX_
}

/*
    Leert den Tastaturpuffer.
*/
void clearBuffer()
{
   char x;
   do
      scanf("%c", &x);
   while (x != '\n');
}

/*
    Fragt den Benutzer, ob er noch ein mal m�chte.
    Der Benutzer kann daraufhin eine Antwort eingeben. Bei 'j' oder 'J' wird
    der Wert 1 zur�ckgegeben. Bei 'n' oder 'N' wird 0 zur�ckgegeben.
    Andere Eingaben f�hren zu einer Fehlermeldung und wiederholter
    Benutzereingabe.
*/
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

      // Eingabe �berpr�fen
      if (anzGelesen != 1)
         printErrorMessage(); // Fehlermeldung hinter dem Eingabecursor ausgeben
      else
      {
         // G�ltige Antworten auf die Frage sind 'j', 'J', 'n' und 'N'.
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
   return 0;
}

/*
    L�sst den Benutzer Zeichen �ber die Tastatur eingeben.
    Die Funktion wird beendet, sobald der Benutzer [Enter] dr�ckt.
*/
void waitForEnter()
{
    // todo testen
    printf("Bitte Eingabetaste druecken ...");
    char x[2];
    scanf("%1[^\n]", x);
    clearBuffer();
}
