
#include <string.h>
#include <stdio.h>

#ifdef _WINDOWS_
#include <windows.h>
#else
#include <unistd.h>
#endif // _WINDOWS_


void animi_out(char const *text, float velocity)
{
    char const *i; // Iterator

    for (i = text; i < text + strlen(text); ++i)
    {
        printf("%c", *i);
        fflush(stdout);

        #ifdef _WINDOWS_
            Sleep(1000.0 / velocity);
        #else
            usleep(1000000.0 / velocity);
        #endif // _WINDOWS_
    }
}
