first of all install library LedControl by Eberhard Fahle

used methods: 
- init: LedControl lc = LedControl (PIN_MAX7219_DIN, PIN_MAX7219_CLK, PIN_MAX7219_CS, 1);
- lc.shutdown(0, false);
- lc.setIntensity(0, 5);
- lc.clearDisplay(0); 
- lc.setRow(0, row, MOON_PHASES[i][row]);