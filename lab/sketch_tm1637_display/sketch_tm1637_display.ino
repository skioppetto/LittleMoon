// Author: Alberto Coppini
// date: 2020-04-06
// test di per la produzione dei messaggi previsti su display tm1637. 
// A rotazione verranno chiamati tutti i possibili stati mostrando il messaggio

#include <TM1637Display.h>

#define PIN_TM1637_CLK 0
#define PIN_TM1637_DIO 4

// Create display object of type TM1637Display:
TM1637Display display = TM1637Display(PIN_TM1637_CLK, PIN_TM1637_DIO);


const uint8_t conn[] = {SEG_G|SEG_E|SEG_D, SEG_G|SEG_E|SEG_D|SEG_C, SEG_G|SEG_E|SEG_C, SEG_G|SEG_E|SEG_C };
const uint8_t conf[] = {SEG_G|SEG_E|SEG_D, SEG_G|SEG_E|SEG_D|SEG_C, SEG_G|SEG_E|SEG_C, SEG_E|SEG_F|SEG_G|SEG_A};
const uint8_t eapi[] = {SEG_D|SEG_E|SEG_G|SEG_F|SEG_A, SEG_D|SEG_E|SEG_G|SEG_A|SEG_B|SEG_C, SEG_E|SEG_G|SEG_A|SEG_B|SEG_F, SEG_E|SEG_A};
const uint8_t econ[] = {SEG_D|SEG_E|SEG_G|SEG_F|SEG_A, SEG_G|SEG_E|SEG_D, SEG_G|SEG_E|SEG_D|SEG_C, SEG_G|SEG_E|SEG_C};
const uint8_t empty[] ={0x00, 0x00, 0x00, 0x00};
 
const  int DISPLAY_CONN = 1;
const  int DISPLAY_CONF = 2;
const  int DISPLAY_EAPI = 3;
const  int DISPLAY_ECON = 4;
const  int DISPLAY_BLINK_INTERVAL = 500;

int display_empty = 0;
int display_set = 0;
unsigned long display_time = 0;

int message_duration = 5000;
unsigned long message_time = 0;

void setup() {
  Serial.begin(9600);
  display.clear();
  display.setBrightness(5);
  message_time = millis();
}

void displayConn(){
  if (display_set != DISPLAY_CONN){
    display.setSegments(conn);
    display_set = DISPLAY_CONN;
  }
}

void displayConf(){
  if (display_set != DISPLAY_CONF){
    display.setSegments(conf);
    display_set = DISPLAY_CONF;
  }
}

void displayBlink(int displayId, const uint8_t data[]){
  if (display_set != displayId){
    display.setSegments(data);
    display_time = millis();
    display_set = displayId;
    display_empty = 0;
  }else{
    if (millis() - display_time >= DISPLAY_BLINK_INTERVAL){
          if (!display_empty){
              display_empty = 1;
              display.setSegments(data);
            }
           else {
              display_empty = 0;
              display.setSegments(empty);
            }
            display_time = millis();
      }
  }
  }

void displayErrApi(){
  displayBlink(DISPLAY_EAPI,eapi);
}

void displayErrConn(){
  displayBlink(DISPLAY_ECON,econ);
}
int pos = 0;
void loop() {
    switch (pos){
      case 0: 
        displayConn();
        break;
      case 1: 
        displayConf();
        break;
      case 2: 
        displayErrConn();
        break;
      case 3: 
        displayErrApi();
        break;
      }
    if (millis()-message_time >= message_duration){
      message_time = millis();
      pos = ++pos % 4;
      }
  }
  
