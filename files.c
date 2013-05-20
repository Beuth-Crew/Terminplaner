#include <stdio.h>
#include <string.h>
#include "datastructure.h"
#include "files.h"



int loadCalendar(TAppointment * Calendar, unsigned short* AppointmentCount)
{
    FILE *CalendarFileStream;
    char DBFilePath[] = "C:\\Users\\andy\\Documents\\GitHub\\Terminplaner\\database\\calendar.db";
    unsigned int DataPointer = 0;
    unsigned int NumberOfLines;


    CalendarFileStream = fopen(DBFilePath, "rt");
    if(CalendarFileStream == 0)
    {
        printf("Calendar-File konnte nicht gelesen werden!");
        fclose(CalendarFileStream);
        return 0;
    }else
    {
        // Oh man, bin schon wieder am verzweifeln!!
        // Wieso kann ich dieses Array von Arrays nicht uebergeben???

        NumberOfLines = numberOFLinesInFile(CalendarFileStream);
        char DataAsStrings[NumberOfLines][100];

        copyLinesInStrings(DataAsStrings, CalendarFileStream);




/*
        if(checkForCharacteristic(CalendarFileStream, DataPointer, "<Calendar>") == 0)
        {
            NumberOfLines = numberOFLinesInFile(CalendarFileStream);

            if()
            printf("File: %s wurde als Terminplaner-Datenbank erkannt.", DBFilePath);
            DataPointer++;

            if(checkForCharacteristic(CalendarFileStream, DataPointer, "<AppointmentCount>") == 0)
            {

                printf("In der Terminplaner-Datenbank befinden sich %hu Termine", AppointmentCount)
                if(checkForCharacteristic(CalendarFileStream, DataPointer, "<Appointment>") == 0)
                {
                    while(loadAppointment(CalendarFileStream, &DataPointer)
                    {
                        AppointmentCount++;
                    }
                }
            }
        }else
        {
            printf("File wurde nicht als Terminplaner-Datenbank erkannt!");
            fclose(CalendarFileStream);
            return 0;
        }*/
    }
    fclose(CalendarFileStream);
    return 1;
}
int saveCalendar(TAppointment * Calendar, unsigned short AppointmentCount)
{
    FILE *CalendarFileStream;
    int i;
//    char c;
//    char Text[1000];
//    int j = 0;

    CalendarFileStream = fopen("C:\\Users\\andy\\Documents\\GitHub\\Terminplaner\\database\\calendar.db", "wt");

    if(CalendarFileStream)
    {
        fprintf(CalendarFileStream,"<Calendar>\n");
        fprintf(CalendarFileStream,"  <AppointmentCount>%hu</AppointmentCount>\n", AppointmentCount);


        for(i = 0; i < AppointmentCount; i++)
        {
            fprintf(CalendarFileStream,"  <Appointment>\n");
            fprintf(CalendarFileStream,"    <Date>%02hu.%02hu.%04hu</Date>\n", Calendar[i].date->day, Calendar[i].date->month,Calendar[i].date->year);
            fprintf(CalendarFileStream,"    <Description>%s</Description>\n", Calendar[i].description);
            fprintf(CalendarFileStream,"    <Duration>%02hu:%02hu</Duration>\n", Calendar[i].duration->hour, Calendar[i].duration->minute);
            fprintf(CalendarFileStream,"    <Location>%s</Location>\n", Calendar[i].location);
            fprintf(CalendarFileStream,"  </Appointment>\n");
        }

        fprintf(CalendarFileStream,"</Calendar>");

        fclose(CalendarFileStream);

        return 1;

    }else
    {
        printf("Calender-File konnte nicht erzeugt/geoeffnet werden!");

        fclose(CalendarFileStream);
        return 0;
    }
}

int checkForCharacteristic(FILE *CalendarFileStream, unsigned int DataPointer, char* Characteristic)
{
    char CharacteristicInFile[strlen(Characteristic+1)];
//    int CharacteristicSize = strlen(Characteristic);

    fscanf(CalendarFileStream, "%s", CharacteristicInFile);

    if(strcmp(Characteristic, CharacteristicInFile) == 0)
    {
        return 0;
    }else
    {
        return 1;
    }

}

int numberOFLinesInFile(FILE *CalendarFileStream)
{
    unsigned int MaxLengthOfLine = 101;
    char DataFromCurrentLine[MaxLengthOfLine+1];
    unsigned int NumberOfLines = 0;

    while(fgets(DataFromCurrentLine, MaxLengthOfLine, CalendarFileStream) != NULL)
    {
        NumberOfLines++;
    }

    return NumberOfLines;
}

int copyLinesInStrings(char ** DataAsStrings, FILE * CalendarFileStream)
{
    unsigned int MaxLengthOfLine = 101;
    char DataFromCurrentLine[MaxLengthOfLine+1];
    unsigned int NumberOfLines = 0;

    while(fgets(DataFromCurrentLine, MaxLengthOfLine, CalendarFileStream) != NULL)
    {
        DataAsStrings[NumberOfLines] = DataFromCurrentLine;
        NumberOfLines++;
    }

    return NumberOfLines;
}
