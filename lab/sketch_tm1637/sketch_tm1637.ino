// Author: Alberto Coppini
// date: 2020-04-06
// test di connessione con tm1637. Il test si conclude facendo blinkare dei trattini sui 4 caratteri

#include <TM1637Display.h>

#define PIN_TM1637_CLK 0
#define PIN_TM1637_DIO 4

// Create display object of type TM1637Display:
TM1637Display display = TM1637Display(PIN_TM1637_CLK, PIN_TM1637_DIO);

// Create array that turns all segments on:
const uint8_t data[] = {SEG_G, SEG_G, SEG_G, SEG_G};
// Create array that turns all segments off:
const uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};
 
void setup() {
 // Clear the display:
  display.clear();
  delay(1000);
  // Set the brightness:
  display.setBrightness(5);
}

void loop() {
  // All segments on:
  display.setSegments(data);
  delay(1000);
  // All segments off:
  display.setSegments(blank);
  delay(1000);
}
