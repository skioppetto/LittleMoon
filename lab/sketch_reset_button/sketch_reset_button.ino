// author: Alberto Coppini
// date: 2020-04-06
// il test è effettuato per verificare corretta funzione di GPIO5 in modalità INPUT_PULLUP
// verifica quindi sul LED BUILTIN che inizialmente il valore dell'ingresso 
// sia alto e alla pressione del tasto RESET si porti sullo stato LOW spegnendo cosi il LED,
// al rilascio il LED dovrà tornare ad accendersi

#define PIN_RST_BUTTON 5

int rstButton = LOW;
void setup() {
  Serial.begin(9600);
  pinMode(PIN_RST_BUTTON, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(50);
  rstButton = digitalRead(PIN_RST_BUTTON);
  // il led dovrebbe essere accesso all'avvio
  digitalWrite(LED_BUILTIN, !rstButton); 
  
}

void loop() {
  
  rstButton = digitalRead(PIN_RST_BUTTON);
  Serial.println(rstButton);
  // il led dovrebbe spegnersi solo durante la pressione
  digitalWrite(LED_BUILTIN, !rstButton);
}
