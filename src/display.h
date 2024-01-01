#pragma once

class Adafruit_SSD1306;

class Display{
  private:
    Adafruit_SSD1306* display;

  public:
    Display();
    void printData(uint16_t rpm, uint16_t ampere);
    void off(); 
};