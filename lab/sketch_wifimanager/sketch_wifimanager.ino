// Author: Alberto Coppini
// date: 2020-04-11
// test libreria wifimanager. Viene testata la callback che verrà utilizzata per scrivere correttamente il testo sul led,
// inoltre viene testata la funzione di reset tramite pressione lunga del tasto. 
// Il led lampeggia fino a che riesce a collegarsi con ultime impostazioni, in tal caso si spegne oppure passa in modalità AP, in tal caso rimane acceso.

#include <FS.h>                   //this needs to be first, or it all crashes and burns...

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager

#include <Ticker.h>

#define PIN_RST_BUTTON 5

WiFiManager wifiManager;
Ticker tick;


void blinker(){
  int state = digitalRead(LED_BUILTIN);
  digitalWrite(LED_BUILTIN, !state);
  }

//gets called when WiFiManager enters configuration mode
void configModeCallback (WiFiManager *myWiFiManager) {
  tick.detach();
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(PIN_RST_BUTTON, INPUT_PULLUP);
}

void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);
  tick.attach(0.1, blinker);
   //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
 
  //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
   wifiManager.setAPCallback(configModeCallback);


  //exit after config instead of connecting
  //wifiManager.setBreakAfterConfig(true);

  //reset settings - for testing
  //wifiManager.resetSettings();

  if (!wifiManager.autoConnect("LittleMoonAP")) {
    Serial.println("failed to connect, we should reset as see if it connects");
    delay(3000);
    ESP.reset();
    delay(5000);
  }
  tick.detach();
  digitalWrite(LED_BUILTIN, HIGH);
}

unsigned long resetTimer = 0;
int           resetLongPress = false;

void checkReset(){
  int rstButton = digitalRead(PIN_RST_BUTTON);
  if (!rstButton){
    if (!resetLongPress){
      resetTimer = millis();
      resetLongPress = true;
    } else {
    // wait 3 seconds
    if (millis() - resetTimer >= 3000){
      wifiManager.resetSettings();
      delay(100);
      ESP.reset();
      }
    }
 }else{
  if (resetLongPress){
    resetTimer = 0;
    resetLongPress = false;
  }
}
  }

void loop() {

 checkReset(); 
  
}
