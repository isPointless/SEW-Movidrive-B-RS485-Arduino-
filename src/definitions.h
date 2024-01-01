#define DISPLAY_ADDR 0x3C // I2C Address - use 0x3C or 0x3D depending on your display -- Display connects A4 A5

#define RS485DE      PA6     // This is both RE and DE together (high = TX)

/*
STM32F411	SSD1306 I2C OLED
----------------------------
3V3			VCC
GND			GND
B7			SDA
B6			SCL
*/

//Pinout for RS485 Serial2 PA2(TX) & PA3(RX)

#define Inom 7.3



