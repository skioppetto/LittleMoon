// Author: Alberto Coppini
// 2020-04-07
// il test ha lo scopo di testare su matrice 8x8 i possibili stati delle fasi lunari.   

#include <LedControl.h>
#include "moon_phases.h"

#define PIN_MAX7219_CLK 13
#define PIN_MAX7219_CS  12
#define PIN_MAX7219_DIN 14

// define LedContrl. Last parameter is # of Elements. 
LedControl lc = LedControl (PIN_MAX7219_DIN, PIN_MAX7219_CLK, PIN_MAX7219_CS, 1);

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 5);
  lc.clearDisplay(0);
}

void loop() {
  for  (int i=0; i<12; i++){
    for (int row = 0; row < 8; row++){
      lc.setRow(0, row, MOON_PHASES[i][row]);
    }
    delay(200);
  }
}
