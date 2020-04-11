#include <ESP8266WiFi.h>
#include <time.h>                       // time() ctime()
#include <sys/time.h>                   // struct timeval
#include <FS.h>                   //this needs to be first, or it all crashes and burns...

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager

time_t now;
struct tm localTime;

void setup() {
  Serial.begin(115200);
  WiFiManager wifiManager;
  
  
  if (!wifiManager.autoConnect("LittleMoonAP")) {
    Serial.println("failed to connect, we should reset as see if it connects");
    delay(3000);
    ESP.reset();
    delay(5000);
  }

 configTime(0, 0, "time.google.com", "time.windows.com", "pool.ntp.org");
 
  // https://github.com/nayarsystems/posix_tz_db/blob/master/zones.json  
  setenv("TZ", "CET-1CEST,M3.5.0,M10.5.0/3", 1);
  tzset();
 
  now = time(nullptr);    
  localTime = *localtime(&now);  
 
  
}

void loop() {
  static uint32_t updateTime;
  if(millis() - updateTime > 1000){
    updateTime = millis();
   
    // Aggiorno la variabile now
    now = time(nullptr);  
    // e la struttura localTime con il valore di now
    localTime = *localtime(&now);
    // La struttura localTime ora contiene il dateTime aggiornato
 
    // Ora stampiamo sulla seriale la data aggiornata    
    char buf[30];
    strftime(buf, sizeof(buf), "\n %d/%m/%Y - %H:%M:%S", &localTime);    
    Serial.println(buf);    
 
    snprintf(buf, 30, "\n Ora legale: %s", localTime.tm_isdst ? "SI" : "NO");
    Serial.println(buf);  
   
 
 
    /* localTime è una struttura di tipo tm definita in questo modo nel file time.h
       struct tm
        {
          int  tm_sec;
          int tm_min;
          int tm_hour;
          int tm_mday;
          int tm_mon;
          int tm_year;
          int tm_wday;
          int tm_yday;
          int tm_isdst;
        #ifdef __TM_GMTOFF
          long  __TM_GMTOFF;
        #endif
        #ifdef __TM_ZONE
          const char *__TM_ZONE;
        #endif
        };
     */
   
    // E' ovviamente possibile estrarre ogni singola informazione di cui abbiamo bisogno
    /*
     int Year = localTime.tm_year;  
     int Month = localTime.tm_mon;
     int Day = localTime.tm_mday;
     int Hour = localTime.tm_hour;
     int Min = localTime.tm_min;
     int Sec = localTime.tm_sec;    
     */    
  }
}
