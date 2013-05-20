#include "datastructure.h"


void swapAppointments(TAppointment Appointment1, TAppointment Appointment2)
{
    TAppointment temp;

    temp = Appointment1;
    Appointment1 = Appointment2;
    Appointment2 = temp;
}
