#include "definitions.h"
#include <Arduino.h>
#include "display.h"
#include <Wire.h>
#include <SPI.h>
#include "ssd1306.h"
#include "nano_gfx.h"

Display::Display() {
  ssd1306_128x64_i2c_init();
  ssd1306_clearScreen();
}

void Display::printData(uint16_t rpm, uint16_t ampere) { 


    ssd1306_128x64_i2c_init();
    ssd1306_fillScreen(0x00);
    ssd1306_setFixedFont(courier_new_font11x16_digits);

 
    char showRpm[4];
    itoa(rpm, showRpm, 10);
    ssd1306_printFixed(40,10, showRpm, STYLE_NORMAL);

    char showAmp[4];
    itoa(ampere, showAmp, 10);
    ssd1306_printFixed(40,30, showAmp, STYLE_NORMAL);

    ssd1306_setFixedFont(ssd1306xled_font8x16);

    ssd1306_printFixed(4, 30, "CURi", STYLE_NORMAL);
    ssd1306_printFixed(4, 10, "RPMi", STYLE_NORMAL);
}


void Display::off() { 
    ssd1306_clearScreen();
    ssd1306_displayOff();
}
