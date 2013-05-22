#include <stdio.h>
#include <string.h>
#include "datastructure.h"
#include "dateutils.h"
#include "files.h"



int loadCalendar(TAppointment * Calendar, unsigned short* AppointmentCount)
{
    FILE *CalendarFileStream;
    char DBFilePath[] = "C:\\Users\\andy\\Documents\\GitHub\\Terminplaner\\database\\calendar.db";
    //unsigned int AppointmentToRead;
    //unsigned int NumberOfLines;
    char CurrentLineAsString[100];


    CalendarFileStream = fopen(DBFilePath, "rt");
    if(CalendarFileStream == 0)
    {
        printf("Calendar-File konnte nicht gelesen werden!");
        fclose(CalendarFileStream);
        return 0;
    }else
    {
        if(copyLineInString(CurrentLineAsString, CalendarFileStream) && checkForCharacteristic(CurrentLineAsString, "<Calendar>") == 0)
        {
            printf("File: %s wurde als Terminplaner-Datenbank erkannt.", DBFilePath);

            if(copyLineInString(CurrentLineAsString, CalendarFileStream) && checkForCharacteristic(CurrentLineAsString, "</Calendar>") == 0)
            {
                printf("Terminplaner-Datenbank enthaelt keine Termine");
            }else
            {
                copyLineInString(CurrentLineAsString, CalendarFileStream);

                while(checkForCharacteristic(CurrentLineAsString, " <Appointment>") == 0)
                {
                    if(loadAppointment(CalendarFileStream, Calendar, * AppointmentCount, CurrentLineAsString));
                        {
                            AppointmentCount++;     //wuerd lieber *AppointmentCount++; schreiben...
                        }
                }
            }
        }else
        {
            printf("File wurde nicht als Terminplaner-Datenbank erkannt!");
            fclose(CalendarFileStream);
            return 0;
        }

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
        fprintf(CalendarFileStream," <AppointmentCount>%hu</AppointmentCount>\n", AppointmentCount);


        for(i = 0; i < AppointmentCount; i++)
        {
            fprintf(CalendarFileStream," <Appointment>\n");
            fprintf(CalendarFileStream,"  <Date>%02hu.%02hu.%04hu</Date>\n", Calendar[i].date->day, Calendar[i].date->month,Calendar[i].date->year);
            fprintf(CalendarFileStream,"  <Description>%s</Description>\n", Calendar[i].description);
            fprintf(CalendarFileStream,"  <Duration>%02hu:%02hu</Duration>\n", Calendar[i].duration->hour, Calendar[i].duration->minute);
            fprintf(CalendarFileStream,"  <Location>%s</Location>\n", Calendar[i].location);
            fprintf(CalendarFileStream," </Appointment>\n");
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

int checkForCharacteristic(char* CurrentLineAsString, char* Characteristic)
{
    if(strncmp(Characteristic, CurrentLineAsString, strlen(Characteristic)) == 0)
    {
        return 0;
    }else
    {
        return 1;
    }
}

int loadAppointment(FILE * CalendarFileStream, TAppointment* Calendar, unsigned short AppointmentCount, char * CurrentLineAsString)
{
    unsigned short LinesToRead      = 5;                                                            //Anzahl von Zeilen, die maximal zu einem Appointment gehoeren

    unsigned short TimeFound        = 0;                                                            //Zeigt an, ob der Punkt eines Appointments schon gefunden wurde
    unsigned short DateFound        = 0;
    unsigned short DescriptionFound = 0;
    unsigned short DurationFound    = 0;
    unsigned short LocationFound    = 0;

// Ueberpruefen, ob der aktuelle String signalisiert, dass keine weiteren Informationen zu diesem Appointment vorliegen
    do
    {
// Einlesen der aktuellen Zeile in den String, bei Fehler wird die Funktion mit Fehler verlassen(return 0)
        if(copyLineInString(CurrentLineAsString, CalendarFileStream))
        {
// Prueft ob bzw. welche Charakteristik vorliegt und uebergibt den aktuellen String der jeweilgen Funktion
            if(TimeFound == 0 && checkForCharacteristic(CurrentLineAsString, "  <Time>") == 0)
            {
                getTimeFromString(CurrentLineAsString, Calendar[AppointmentCount].time);
            }else if(DateFound == 0 && checkForCharacteristic(CurrentLineAsString, "  <Date>") == 0)
            {
                getDateFromString(CurrentLineAsString, Calendar[AppointmentCount].date);
            }else if(DescriptionFound == 0 && checkForCharacteristic(CurrentLineAsString, "  <Description>") == 0)
            {
                strcpy(Calendar[AppointmentCount].description, CurrentLineAsString);
            }else if(DurationFound == 0 && checkForCharacteristic(CurrentLineAsString, "  <Duration>") == 0)
            {
                getTimeFromString(CurrentLineAsString, Calendar[AppointmentCount].duration);
            }else if(LocationFound == 0 && checkForCharacteristic(CurrentLineAsString, "  <Location>") == 0)
            {
                strcpy(Calendar[AppointmentCount].location, CurrentLineAsString);
            }else
            {
                return 0;
            }

            LinesToRead--;

        }else
        {
            return 0;
        }
    }while(checkForCharacteristic(CurrentLineAsString, "</Appointment>") != 0 && LinesToRead != 0);

    return 1;
}


int copyLineInString(char * LineAsString, FILE * CalendarFileStream)
{
    unsigned int MaxLengthOfLine = 99;

    if(fgets(LineAsString, MaxLengthOfLine, CalendarFileStream) != NULL)
    {
        return 1;
    }

    return 0;
}





/*
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
*/
