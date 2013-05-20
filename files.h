#ifndef FILES_H_INCLUDED
#define FILES_H_INCLUDED
#include "datastructure.h"
#include <stdio.h>

int loadCalendar(TAppointment * Calendar, unsigned short* AppointmentCount);

int saveCalendar(TAppointment * Calendar, unsigned short AppointmentCount);

int checkForCharacteristic(FILE *CalendarFile, unsigned int DataPointer, char* Characteristic);

int numberOFLinesInFile(FILE *CalendarFileStream);

int copyLinesInStrings(char ** DataAsString, FILE * CalendarFileStream);

#endif
