#include <stdio.h>
#include "datastructure.h"


int saveCalendar(TAppointment * Calendar, unsigned short AppointmentCount)
{
    FILE *calendarFile;
    int i;
//    char c;
//    char Text[1000];
//    int j = 0;

    calendarFile = fopen("D:\\CALENDAR\\CALENDAR.TXT", "wt");
    if(calendarFile)
    {
        fprintf(calendarFile,"<Calendar>\n");

        for(i = 0; i < AppointmentCount; i++)
        {
            fprintf(calendarFile,"  <AppointmentCount>%hu</AppointmentCount>\n", AppointmentCount);
            fprintf(calendarFile,"  <Appointment>\n");
            fprintf(calendarFile,"    <Date>%02hu.%02hu.%04hu</Date>\n", Calendar[i].date->day, Calendar[i].date->month,Calendar[i].date->year);
            fprintf(calendarFile,"    <Description>%s</Description>\n", Calendar[i].description);
            fprintf(calendarFile,"    <Duration>%02hu:%02hu</Duration>\n", Calendar[i].duration->hour, Calendar[i].duration->minute);
            fprintf(calendarFile,"    <Location>%s</Location>\n", Calendar[i].location);
            fprintf(calendarFile,"  </Appointment>\n");
        }

        fprintf(calendarFile,"</Calendar>");

        fclose(calendarFile);

        return 0;

    }else
    {
        printf("Calender-File konnte nicht erzeugt/geoeffnet werden!");

        return 1;
    }
}
