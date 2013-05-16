#ifndef DATASTRUCTURE_H_INCLUDED
#define DATASTRUCTURE_H_INCLUDED

#define MAX_APPOINTMENTS 100

typedef enum /* 0 - 6 */
{
  So = 0, Mo, Di, Mi, Do, Fr, Sa
} DayOfWeek;

typedef struct
{
    unsigned short minute;
    unsigned short hour;
//    zeitOfDay zeitOfDay;
} Tzeit;

typedef struct
{
    unsigned short day;
    unsigned short month;
    unsigned short year;
    DayOfWeek dayOfWeek;
} TDate;

typedef struct
{
    Tzeit *zeit;
    TDate *date;
    char *description;
    Tzeit *duration;
    char *location;
} TAppointment;

extern unsigned short AppointmentCount;
extern TAppointment Calendar[];

#endif // DATASTRUCTURE_H_INCLUDED
