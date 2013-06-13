#ifndef DATASTRUCTURE_H_INCLUDED
#define DATASTRUCTURE_H_INCLUDED

typedef enum /* 0 - 6 */
{
  So = 0, Mo, Di, Mi, Do, Fr, Sa
} DayOfWeek;

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
    DayOfWeek dayOfWeek;
} TDate;

typedef struct
{
    TTime *time;
    TDate *date;
    char *description;
    TTime *duration;
    char *location;
} TAppointment;

#define MAX_APPOINTMENTS 100
extern unsigned short AppointmentCount;
extern TAppointment Calendar[MAX_APPOINTMENTS];

#endif // DATASTRUCTURE_H_INCLUDED
