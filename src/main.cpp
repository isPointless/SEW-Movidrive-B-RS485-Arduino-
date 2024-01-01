#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "definitions.h"
#include "sew.h"
#include "display.h"

// *** stuff *** //
// ************* //

SEW *sew;
Display *display;

//PIs
int16_t motorRPM = 0;
int16_t motor_current = 0;

//POs
int16_t setRPM = 0; //set RPM in % of max (p302). with max being 0x4000, this is how you control the motor for now.

unsigned long lastSend = 0; //start after 1s.
bool flipOver = 0;
//DEBUG 
#define DEBUG

void setup() {
  #ifdef DEBUG
  SerialUSB.begin(115200); //USB-CDC (Takes PA8,PA9,PA10,PA11)
  #endif
  display = new Display();
  sew = new SEW();

  // see sew.h for meaning of control bits. Result of bitset below is 0x06, which is the most basic 'enable' signal
  sew->controller_inhibit = false; //enable controller 
  sew->controller_rapidStop = true;
  sew->controller_stop = true;
    //       bit 3 = 0
  sew->set_ramp = false;
  sew->set_param = false;
  sew->controller_reset = false;
  sew->direction = false;
}

void loop() 
{
  // SIMPLE CHANGING RPM
  if(lastSend + 60 < millis() )  // send every sec
  { 
    lastSend = millis();
    if(flipOver == false) 
    { 
      setRPM += 100;
      if(setRPM >= 0x4000) { 
        flipOver = !flipOver;
      }
    } else 
    { 
      setRPM -= 94;
      if(setRPM < 1000) { 
        flipOver = !flipOver;
      }
    }

    // SEND NEW MSG (min time between +- 60ms)
    sew->sendSEW(1, setRPM, 0);

    #ifdef DEBUG
    // Give back over USB serial
    SerialUSB.print(" RPMo: "), SerialUSB.print(setRPM, HEX), SerialUSB.print(" RPMi: "), SerialUSB.print(sew->PI2);
    SerialUSB.print(" curr-in "), SerialUSB.println(sew->PI3),
    #endif

    //Show it on the screen
    display->printData(motorRPM, motor_current);  

    }
  // RECEIVE (continuous)
  if(sew->receiveSEW() == true) 
    { 
    #ifdef DEBUG
    SerialUSB.print("Received, delta: "), SerialUSB.print(sew->dataDiff), SerialUSB.print(" corrupted: "), SerialUSB.println(sew->corrupt_counter);
    #endif
    motorRPM = sew->PI2/5;
    motor_current = (sew->PI3*Inom)/100; // x10 
    }
  
}

