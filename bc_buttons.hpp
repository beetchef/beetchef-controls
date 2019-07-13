#define SINGLE_PRESS "sp"
#define DOUBLE_PRESS "dp"
#define LONG_PRESS "lp"

#include "Arduino.h"

class BcButton {
  public:
    BcButton(uint8_t pin);
    bool update(void);
    String getEvent();
  private:
    uint8_t mPin;
    uint8_t mPressCounter;
    unsigned long mPressTimePoint;
    unsigned long mReleaseTimePoint;
    unsigned long mLastDebounceTime;
    static const uint16_t mDoublePressGap = 500;
    static const uint16_t mLongPressSpan = 500;
    static const uint8_t mDebounceDelay = 10;
    bool mCurrentPinState;
    bool mLastPinState;
    bool mNewPressOccured;
    void updateButtonState(bool updatedPinState);
    String mEvent;
};
