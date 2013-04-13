#ifndef DATASTRUCTURE_H_INCLUDED
#define DATASTRUCTURE_H_INCLUDED

#define MAX_APPOINTMENTS 100

typedef enum
{
  So = 0, Mo, Di, Mi, Do, Fr, Sa
} Weekday;

typedef struct
{
    unsigned short minute;
    unsigned short hour;
} TTime;

typedef struct
{
    unsigned short day;
    unsigned short month;
    unsigned short year;
    Weekday weekday;
} TDate;

typedef struct
{
    TTime *time;
    TDate *date;
    char *description;
    TTime *duration;
} TAppointment;

extern unsigned short AppointmentCount;
extern TAppointment Calendar[];

#endif // DATASTRUCTURE_H_INCLUDED
