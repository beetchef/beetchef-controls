#include "bc_button.hpp"

BcButton::BcButton(uint8_t pin)/*: pin(pin), valueLowerBound(valueLowerBound), valueUpperBound(valueUpperBound)*/ {

  this->pin=pin;
  /*this->valueLowerBound=valueLowerBound;
  this->valueUpperBound=valueUpperBound;*/
  this->currentPinState = false;
  this->newPressOccured = false;
  pinMode(pin, INPUT_PULLUP);
}

bool BcButton::update(void) {
  // read the state of the pin into a local variable:
  //uint8_t reading = digitalRead(pin);
  bool reading = digitalRead(pin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:
  
  // If the switch changed, due to noise or pressing:
  if (reading != (this->lastPinState)) { 
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    updateButtonState(reading);
  }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastPinState = reading;
  return newPressOccured;
}

void BcButton::updateButtonState(bool updatedState) {
  if(updatedState != this->currentPinState) { 
    // button state changed
    this->currentPinState = updatedState;
    
    if(updatedState == HIGH) {
      // button pressed
      newPressOccured = true;
    }
  }
}

bool BcButton::getCurrentPinState() {
  this->newPressOccured = false;
  return this->currentPinState;
}
