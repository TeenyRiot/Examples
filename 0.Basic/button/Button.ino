#include "bounce.h"

// constants won't change. Used here to set a pin number :
//int ledState = LOW;             // ledState used to set the LED
//unsigned long previousMillis = 0;        // will store last time LED was updated
//int interval = 1000;           // interval at which to blink (milliseconds)

button_state ledTog;

void cbledTogOnClick(void * state)
{
//  interval = interval - 100;
 digitalWrite(PB4, !btn_get_toggle((button_state*)state)); 
}
 
void setup() {
  pinMode(PB4, OUTPUT);
  btn_setup(&ledTog, PB2, cbledTogOnClick);
}

void loop() {
  
  /*
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;   
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;
    digitalWrite(PB4, ledState);
  }
  */
  
  btn_update_reading(&ledTog);
}
