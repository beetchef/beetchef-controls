

#include "Arduino.h"

class BcButton {
  public:
    BcButton(uint8_t pin);
    bool update(void);
    bool getCurrentPinState();
  private:
    unsigned long mLastDebounceTime;
    static const uint8_t debounceDelay = 10;
    uint8_t mPin;
    bool mCurrentPinState;
    bool mLastPinState;
    bool mNewPressOccured;
    void updateButtonState(bool updatedState);
};
