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

  if((millis() - mLastDebounceTime) > mDebounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    updateButtonState(reading);
  }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  mLastPinState = reading;
  return mNewPressOccured;
}

void BcButton::updateButtonState(bool updatedPinState) {
  if(mPressCounter == 1 && millis() - mReleaseTimePoint > mDoublePressGap) {
    // too much time has passed since last button press -> double press won't be generated -> reset counter
    mPressCounter = 0;
  }
  if(updatedPinState != mCurrentPinState) {
    // button state changed
    mCurrentPinState = updatedPinState;
    if(updatedPinState == HIGH) {
      // button pressed
      if(mPressCounter == 0) {
        mPressTimePoint = millis();
      }
      if(mPressCounter == 1) {
        // double press
        mNewPressOccured = true;
        mEvent = DOUBLE_PRESS;
        mPressCounter = 0;
      }
    } else {
      //button released
      if(mPressCounter == 0 & mPressTimePoint != -1 & millis() - mPressTimePoint < mLongPressSpan) {
        //single press
        mNewPressOccured = true;
        mEvent = SINGLE_PRESS;
        mPressCounter++;
        mPressTimePoint = -1;
        mReleaseTimePoint = millis();
      }
    }
  } else {
    //button state remains
    if(updatedPinState == HIGH & mPressTimePoint != -1 & millis() - mPressTimePoint >= mLongPressSpan) {
      //button is pressed long enough to generate long press event
      mNewPressOccured = true;
      mEvent = LONG_PRESS;
      mPressTimePoint = -1;
    }
  }
}

String BcButton::getEvent() {
  mNewPressOccured = false;
  return mEvent;
}
