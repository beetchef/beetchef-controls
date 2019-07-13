#include "switchboxes.hpp"

const uint8_t DIGITAL_PIN = 2;
const uint8_t ANALOG_PIN = A0;
const int SWITCH_COUNT = 3;
SwitchBox *buttons[SWITCH_COUNT] = {
  new AnalogSwitchBox(ANALOG_PIN, 0, 100),
  new AnalogSwitchBox(ANALOG_PIN, 200, 300),
  new AnalogSwitchBox(ANALOG_PIN, 300, 400)
};
SwitchBox *button1;

void setup() {
  Serial.begin(9600);
  //buttons[0] = new SwitchBox(2);
//  button1 = new DigitalSwitchBox(DIGITAL_PIN);
    //button1 = new AnalogSwitchBox(ANALOG_PIN, 200, 300);
}


void loop() {
  for(int id = 0; id < SWITCH_COUNT; id++) {
    if(buttons[id]->update()) {
      Serial.print("[switch ");
      switch (id) {
        case 0:
          Serial.print("jeden + dva");
          break;
        case 1:
          Serial.print("jeden");
          break;
        case 2:
          Serial.print("dva");
          break;
        default:
          break;
      }
      Serial.print("]:");
      Serial.print(buttons[id]->getEvent());
      Serial.print("\n");
    }
  }

}
