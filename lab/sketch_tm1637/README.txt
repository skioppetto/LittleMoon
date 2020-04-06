Avishay Orpaz has written an excellent library for TM1637 displays, the TM1637Display library. This library has several built-in functions that make controlling the display fairly easy.

The main functions include:

setSegments() – Set the raw value of the segments of each digit
showNumberDec() – Display a decimal number
showNumberDecEx() – Display a decimal number with decimal points or colon
setBrightness() – Set the brightness of the display
clear() – Clear the display

You can search for ‘tm1637’ and look for the library by Avishay Orpaz. Select the latest version and then click Install.

// You can set the individual segments per digit to spell words or create other symbols:
const uint8_t done[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};
