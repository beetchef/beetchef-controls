#include "switchboxes.hpp"


/**********
 * SWITCH *
 **********/

void Switch::updateRawState(int pinValue) {

  // decode raw switch state from pin value
  bool newRawState = decodeRawState(pinValue);

  // if raw state changed compared to previous raw state (due to noise or pressing)
  if (newRawState != mRawState) {

    // reset the debouncing timer
    mLastDebounceTime = millis();
  }

  // update raw state for the switch with the new raw state
  mRawState = newRawState;
}

void Switch::updateInternalStates(TimingConfig *timingConfig) {

  if(mPressCounter == 1 && millis() - mReleaseTimePoint > timingConfig->doublePressGap) {

    // too much time has passed since last button press -> double press won't be generated -> reset counter
    mPressCounter = 0;
  }


  // NOTE: when updateInternalStates method is called mRawState is supposed to be already debounced
  // if debounced state changed compared to last debounce state
  if(mRawState != mLastDebouncedState) {

    // set current debounced state as last debounced state
    mLastDebouncedState = mRawState;

    // if switch has been pressed
    if(mRawState == HIGH) {

      // if it's the first switch press
      if(mPressCounter == 0) {

        // set press time point
        mPressTimePoint = millis();
      }

      // if it's second switch press
      if(mPressCounter == 1) {

        // generate double press event
        mNewEventOccurred = true;
        mEvent = DOUBLE_PRESS;

        // reset press counter
        mPressCounter = 0;
      }

    // if switch has been released
    } else {

      // if it was the first switch press
      if(mPressCounter == 0 && mPressTimePoint != -1 && millis() - mPressTimePoint < timingConfig->longPressSpan) {

        // generate single press event
        mNewEventOccurred = true;
        mEvent = SINGLE_PRESS;

        // reset counter and press time point
        mPressCounter++;
        mPressTimePoint = -1;

        // set release time point
        mReleaseTimePoint = millis();
      }
    }

  // if debounced state remains the same compared to last debounced state
  } else {

    // if the switch is currently pressed, press time point is set and it exceeds long press span
    // i.e. the switch is pressed long enoungh to generate long press event
    if(mRawState == HIGH && mPressTimePoint != -1 && millis() - mPressTimePoint >= timingConfig->longPressSpan) {

      // generate long press event
      mNewEventOccurred = true;
      mEvent = LONG_PRESS;

      // reset press time point
      mPressTimePoint = -1;
    }
  }
}

bool Switch::isRawStateDebounced(TimingConfig *timingConfig) {

  // whatever the raw state is at, it's been there for longer
  // than the debounce delay, so take it as the actual current state
  return millis() - mLastDebounceTime > timingConfig->debounceDelay;
}

bool Switch::hasNewEventOccurred() {
  return mNewEventOccurred;
}

String Switch::getEvent() {
  return mEvent;
}

void Switch::dismissEvent() {
  mNewEventOccurred = false;
}


/******************
 * DIGITAL SWITCH *
 ******************/

DigitalSwitch::DigitalSwitch(uint8_t inputPin) {
  this->mInputPin = inputPin;
}

uint8_t DigitalSwitch::getInputPin() {
  return this->mInputPin;
}

bool DigitalSwitch::decodeRawState(int pinValue) {
  // simply return true when pin value is high and false otherwise
  return pinValue == HIGH;
}


/*****************
 * ANALOG SWITCH *
 *****************/

AnalogSwitch::AnalogSwitch(int **inputPinValueBoundPairs, uint8_t inputPinValueBoundPairCount) {
  this->mInputPinValueBoundPairs = inputPinValueBoundPairs;
  this->minputPinValueBoundPairCount = inputPinValueBoundPairCount;
}

bool AnalogSwitch::decodeRawState(int pinValue) {

  for (uint8_t i = 0; i < minputPinValueBoundPairCount; i++) {

    // if pin value falls into given value bound pair
    if (pinValue >= mInputPinValueBoundPairs[i][0] && pinValue <= mInputPinValueBoundPairs[i][1]) {

      return true;
    }
  }

  // pin value does not fall into any of value bound pairs, return false
  return false;
}


/**************
 * SWITCH BOX *
 **************/

template<class SWITCH_TYPE>
SwitchBox<SWITCH_TYPE>::SwitchBox(SWITCH_TYPE **switches, uint8_t switchCount, TimingConfig *timingConfig) {
  this->mSwitches = switches;
  this->mSwitchCount = switchCount;
  this->mTimingConfig = timingConfig;
}

template<class SWITCH_TYPE>
void SwitchBox<SWITCH_TYPE>::update() {

  // update raw switch states (not necessarily debounced states)
  updateRawSwitchStates();

  // iterate over all switches
  for (uint8_t i = 0; i < getSwitchCount(); i++) {

    // if raw state for given switch is debounced (i.e. noise is eliminated)
    if (mSwitches[i]->isRawStateDebounced(mTimingConfig)) {

      // update internal states for given switch
      mSwitches[i]->updateInternalStates(mTimingConfig);

      // NOTE: Execution of this doesn't mean that debounced state has changed since the last update.
      // Updating internal states is necessary when debounce state hasn't changed as well.
      // e.g. counting elapsed time for long press
    }
  }
}

template<class SWITCH_TYPE>
uint8_t SwitchBox<SWITCH_TYPE>::getSwitchCount() {
  return mSwitchCount;
}

template<class SWITCH_TYPE>
Switch *SwitchBox<SWITCH_TYPE>::getSwitch(uint8_t switchIdx) {
  return mSwitches[switchIdx];
}


/**********************
 * DIGITAL SWITCH BOX *
 **********************/

DigitalSwitchBox::DigitalSwitchBox(DigitalSwitch **switches, uint8_t switchCount, TimingConfig *timingConfig): SwitchBox(switches, switchCount, timingConfig) {
  for (uint8_t i = 0; i < switchCount; i++) {
    pinMode(switches[i]->getInputPin(), INPUT_PULLUP);
  }
}

void DigitalSwitchBox::updateRawSwitchStates() {

  // iterate over all switches
  for (uint8_t i = 0; i < mSwitchCount; i++) {

    // read value from digital pin for given switch and update raw state using it
    mSwitches[i]->updateRawState(digitalRead(mSwitches[i]->getInputPin()));
    // comment out the line above and uncomment the line below if physical switch is producing reversed values (i.e. 0 instead of 1 and vice versa)
    //mSwitches[i]->updateRawState(!digitalRead(mSwitches[i]->getInputPin()));
  }
}


/*********************
 * ANALOG SWITCH BOX *
 *********************/

AnalogSwitchBox::AnalogSwitchBox(AnalogSwitch **switches, uint8_t switchCount, TimingConfig *timingConfig, uint8_t inputPin) : SwitchBox(switches, switchCount, timingConfig) {
  this->mInputPin = inputPin;
  pinMode(this->mInputPin, INPUT_PULLUP);
}

void AnalogSwitchBox::updateRawSwitchStates() {

  // read value from analog input pin for this switchbox (input pin is shared by all switches)
  int pinValue = analogRead(mInputPin);

  // iterate over all switches
  for (uint8_t i = 0; i < mSwitchCount; i++) {

    // update raw state for given switch using the value from input pin
    mSwitches[i]->updateRawState(pinValue);
  }
}

// this fixes linker error during compilation
template class SwitchBox<AnalogSwitch>;
