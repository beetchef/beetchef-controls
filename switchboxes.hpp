#ifndef SWITCHBOXES_HPP
#define SWITCHBOXES_HPP

#define SINGLE_PRESS "single press"
#define DOUBLE_PRESS "double press"
#define LONG_PRESS "long press"

#include "Arduino.h"


struct TimingConfig{
  TimingConfig();
  TimingConfig(
    uint8_t debounceDelay,
    uint16_t doublePressGap,
    uint16_t longPressSpan):
      debounceDelay(debounceDelay),
      doublePressGap(doublePressGap),
      longPressSpan(longPressSpan){}

  ~TimingConfig();

  uint8_t debounceDelay;
  uint16_t doublePressGap;
  uint16_t longPressSpan;
};

class Switch {
  public:
    void updateRawState(int pinValue);
    void updateInternalStates(TimingConfig *timingConfig);
    bool isRawStateDebounced(TimingConfig *timingConfig);
    bool hasNewEventOccurred();
    String getEvent();
    void dismissEvent();
    virtual bool decodeRawState(int pinValue) = 0;
  private:
    bool mRawState = false;
    bool mLastDebouncedState = false;
    unsigned long mLastDebounceTime = -1;
    uint8_t mPressCounter = 0;
    unsigned long mPressTimePoint = -1;
    unsigned long mReleaseTimePoint = -1;
    bool mNewEventOccurred = false;
    String mEvent;
};

class DigitalSwitch: public Switch {
  public:
    DigitalSwitch(uint8_t inputPin);
    uint8_t getInputPin();
    bool decodeRawState(int pinValue);
  private:
    uint8_t mInputPin;
};

class AnalogSwitch: public Switch {
  public:
    AnalogSwitch(int **inputPinValueBoundPairs, uint8_t inputPinValueBoundPairCount);
    bool decodeRawState(int pinValue);
  private:
    /*  array of int pairs representing bounds for input pin
     *  value for which switch is considered pressed
     *  e.g. {{0, 100}, {300, 400}}
     */
    int **mInputPinValueBoundPairs;
    uint8_t minputPinValueBoundPairCount;
};

template<class SWITCH_TYPE>
class SwitchBox {
  public:
    SwitchBox(SWITCH_TYPE **switches, uint8_t switchCount, TimingConfig *timingConfig);
    void update();
    uint8_t getSwitchCount();
    SWITCH_TYPE **getSwitches();
  protected:
    SWITCH_TYPE **mSwitches;
    uint8_t mSwitchCount;
  private:
    TimingConfig *mTimingConfig;
    virtual void updateRawSwitchStates() = 0;
};

class DigitalSwitchBox: public SwitchBox<DigitalSwitch> {
  public:
    DigitalSwitchBox(DigitalSwitch **switches, uint8_t switchCount, TimingConfig *timingConfig);
    void updateRawSwitchStates();
};

class AnalogSwitchBox: public SwitchBox<AnalogSwitch> {
  public:
    AnalogSwitchBox(AnalogSwitch **switches, uint8_t switchCount, TimingConfig *timingConfig, uint8_t inputPin);
    void updateRawSwitchStates();
  private:
    int mInputPin;
};

#endif
