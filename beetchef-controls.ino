#include "switchboxes.hpp"

const uint8_t DIGITAL_PIN_1 = 2;
const uint8_t DIGITAL_PIN_2 = 3;
const uint8_t ANALOG_PIN = A0;
const uint8_t SWITCH_BOX_COUNT = 1;
const uint8_t MAX_SWITCH_BOXES = 4;
const uint8_t BOX1_SWITCH_COUNT = 2;
const uint8_t MAX_SWITCHES_PER_BOX = 2;

bool initialized = false;

// global variable to hold an array of all switch boxes
AbstractSwitchBox **switchBoxes;

void setup() {

  // open serial port
  Serial.begin(9600);

  if (SWITCH_BOX_COUNT > MAX_SWITCH_BOXES) {
    // TEMP: write plain message to serial port
    // TODO: send OSC message
    Serial.println("Maximum number of switch boxes exceeded!");

    // return from setup function - variable "initialized" won't get set to true
    return;
  }

  // allocate dynamic array (on heap) of pointers to abstract switch box objects of size defined by SWITCH_BOX_COUNT
  switchBoxes = new AbstractSwitchBox*[SWITCH_BOX_COUNT];

  // TEMP: create timing configuration object with following values:
  // debounceDelay = 10 ms
  // doublePressGap = 500 ms
  // longPressSpan = 500 ms
  // TODO: read this from external build config file
  TimingConfig *timingConfig = new TimingConfig(10, 500, 500);

  // TEMP: execute following block just once for boxIdx = 0
  uint8_t boxIdx = 0;
  // TODO: iterate over switch box configurations taken from external build config file
  //for (uint8_t boxIdx = 0; boxIdx < SWITCH_BOX_COUNT; boxIdx++) {

    // TEMP: set switch count to BOX1_SWITCH_COUNT
    uint8_t switchCount = BOX1_SWITCH_COUNT;
    // TODO: read switch count for given switch box from external build config file
    if (switchCount > MAX_SWITCHES_PER_BOX) {

      // TEMP: write plain message to serial port
      // TODO: send OSC message
      Serial.println("Maximum number of switches per box exceeded!");

      // return from setup function - variable "initialized" won't get set to true
      return;
    }


    ////////////////////// ANALOG SWITCH BOX INITIALIZATION //////////////////////////////////


    // allocate dynamic array (on heap) of pointers to analog switch objects of size defined by switchCount
    AnalogSwitch **switches = new AnalogSwitch*[switchCount];

    // TODO: iterate over switch configurations taken from exernal build config file
    //for (uint8_t switchIdx = 0; switchIdx < switchCount; switchIdx++) {

      // TEMP: create 2 analog switches and store their pointers as first 2 elements of switches array
      // TODO: initialize just given switch from external build config using switchIdx
      switches[0] = new AnalogSwitch(new int*[2]{ new int[2]{0, 100}, new int[2]{200, 300}}, 2);
      switches[1] = new AnalogSwitch(new int*[2]{ new int[2]{0, 100}, new int[2]{300, 400}}, 2);
    //}

    // create new analog switch box and store it to array of switch boxes at given index
    switchBoxes[boxIdx] = new AnalogSwitchBox(switches, switchCount, timingConfig, ANALOG_PIN);



    /*
    ////////////////////////  DIGITAL SWITCH BOX INITIALIZATION //////////////////////////////////


    // allocate dynamic array (on heap) of pointers to digital switch objects of size defined by switchCount
    DigitalSwitch **switches = new DigitalSwitch*[switchCount];

    // TODO: iterate over switch configurations taken from exernal build config file
    //for (uint8_t switchIdx = 0; switchIdx < switchCount; switchIdx++) {

      // TEMP: create 2 digital switches and store their pointers as first 2 elements of switches array
      // TODO: initialize just given switch from external build config using switchIdx
      switches[0] = new DigitalSwitch(DIGITAL_PIN_1);
      switches[1] = new DigitalSwitch(DIGITAL_PIN_2);
    //}

    // create new digital switch box and store it to array of switch boxes at given index
    switchBoxes[boxIdx] = new DigitalSwitchBox(switches, switchCount, timingConfig);
     */

  //}

  // after successful initialization set variable "initialized" to true
  initialized = true;
  // TODO: send OSC message
}


void loop() {

  if (initialized) {

    // iterate over all switchboxes
    for (uint8_t boxIdx = 0; boxIdx < SWITCH_BOX_COUNT; boxIdx++) {

      // update given switchbox
      switchBoxes[boxIdx]->update();

      // iterate over switches for given switch box
      for (uint8_t switchIdx = 0; switchIdx < switchBoxes[boxIdx]->getSwitchCount(); switchIdx++) {

        // if a new event occurred for given switch
        if (switchBoxes[boxIdx]->getSwitch(switchIdx)->hasNewEventOccurred()) {

          // TEMP: print it to serial port
          // TODO: send OSC message
          char label[22];
          sprintf(label, "[box %d][switch %d]: ", boxIdx, switchIdx);
          Serial.print(label);
          Serial.println(switchBoxes[boxIdx]->getSwitch(switchIdx)->getEvent());

          // dismiss event
          switchBoxes[boxIdx]->getSwitch(switchIdx)->dismissEvent();
        }
      }
    }
  }
}
