
#include "Menu.h"
#include <stdio.h>
#include <string.h>

int main()
{
    unsigned short const numMenuPoints = 4;
    int selection;
    char const * const title = "Mein Menu";
    char const * menuPoints[numMenuPoints];
    menuPoints[0] = "one";
    menuPoints[1] = "two";
    menuPoints[2] = "three";
    menuPoints[3] = "techno";


    selection = Menu(title, menuPoints, numMenuPoints);

    printf("\nDu hast \"%s\" ausgewaehlt.", menuPoints[selection-1]);

    return 0;
}
