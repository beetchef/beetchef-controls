#include "bc_button.hpp"

const uint8_t DIGITAL_PIN = 2;

//BcButton buttons[4];/* = {
//  BcButton(2)  
//};*/
BcButton *button1;

void setup() {
  Serial.begin(9600);
  //buttons[0] = new BcButton(2);

  button1 = new BcButton(DIGITAL_PIN);
}

void loop() {
  for(int id = 0; id < 4; id++) {
    if(button1->update()) {
      Serial.print(button1->getEvent());
      Serial.print("\n");
    }
  }

}
