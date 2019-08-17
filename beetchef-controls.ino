#include "switchboxes.hpp"

const uint8_t DIGITAL_PIN = 2;
const uint8_t ANALOG_PIN = A0;
const uint8_t SWITCH_BOX_COUNT = 1;
const uint8_t MAX_SWITCH_BOXES = 4;
const uint8_t BOX1_SWITCH_COUNT = 2;
const uint8_t MAX_SWITCHES_PER_BOX = 2;

bool initialized = false;

// global variable to hold an array of all switch boxes
AnalogSwitchBox **switchBoxes;
//SwitchBox<AnalogSwitch> **switchBoxes; // TODO: does this work in c++?

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

  // allocate dynamic array (on heap) of pointers to analog switch box objects of size defined by SWITCH_BOX_COUNT
  switchBoxes = new AnalogSwitchBox*[SWITCH_BOX_COUNT];

  // TEMP: create timing configuration object with following values:
  // debounceDelay = 10 ms
  // doublePressGap = 500 ms
  // longPressSpan = 500 ms
  // TODO: read this from external build config file
  TimingConfig *timingConfig = new TimingConfig(10, 500, 500);

  // TODO: iterate over switch box configurations taken from external build config file
  //for (uint8_t boxIdx = 0; boxIdx < SWITCH_BOX_COUNT; boxIdx++) {

    if (BOX1_SWITCH_COUNT > MAX_SWITCHES_PER_BOX) {

      // TEMP: write plain message to serial port
      // TODO: send OSC message
      Serial.println("Maximum number of switches per box exceeded!");

      // return from setup function - variable "initialized" won't get set to true
      return;
    }

    // allocate dynamic array (on heap) of pointers to analog switch objects of size defined by BOX1_SWITCH_COUNT
    AnalogSwitch **switches = new AnalogSwitch*[BOX1_SWITCH_COUNT];

    // TODO: iterate over switch configurations taken from exernal build config file
    //for (uint8_t switchIdx = 0; switchIdx < BOX1_SWITCH_COUNT; switchIdx++) {

      // TEMP: create 2 analog switches and store their pointers as first 2 elements of switches array
      // TODO: initialize just given switch from external build config using switchIdx
      switches[0] = new AnalogSwitch(new int*[2]{ new int[2]{0, 100}, new int[2]{200, 300}}, 2);
      switches[1] = new AnalogSwitch(new int*[2]{ new int[2]{0, 100}, new int[2]{300, 400}}, 2);
    //}

    // TEMP: create analog switch box object and store it as first element of switchBoxes array
    // TODO: use boxIdx for storing its pointer to a position in switchBoxes array corresponding to given switch box
    switchBoxes[0] = new AnalogSwitchBox(switches, BOX1_SWITCH_COUNT, timingConfig, ANALOG_PIN);
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
        if (switchBoxes[boxIdx]->getSwitches()[switchIdx]->hasNewEventOccurred()) {

          // TEMP: print it to serial port
          // TODO: send OSC message
          char label[22];
          sprintf(label, "[box %d][switch %d]: ", boxIdx, switchIdx);
          Serial.print(label);
          Serial.println(switchBoxes[boxIdx]->getSwitches()[switchIdx]->getEvent());

          // dismiss event
          switchBoxes[boxIdx]->getSwitches()[switchIdx]->dismissEvent();
        }
      }
    }
  }
}
