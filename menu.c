
#include "menu.h"
#include "tools.h"
#include <stdio.h>
#include <assert.h>

unsigned short Menu(char const *title, char const **menuPoints, unsigned short numMenuPoints)
{
    unsigned short i; // Zählvariable
    unsigned short input; // Benutzereingabe
    int scanfRet = 0;

    // Abbrechen, falls sinnlose Parameter übergeben werden.
    assert(title);
    assert(numMenuPoints);
    assert(menuPoints);

    do
    {
        clearScreen();
        printf("- %s -\n", title);
        for (i = 0; i < numMenuPoints; ++i)
            printf("%2hu. %s\n", i + 1, menuPoints[i]);

        printf("\nAuswahl (1 - %hu): ", numMenuPoints);
        scanfRet = scanf("%hu", &input);
        clearBuffer();
    } while (scanfRet != 1 || input < 1 || input > numMenuPoints);

    return input;
}
