#ifndef DATEUTILS_H_INCLUDED
#define DATEUTILS_H_INCLUDED

int isLeapYear(int jahr);

int isDateValid(int tag, int monat, int jahr);

int getDateFromString(char *datum, int *tag, int *monat, int *jahr);

int getDate(char const *prompt, int *tag, int *monat, int *jahr);

#endif // DATEUTILS_H_INCLUDED
