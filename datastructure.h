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

typedef struct sAppointment
{
//      Next- und Prev-Zeiger auf die eigene Struktur hinzugefügt
    TTime *time;
    TDate *date;
    char *description;
    TTime *duration;
    char *location;
    struct sAppointment *Next;
    struct sAppointment *Prev;
} TAppointment;

#endif // DATASTRUCTURE_H_INCLUDED
