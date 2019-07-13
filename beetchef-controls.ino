#include "footswitch.hpp"

const uint8_t DIGITAL_PIN = 2;

//FootSwitch buttons[4];/* = {
//  FootSwitch(2)  
//};*/
FootSwitch *button1;

void setup() {
  Serial.begin(9600);
  //buttons[0] = new FootSwitch(2);

  button1 = new DigitalFootSwitch(DIGITAL_PIN);
}

void loop() {
  for(int id = 0; id < 4; id++) {
    if(button1->update()) {
      Serial.print(button1->getEvent());
      Serial.print("\n");
    }
  }

}
