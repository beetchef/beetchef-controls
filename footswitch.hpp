#define SINGLE_PRESS "sp"
#define DOUBLE_PRESS "dp"
#define LONG_PRESS "lp"

#include "Arduino.h"

class FootSwitch {
  public:
    FootSwitch(uint8_t pin);
    bool update(void);
    String getEvent();
  protected:
    uint8_t mPin;
    unsigned long mLastDebounceTime;
    static const uint8_t mDebounceDelay = 10;
    void updateInternalStates(bool updatedSwitchState);
    bool mNewPressOccured;
  private:
    bool mLastSwitchState;
    bool mCurrentSwitchState; 
    uint8_t mPressCounter;
    unsigned long mPressTimePoint;
    unsigned long mReleaseTimePoint;
    static const uint16_t mDoublePressGap = 500;
    static const uint16_t mLongPressSpan = 500;
    String mEvent;
    virtual bool readSwitchState() = 0;
};

class DigitalFootSwitch: public FootSwitch {
  public:
    DigitalFootSwitch(uint8_t pin);
  private:
    bool readSwitchState();
};

class AnalogFootSwitch: public FootSwitch {
  public:
    AnalogFootSwitch(uint8_t pin, int minPinValue, int maxPinValue);
  private:
    int mMinPinValue;
    int mMaxPinValue;
    bool readSwitchState();
};
