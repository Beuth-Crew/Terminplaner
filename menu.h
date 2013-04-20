#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

unsigned short Menu(char const *title, char const **menuPoints, unsigned short numMenuPoints);
/************************************************************************************
 * FUNCTION:                Menu
 *-----------------------------------------------------
 * DESCRIPTION:             Diese Funktion erhaelt eine Zeichenkette mit dem Titel,
                            der ueber dem Menue stehen soll, ein Array von Zeichenketten,
                            in denen die Menuepunkte stehen sowie die Anzahl der Menuepunkte.
                            Die Funktion gibt den gewaehlten Menuepunkt als Zahl zurueck.
                            In der Funktion wird in einer Schleife erst der Bildschirminhalt
                            geloescht, dann der Titel sowie die einzelnen Menuepunkte ausgegeben.
                            Nach den Menuepunkten erscheint mit einer Leerzeile Abstand eine
                            Eingabeaufforderung auf dem Bildschirm.
                            Die Schleife wird nur verlassen, wenn der Benutzer eine gueltige
                            Eingabe (zwischen 1 und der Anzahl der Menuepunkte) eingegeben hat.
 * FIELD OF APPLICATION:    Global
 * PARAMETER:               char const *title
                            char const **menuPoints
                            unsigned short numMenuPoints
 * TYP OF RESULT:           unsigned short
 * VALUE OF RESULT:
 *   -> NORMAL CASE:        1 bis menuPoints (Auswahl des jeweiligen Menuepunkts)
 *   -> FAULT  CASE:        -
 *-----------------------------------------------------
 * DEVELOPED BY:            Seven Hallmann
 *           AT:            2013-04-13
 * CHANGES     :            -
 ******************************************************/

#endif // MENU_H_INCLUDED
