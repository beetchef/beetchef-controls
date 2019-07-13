#include "switchboxes.hpp"

SwitchBox::SwitchBox() {
  this->mCurrentSwitchState = false;
  this->mNewPressOccured = false;
}

bool SwitchBox::update(void) {
  // read the state of the pin into a local variable
  bool reading = readSwitchState();

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:
  
  // If the switch changed, due to noise or pressing:
  if (reading != (mLastSwitchState)) {
    // reset the debouncing timer
    mLastDebounceTime = millis();
  }

  if((millis() - mLastDebounceTime) > mDebounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    updateInternalStates(reading);
  }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  mLastSwitchState = reading;
  return mNewPressOccured;
}

void SwitchBox::updateInternalStates(bool updatedSwitchState) {
  if(mPressCounter == 1 && millis() - mReleaseTimePoint > mDoublePressGap) {
    // too much time has passed since last button press -> double press won't be generated -> reset counter
    mPressCounter = 0;
  }
  if(updatedSwitchState != mCurrentSwitchState) {
    // button state changed
    mCurrentSwitchState = updatedSwitchState;
    if(updatedSwitchState == HIGH) {
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
    if(updatedSwitchState == HIGH & mPressTimePoint != -1 & millis() - mPressTimePoint >= mLongPressSpan) {
      //button is pressed long enough to generate long press event
      mNewPressOccured = true;
      mEvent = LONG_PRESS;
      mPressTimePoint = -1;
    }
  }
}

String SwitchBox::getEvent() {
  mNewPressOccured = false;
  return mEvent;
}

DigitalSwitchBox::DigitalSwitchBox(uint8_t switch1Pin, uint8_t switch2Pin): SwitchBox() {
  this->mSwitchPins[0] = switch1Pin;
  this->mSwitchPins[1] = switch2Pin;
  pinMode(this->mSwitchPins[0], INPUT_PULLUP);
  pinMode(this->mSwitchPins[1], INPUT_PULLUP);
}

bool DigitalSwitchBox::readSwitchState() {
  return digitalRead(mSwitchPins[0]);
}

AnalogSwitchBox::AnalogSwitchBox(uint8_t inputPin, int minPinValue, int maxPinValue): SwitchBox() {
  this->mMinPinValue = minPinValue;
  this->mMaxPinValue = maxPinValue;
  this->mInputPin = inputPin;
  pinMode(this->mInputPin, INPUT_PULLUP);
}

bool AnalogSwitchBox::readSwitchState() {
  int pinValue = analogRead(mInputPin);
  //Serial.print(pinValue);
  //Serial.print("\n");
  return pinValue >= mMinPinValue && pinValue <= mMaxPinValue;
}
