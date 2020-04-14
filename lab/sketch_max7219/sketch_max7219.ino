// Author: Alberto Coppini
// 2020-04-07
// il test ha lo scopo di testare su matrice 8x8 i possibili stati delle fasi lunari.   

#include <LedControl.h>
#include "moon_phases.h"

#define PIN_MAX7219_CLK 13
#define PIN_MAX7219_CS  12
#define PIN_MAX7219_DIN 14

const int MATRIX_ELEMETS = 1;
const int MATRIX_ROWS = 8;

// define LedContrl. Last parameter is # of Elements. 
LedControl lc = LedControl (PIN_MAX7219_DIN, PIN_MAX7219_CLK, PIN_MAX7219_CS, MATRIX_ELEMETS);

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 5);
  lc.clearDisplay(0);
}

void matrixSetMoonPhase(int i){
  for (int row = 0; row < MATRIX_ROWS; row++){
      lc.setRow(0, row, MOON_PHASES[i-1][row]);
    }
  }

void loop() {
  for  (int i=1; i<=12; i++){
    matrixSetMoonPhase(i);
    delay(200);
  }
}
