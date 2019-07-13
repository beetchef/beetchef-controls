

#include "Arduino.h"

class BcButton {
  public:
    BcButton(uint8_t pin);
    bool update(void);
    bool getCurrentPinState();
  private:
    unsigned long lastDebounceTime;
    static const uint8_t debounceDelay = 10;
    uint8_t pin;
 /*   uint8_t valueLowerBound;
    uint8_t valueUpperBound;*/
    bool currentPinState;
    bool lastPinState;
    bool newPressOccured;
    void updateButtonState(bool updatedState);
};
