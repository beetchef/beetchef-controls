#include "bc_button.hpp"

BcButton::BcButton(uint8_t pin) {

  mPin=pin;
  mCurrentPinState = false;
  mNewPressOccured = false;
  pinMode(pin, INPUT_PULLUP);
}

bool BcButton::update(void) {
  // read the state of the pin into a local variable
  bool reading = digitalRead(mPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:
  
  // If the switch changed, due to noise or pressing:
  if (reading != (mLastPinState)) { 
    // reset the debouncing timer
    mLastDebounceTime = millis();
  }

  if((millis() - mLastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    updateButtonState(reading);
  }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  mLastPinState = reading;
  return mNewPressOccured;
}

void BcButton::updateButtonState(bool updatedState) {
  if(updatedState != mCurrentPinState) { 
    // button state changed
    mCurrentPinState = updatedState;
    
    if(updatedState == HIGH) {
      // button pressed
      mNewPressOccured = true;
    }
  }
}

bool BcButton::getCurrentPinState() {
  mNewPressOccured = false;
  return mCurrentPinState;
}
