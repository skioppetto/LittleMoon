#include "moon_phases.h"

// "capomese" assigned to each month from january to december 
static const int CAPOMESE_ARR[] = {11, 12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
static const int EPATTA_VAL = 4; // valid starting from 2020-03-01
static const int EPATTA_YEARMONTH = 202002;

int incrEpatta(int epatta){
    int incr_epatta = epatta + 11;
    if (incr_epatta > 30)
        return incr_epatta - 30;
    else
        return incr_epatta;
}

int calculateEpatta (int year, int month, int day){
    int epatta = EPATTA_VAL;
    int yearmonth = year*100+month;
    int yearmonth_progr = EPATTA_YEARMONTH;
    while (yearmonth > yearmonth_progr+100){
        epatta = incrEpatta(epatta);
        yearmonth_progr += 100;
    }
    
    return epatta;    
}

/*
0	        new moon
1 to 14	    crescent moon
15	        full moon
16 to 29	waning moon
*/
int getMoonPhase(int year, int month, int day){
    int capomese = CAPOMESE_ARR[month-1];
    int epatta = calculateEpatta(year, month, day);
    int fase = day + capomese + epatta + 1;
    if (fase >= 30){
        fase -= 30;
    }
    return fase;
}
