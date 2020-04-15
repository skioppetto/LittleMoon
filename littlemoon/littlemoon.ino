/*
  littlemoon firmware - Utility library for LittleMoon project.
  Created by A. Coppini, April 12, 2020.
*/
#include "moon_phases.h"
/*display TM1637 - directives*/
#include <TM1637Display.h>
#include <Ticker.h>
#define PIN_TM1637_CLK 0
#define PIN_TM1637_DIO 4
/*matrix led MAX7219 - directives*/
#include <LedControl.h>
#include "max7219_moon_phases.h"
#define PIN_MAX7219_CLK 13
#define PIN_MAX7219_CS  12
#define PIN_MAX7219_DIN 14
/*reset button - directives*/
#define PIN_RST_BUTTON 5
/*configTime - directives*/
#include <time.h>                       // time() ctime()
#include <sys/time.h>                   // struct timeval
/*wifiManager - directives*/
#include <FS.h>                         // this needs to be first, or it all crashes and burns...
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
/*display TM1637 - global variables*/
TM1637Display   display   = TM1637Display(PIN_TM1637_CLK, PIN_TM1637_DIO);
Ticker          display_blinker;
uint8_t         conn[]    = {SEG_G | SEG_E | SEG_D, SEG_G | SEG_E | SEG_D | SEG_C, SEG_G | SEG_E | SEG_C, SEG_G | SEG_E | SEG_C };
uint8_t         conf[]    = {SEG_G | SEG_E | SEG_D, SEG_G | SEG_E | SEG_D | SEG_C, SEG_G | SEG_E | SEG_C, SEG_E | SEG_F | SEG_G | SEG_A};
uint8_t         eapi[]    = {SEG_D | SEG_E | SEG_G | SEG_F | SEG_A, SEG_D | SEG_E | SEG_G | SEG_A | SEG_B | SEG_C, SEG_E | SEG_G | SEG_A | SEG_B | SEG_F, SEG_E | SEG_A};
uint8_t         econ[]    = {SEG_D | SEG_E | SEG_G | SEG_F | SEG_A, SEG_G | SEG_E | SEG_D, SEG_G | SEG_E | SEG_D | SEG_C, SEG_G | SEG_E | SEG_C};
uint8_t         empty[]   = {0x00, 0x00, 0x00, 0x00};
const int       DISPLAY_EMPTY = 0;
const int       DISPLAY_CONN = 1;
const int       DISPLAY_CONF = 2;
const int       DISPLAY_EAPI = 3;
const int       DISPLAY_ECON = 4;
const double    DISPLAY_BLINK_INTERVAL_S = 0.3;
int             display_set = 0;
unsigned long   display_time = 0;
int             display_empty = false;
/*matrix led MAX7219 - global variables*/
const int MATRIX_ELEMENTS = 1;
const int MATRIX_ROWS = 8;
LedControl matrix = LedControl (PIN_MAX7219_DIN, PIN_MAX7219_CLK, PIN_MAX7219_CS, MATRIX_ELEMENTS);
/*reset button - global variables*/
unsigned long resetBtnTimer = 0;
int           resetBtnLongPress = false;
const int     RESETBTN_TIMEOUT_MS = 3000;
/*configTime - global variables*/
time_t configTime_now;
struct tm configTime_localTime;
unsigned long configTime_update;
/*wifiManager - global variables*/
WiFiManager wifiManager;
/*display TM1637 - methods*/
void display_blink(uint8_t data[]) {
  if (display_empty) {
    display.setSegments(data);
  } else {
    display.setSegments(empty);
  }
  display_empty = !display_empty;
}
void displayEmpty() {
    display_blinker.detach();
    display.setSegments(empty);
    display_set = DISPLAY_EMPTY;
}
void displayConn() {
  if (display_set != DISPLAY_CONN) {
    display_blinker.detach();
    display.setSegments(conn);
    display_set = DISPLAY_CONN;
  }
}
void displayConf() {
  if (display_set != DISPLAY_CONF) {
    display_blinker.detach();
    display_blinker.attach(DISPLAY_BLINK_INTERVAL_S, display_blink, conf);
    display_set = DISPLAY_CONF;
  }
}
void displayErrApi() {
  if (display_set != DISPLAY_EAPI) {
    display_blinker.detach();
    display_blinker.attach(DISPLAY_BLINK_INTERVAL_S, display_blink, eapi);
    display_set = DISPLAY_EAPI;
  }
}
void displayErrConn() {
  if (display_set != DISPLAY_ECON) {
    display_blinker.detach();
    display_blinker.attach(DISPLAY_BLINK_INTERVAL_S, display_blink, econ);
    display_set = DISPLAY_ECON;
  }
}
void displaySetup() {
  display.clear();
  display.setBrightness(5);
}
/*matrix led MAX7219 - methods*/
void matrixShowMoon(int i) {
  matrix.clearDisplay(0);
  for (int row = 0; row < MATRIX_ROWS; row++) {
    matrix.setRow(0, row, MATRIX_MOON_PHASES[i][row]);
  }
}
void matrixSetup() {
  matrix.shutdown(0, false);
  matrix.setIntensity(0, 5);
  matrix.clearDisplay(0);
}
/*reset button - methods*/
int resetBtnCheck() {
  int resetBtn = digitalRead(PIN_RST_BUTTON);
  if (!resetBtn) {
    if (!resetBtnLongPress) {
      resetBtnTimer = millis();
      resetBtnLongPress = true;
    } else {
      // wait 3 seconds
      if (millis() - resetBtnTimer >= RESETBTN_TIMEOUT_MS) {
        return true;
      }
    }
  } else {
    if (resetBtnLongPress) {
      resetBtnTimer = 0;
      resetBtnLongPress = false;
    }
  }
  return false;
}

/*configTime - methods*/
void configTimeUpdate() {
  configTime_now = time(nullptr);
  configTime_localTime = *localtime(&configTime_now);
}
void configTimeSetup() {
  configTime(0, 0, "time.google.com", "time.windows.com", "pool.ntp.org");
  setenv("TZ", "CET-1CEST,M3.5.0,M10.5.0/3", 1); // https://github.com/nayarsystems/posix_tz_db/blob/master/zones.json
  tzset();
  delay(1000);
  configTimeUpdate();
}
int configTimeUpdateCheck() {
  if (millis() - configTime_update > 1000) {
    configTime_update = millis();
    configTimeUpdate();
    return true;
  }
  return false;
}
/*wifiManager - methods*/
void wifiManagerSetup() {
  wifiManager.setAPCallback(configModeCallback);
}
void wifiManagerConnect() {
  displayConn();
  if (!wifiManager.autoConnect("LittleMoonAP")) {
    delay(3000);
    ESP.reset();
    delay(5000);
  }
  displayEmpty();
}
Ticker moon_ticker;
void moonUpdate() {
  int year = configTime_localTime.tm_year;
  int mon = configTime_localTime.tm_mon + 1;
  int day = configTime_localTime.tm_mday;
  int phase = getMoonPhase(year, mon, day);
  int matrixPhase;
  // crescent moon
  if (phase >= 1 && phase <= 14) {
    matrixPhase = map(phase, 1, 14, 1, 5);
  }
  // waning moon
  else if (phase >= 16 && phase <= 29) {
    matrixPhase = map(phase, 16, 29, 7, 11);
  }
  else {
    // new/full moon
    matrixPhase = phase;
  }
  matrixShowMoon(matrixPhase);
}

//gets called when WiFiManager enters configuration mode
void configModeCallback (WiFiManager *myWiFiManager) {
  displayConf();
}
// sketch
void setup() {
  pinMode(PIN_RST_BUTTON, INPUT_PULLUP);
  matrixSetup();
  displaySetup();
  wifiManagerSetup();
  wifiManagerConnect();
  configTimeSetup();
  moonUpdate();
  moon_ticker.attach(3600, moonUpdate);
}

void loop() {
  static int colon_visible = false;
  static unsigned long colon_timeout = 0;

  if (resetBtnCheck()) {
    wifiManager.resetSettings();
    delay(100);
    ESP.reset();
  }

  configTimeUpdateCheck();
  if (millis() - colon_timeout >= 1000) {
    colon_timeout = millis();
    colon_visible = !colon_visible;
    int hour = configTime_localTime.tm_hour;
    int minute = configTime_localTime.tm_min;
    if (colon_visible) {
      display.showNumberDecEx(hour * 100 + minute, 0b11100000, true);
    } else {
      display.showNumberDec(hour * 100 + minute, true);
    }
  }
}
