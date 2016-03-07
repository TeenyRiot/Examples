#include "Arduino.h"

#define DEBOUNCE_DELAY 60

typedef struct {
  uint8_t pin_btn;
  uint8_t btn_states; //state array
  uint8_t debounce; //debounce timer
  void (*click_cb)(void*) ;
} button_state;


void btn_setup(button_state * state, uint8_t pin,void (*click_cb)(void*))
{
  state->debounce = 255;
  state->btn_states = 0;
  state->pin_btn = pin;
  state->click_cb = click_cb;

  //  if (pullup)
  //  {
  pinMode(pin, INPUT);
  digitalWrite(pin, HIGH);
  //  }else{
  //      pinMode(pin, INPUT);
  //  }
}

uint8_t btn_get_toggle(button_state * state)
{
  return (state->btn_states >> 4) & 1;
}

void btn_update_reading(button_state * state)
{
  if (digitalRead(state->pin_btn))
  {
    state->btn_states &= ~(1 << 7);
  } else {
    state->btn_states |= (1 << 7);
  }
  
  //btn pressed from 0 to 1
  if ( ((state->btn_states >> 7) & 1) != ((state->btn_states >> 6) & 1) && ((state->btn_states >> 7) & 1) )
  {
    state->debounce = 255;
  }

  if (state->debounce <= DEBOUNCE_DELAY)
  {

    //btn prev and now is diffrernt
    if (((state->btn_states >> 7) & 1) != ((state->btn_states >> 5) & 1)) {

      if ((state->btn_states >> 7) & 1)
      {
        state->btn_states |= (1 << 5);
      } else {
        state->btn_states &= ~(1 << 5);
      }
      
      //btn now is 1 (from 0 to 1)
      if (((state->btn_states >> 5) & 1) == HIGH) {
        //state->toggle = !state->toggle;
        if ((state->btn_states >> 4) & 1)
        {
          state->btn_states &= ~(1 << 4);
        } else {
          state->btn_states |= (1 << 4);
        }
        
        state->click_cb(state);
        
      }
      
      
    }

  }

  state->debounce--;

  if ( (state->btn_states >> 7)  == 1)
  {
    state->btn_states |= (1 << 6);
  } else {
    state->btn_states &= ~(1 << 6);
  }
}

