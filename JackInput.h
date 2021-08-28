#ifndef JackInput_h
#define JackInput_h

#include "Arduino.h"

class JackInput {

  public:
    JackInput(uint8_t pin) {
      _pin = pin;
      pinMode(_pin, INPUT);
      lastState = LOW;
    };
    int state() {
      int currentState = digitalRead(_pin);
      if (lastState == LOW && currentState == HIGH) {
        lastState = currentState;
        return 1;
      }
      else if (lastState == HIGH && currentState == LOW) {
        lastState = currentState;
        return - 1;
      }
      lastState = currentState;
      if (currentState == HIGH) {
        return 2;
      }
      else
        return - 2;
    };
  private:
    uint8_t _pin;
    bool lastState;
};


#endif
