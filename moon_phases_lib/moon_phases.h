/*
  moon_phases.h - Library for getting Moon Phase Day 0-29.
  Created by A. Coppini, April 8, 2020.
  see http://www.marcopersichetti.it/joomla/index.php/calcolo-delle-fasi-lunari
*/
#ifndef Moon_Phases_h
#define Moon_Phases_h
/*
0	        new moon
1 to 14	    crescent moon
15	        full moon
16 to 29	waning moon
*/
extern int getMoonPhase (int year, int month, int day);
#endif

