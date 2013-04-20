#ifndef TOOLS_H
#define TOOLS_H

void clearScreen();
/******************************************************
 * FUNCTION:                clearScreen
 *-----------------------------------------------------
 * DESCRIPTION:             ...
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
 * DESCRIPTION:             ...
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
 * DESCRIPTION:             ...
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
 * DESCRIPTION:             ...
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


#endif

