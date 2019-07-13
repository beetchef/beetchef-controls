#define SINGLE_PRESS "sp"
#define DOUBLE_PRESS "dp"
#define LONG_PRESS "lp"

#include "Arduino.h"

class SwitchBox {
  public:
    SwitchBox();
    bool update(void);
    String getEvent();
  protected:
    static const uint8_t mSwitchCount = 2;
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

class DigitalSwitchBox: public SwitchBox {
  public:
    DigitalSwitchBox(uint8_t switch1Pin, uint8_t switch2Pin);
  private:
    uint8_t mSwitchPins[mSwitchCount];
    bool readSwitchState();
};

class AnalogSwitchBox: public SwitchBox {
  public:
    AnalogSwitchBox(uint8_t inputPin, int minPinValue, int maxPinValue);
  private:
    int mInputPin;
    int mMinPinValue;
    int mMaxPinValue;
    bool readSwitchState();
};
