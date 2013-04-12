
#include "menu.h"
#include "tools.h"
#include <stdio.h>

unsigned short Menu(char *title, char **menuPoints, unsigned short numMenuPoints)
{
    unsigned short i; // Zählvariable
    unsigned short input; // Benutzereingabe
    int scanfRet = 0;

    do
    {
        clearScreen();
        printf("- %s -\n", title);
        for (i = 0; i < numMenuPoints; ++i)
            printf("%2hu. %s\n", i, menuPoints[i]);

        printf("\nAuswahl (1 - %hu): ", numMenuPoints);
        scanfRet = scanf("%hu", &input);
        clearBuffer();
    } while (scanfRet != 1 || input < 1 || input > numMenuPoints);
    // todo

    return input;
}
