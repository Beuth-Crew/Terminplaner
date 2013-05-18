#ifndef TOOLS_H
#define TOOLS_H

void clearScreen();
/******************************************************
 * FUNCTION:                clearScreen
 *-----------------------------------------------------
 * DESCRIPTION:             Macht das Konsolenfenster wieder schön leer.
 * FIELD OF APPLICATION:    Global
 * PARAMETER:               -
 * TYP OF RESULT:           void
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        -
 *   -> FAULT  CASE:        -
 *-----------------------------------------------------
 * DEVELOPED BY:            Seven Hallmann
 *           AT:            2013-04-13
 * CHANGES     :            -
 ******************************************************/

void clearBuffer();
/******************************************************
 * FUNCTION:                clearBuffer
 *-----------------------------------------------------
 * DESCRIPTION:             Leert den Tastaturpuffer.
 * FIELD OF APPLICATION:    Global
 * PARAMETER:               -
 * TYP OF RESULT:           void
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        -
 *   -> FAULT  CASE:        -
 *-----------------------------------------------------
 * DEVELOPED BY:            Seven Hallmann
 *           AT:            2013-04-13
 * CHANGES     :            -
 ******************************************************/

int askAgain();
/******************************************************
 * FUNCTION:                askAgain
 *-----------------------------------------------------
 * DESCRIPTION:             Fragt den Benutzer, ob er noch ein mal möchte.
 *                          Der Benutzer kann daraufhin eine Antwort eingeben. Bei 'j' oder 'J' wird
 *                          der Wert 1 zurückgegeben. Bei 'n' oder 'N' wird 0 zurückgegeben.
 *                          Andere Eingaben führen zu einer Fehlermeldung und wiederholter
 *                          Benutzereingabe.
 * FIELD OF APPLICATION:    Global
 * PARAMETER:               -
 * TYP OF RESULT:           void
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        -
 *   -> FAULT  CASE:        -
 *-----------------------------------------------------
 * DEVELOPED BY:            Seven Hallmann
 *           AT:            2013-04-13
 * CHANGES     :            -
 ******************************************************/

void waitForEnter();
/******************************************************
 * FUNCTION:                waitForEnter
 *-----------------------------------------------------
 * DESCRIPTION:             Lässt den Benutzer Zeichen über die Tastatur eingeben.
 *                          Die Funktion wird beendet, sobald der Benutzer [Enter] drückt.
 * FIELD OF APPLICATION:    Global
 * PARAMETER:               -
 * TYP OF RESULT:           void
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        -
 *   -> FAULT  CASE:        -
 *-----------------------------------------------------
 * DEVELOPED BY:            Seven Hallmann
 *           AT:            2013-04-13
 * CHANGES     :            -
 ******************************************************/

 void printLine(char symbol, int lineLength);
/******************************************************
 * FUNCTION:                printLine
 *-----------------------------------------------------
 * DESCRIPTION:             Ein uebergebenes Zeichen wird
                            eine uebergebene Anzahl mal
                            ausgegeben
 * FIELD OF APPLICATION:    Global
 * PARAMETER:               char symbol
                            int lineLength
 * TYP OF RESULT:           void
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        -
 *   -> FAULT  CASE:        -
 *-----------------------------------------------------
 * DEVELOPED BY:            Martin Ortel
 *           AT:            2013-04-20
 * CHANGES     :            -
 ******************************************************/

/*
    Beschreibung:           Fordert den Benutzer zur Eingabe auf, liest einen String ein und
                            speichert diesen in einem Array, dessen Speicher zur Laufzeit
                            reserviert wird und genau die Größe der Zeichenkette hat.
                            Gibt der Benutzer mehr Zeichen ein, als im maxLen-Parameter
                            angegeben, wird der Rest des Strings abgeschnitten.
                            WICHTIG: Der Speicher, der durch diese Funktion reserviert
                            wird, muss später durch den Aufrufer wieder freigegeben werden.
    Rückgabe:               Im Erfolgsfall 1, andernfalls 0.
    Parameter:
        prompt              Benutzeraufforderung, wird in die Konsole geprintet.
        maxLen              maximale Zeichenanzahl der Benutzereingabe.
        str                 Zeiger auf eine Zeichenkette (Zeiger auf ein char-Zeiger),
                            enthält nach erfolgreicher Funktion die Benutzereingabe
*/
int getText(char const *prompt, unsigned short maxLen, char **str);

int askPolarQuestion(char * Prompt);

#endif

