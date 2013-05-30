#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "datastructure.h"
#include "dateutils.h"
#include "files.h"
#include "calendar.h"



int loadCalendar(TAppointment * Calendar, unsigned short * AppointmentCount)
{
    FILE *CalendarFileStream;
    char DBFilePath[] = "/Volumes/HDD-DATA/C/Terminplaner/Terminplaner/Terminplaner/database/calendar.db";
    //unsigned int AppointmentToRead;
    //unsigned int NumberOfLines;
    char CurrentLineAsString[100];
    char CurrentCleanString[90];


    CalendarFileStream = fopen(DBFilePath, "rt");
    if(CalendarFileStream == 0)
    {
        printf("Calendar-File konnte nicht gelesen werden!\n");
        fclose(CalendarFileStream);
        return 0;
    }else
    {
        if(copyLineInString(CurrentLineAsString, CalendarFileStream) && checkForCharacteristic(CurrentLineAsString, "<Calendar>") == 0)
        {
            printf("File: %s wurde als Terminplaner-Datenbank erkannt.\n", DBFilePath);

            if(copyLineInString(CurrentLineAsString, CalendarFileStream) && checkForCharacteristic(CurrentLineAsString, "</Calendar>") == 0)
            {
                printf("Terminplaner-Datenbank enthaelt keine Termine\n");
            }else
            {
                
                cleanStringFromCharacteristic(CurrentLineAsString, "<AppointmentCount>", CurrentCleanString);
                
                
                
                while(copyLineInString(CurrentLineAsString, CalendarFileStream) == 1 && checkForCharacteristic(CurrentLineAsString, "<Appointment>") == 0)
                {
                    if(loadAppointment(CalendarFileStream, Calendar, AppointmentCount, CurrentLineAsString))
                    {
                        *(AppointmentCount) = *(AppointmentCount) + 1;
                        printf("Termin %i wurde eingelesen\n", *(AppointmentCount));
                    }
                }
            }
        }else
        {
            printf("File wurde nicht als Terminplaner-Datenbank erkannt!\n");
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

    CalendarFileStream = fopen("/Volumes/HDD-DATA/C/Terminplaner/Terminplaner/Terminplaner/database/calendar.db", "wt");

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
        printf("Calender-File konnte nicht erzeugt/geoeffnet werden!\n");

        fclose(CalendarFileStream);
        return 0;
    }
}


int checkForCharacteristic(char* CurrentLineAsString, char* Characteristic)
{
    int i = 0;                                                          //Durchgehen der Zeichen von CurrentLine
    int j = 0;                                                          //Durchgehen der Zeichen von Characteristic
    int l = 0;                                                          //Zaehler der uebereinstimmenden Zeichen
    
// Durchgehen des uebergebene Strings, Zeichen fuer Zeichen bis zum Zeilenumbruch
    
    for(i = 0; strlen(CurrentLineAsString) >= i; i++)
    {

// Ueberpruefen ob das aktuelle Zeichen mit dem ersten Zeichen der Charakteristik uebereinstimmt
        
        if(*(CurrentLineAsString + i) == *(Characteristic + j))
        {
            i++;
            j++;
            l++;
            
// weiter Ueberpruefen ob das jeweilig aktuelle Zeichen mit dem jeweilgen Zeichen der Charakteristik uebereinstimmt
            
            while(*(CurrentLineAsString + i) - *(Characteristic + j) == 0)
            {
                i++;
                j++;
                l++;
            }
            
// wenn die Charakteristik erkannt wurde wird der Funktionswert 0 zurueckgegeben            
            if(l == strlen(Characteristic))
            {
                return 0;
            }else
            {
                return 1; 
            }
        }
    }
    
    return 1;
}

int cleanStringFromCharacteristic(char * CurrentLineAsString, char * Characteristic, char * CurrentCleanString)
{
    int i = 0;
    int j = 0;
    
    if(checkForCharacteristic(CurrentLineAsString,Characteristic) == 0)
    {
        for(i = 0; strlen(CurrentLineAsString) >= i; i++)
        {
            if(*(CurrentLineAsString + i) == '>')
            {
                while(*(CurrentLineAsString + i) != '<')
                {
                    i++;
                    
                    *(CurrentCleanString + j) = *(CurrentLineAsString + i);
                    
                    j++;
                }
                 *(CurrentCleanString + j - 1) = '\0';
                
                return 1;
            }
            
        }
       
        
        return 0;
        
    }else
    {
        return 0;
    }
}


int loadAppointment(FILE * CalendarFileStream, TAppointment * Calendar, unsigned short * AppointmentCount, char * CurrentLineAsString)
{
    unsigned short LinesToRead      = 6;                                                            //Anzahl von Zeilen, die maximal zu einem Appointment gehoeren

    unsigned short TimeFound        = 0;                                                            //Zeigt an, ob der Punkt eines Appointments schon gefunden wurde
    unsigned short DateFound        = 0;
    unsigned short DescriptionFound = 0;
    unsigned short DurationFound    = 0;
    unsigned short LocationFound    = 0;
    
    
    char CurrentCleanString[90];
    

    Calendar[*AppointmentCount].time = malloc(sizeof(TTime));
    Calendar[*AppointmentCount].date = malloc(sizeof(TDate));
    Calendar[*AppointmentCount].description = (char *)malloc(sizeof(char)*strlen(CurrentLineAsString));
    Calendar[*AppointmentCount].duration = malloc(sizeof(TTime));
    Calendar[*AppointmentCount].location = (char *)malloc(sizeof(char)*strlen(CurrentLineAsString));
    
// Ueberpruefen, ob der aktuelle String signalisiert, dass keine weiteren Informationen zu diesem Appointment vorliegen
    do
    {                          
// Einlesen der aktuellen Zeile in den String, bei Fehler wird die Funktion mit Fehler verlassen(return 0)
        if(copyLineInString(CurrentLineAsString, CalendarFileStream) && checkForCharacteristic(CurrentLineAsString, "</Appointment>") != 0)
        
        {

            
// Prueft ob bzw. welche Charakteristik vorliegt und uebergibt den aktuellen String der jeweilgen Funktion
            if(TimeFound == 0 && checkForCharacteristic(CurrentLineAsString, "<Time>") == 0)
                
            {
                
                
                if(Calendar[*AppointmentCount].time)
                {
                    cleanStringFromCharacteristic(CurrentLineAsString, "<Time>", CurrentCleanString);
                
                    getTimeFromString(CurrentCleanString, Calendar[*AppointmentCount].time);
                
                    TimeFound = 1;
                }
                
            }else if(DateFound == 0 && checkForCharacteristic(CurrentLineAsString, "<Date>") == 0)
            
            {

                if(Calendar[*AppointmentCount].date)
                {
                    cleanStringFromCharacteristic(CurrentLineAsString, "<Date>", CurrentCleanString);
                
                    getDateFromString(CurrentCleanString, Calendar[*AppointmentCount].date);
                
                    DateFound = 1;
                }
            
            }else if(DescriptionFound == 0 && checkForCharacteristic(CurrentLineAsString, "<Description>") == 0)
            
            {
                
                if(Calendar[*AppointmentCount].description)
                {
                    cleanStringFromCharacteristic(CurrentLineAsString, "<Description>", CurrentCleanString);

                    strcpy(Calendar[*AppointmentCount].description, CurrentCleanString);
                
                    DescriptionFound = 1;
                }
            
            }else if(DurationFound == 0 && checkForCharacteristic(CurrentLineAsString, "<Duration>") == 0)
            
            {
                
                if(Calendar[*AppointmentCount].duration)
                {
                    cleanStringFromCharacteristic(CurrentLineAsString, "<Duration>", CurrentCleanString);
                
                    getTimeFromString(CurrentCleanString, Calendar[*AppointmentCount].duration);
                
                    DurationFound = 1;
                }
            
            }else if(LocationFound == 0 && checkForCharacteristic(CurrentLineAsString, "<Location>") == 0)
            
            {
                
                if(Calendar[*AppointmentCount].location)
                {
                    cleanStringFromCharacteristic(CurrentLineAsString, "<Location>", CurrentCleanString);
                
                    strcpy(Calendar[*AppointmentCount].location, CurrentCleanString);
                
                    LocationFound = 1;
                }
            
            }

            LinesToRead--;
        }else
        
            
        //if(DateFound == 1)
        //{
        
            return 1;
        //}else
        //{
        //    return 0;
        //}

    }while(LinesToRead);
    
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

