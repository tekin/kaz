
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <OSCBundle.h>
#include "TwizMonitor.h"
#include <AccelStepper.h>

#define STEPS_PER_ROTATION 3200
#define HALL_SWITCH_PIN 7

#define TWIZ_UDP_PORT 10000
#define OVERRIDE_UDP_PORT 20000
#define TWIZ_ADDRESS "/twiz"
#define OVERRIDE_TOGGLE_ADDRESS "/1/fader1"
#define OVERRIDE_SIGNAL_ADDRESS "/1/fader2"
#define CALIBRATE_ADDRESS "/calibrate"

byte arduino_mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE,  0xED } ;
byte arduino_ip[] = { 192, 168, 0, 100 };

bool calibrated = false;
bool override = false;
int stepperOffset = 0;

EthernetUDP TwizUdp;
EthernetUDP OverrideUdp;


TwizMonitor twiz_monitor(STEPS_PER_ROTATION);
AccelStepper stepper1(1, 6, 5);

void setup() {
  Ethernet.begin(arduino_mac, arduino_ip);
  TwizUdp.begin(TWIZ_UDP_PORT);
  OverrideUdp.begin(OVERRIDE_UDP_PORT);
  stepper1.setMaxSpeed(10000.0);
  stepper1.setAcceleration(10000.0);
}

void loop() {
  handleOSCMessages();

  if( calibrated == true ){
    updateStepperPosition();
  } else {
    checkForCalibaration();
  }
}

void updateStepperPosition() {
  int new_position = twiz_monitor.read() - stepperOffset;
  stepper1.moveTo(new_position);
  stepper1.run();
}

void handleOSCMessages() {
  int size;
  OSCMessage OverrideMessage;

  // always read from the override connection
  if ((size = OverrideUdp.parsePacket()) > 0) {
    while (size--) { OverrideMessage.fill(OverrideUdp.read()); }
  }

  // will set override to true if the toggle value is greater than 0.5
  OverrideMessage.dispatch(CALIBRATE_ADDRESS, handleForceCalibrate);

  // will set override to true if the toggle value is greater than 0.5
  OverrideMessage.dispatch(OVERRIDE_TOGGLE_ADDRESS, handleOverrideToggle);

  if (override == true) {
    // set the position based on the override signal if it is present
    OverrideMessage.dispatch(OVERRIDE_SIGNAL_ADDRESS, handleOverrideData);
  } else {
    // otherwise we read from the Twiz
    if ((size = TwizUdp.parsePacket()) > 0) {
      OSCMessage TwizMessage;
      while (size--) { TwizMessage.fill(TwizUdp.read()); }
      TwizMessage.dispatch(TWIZ_ADDRESS, handleTwizData);
    }
  }
}

// Handle for the Twiz data. Can handle both a raw unsigned integer value and a float
// between 0.0 and 1.0
void handleTwizData(OSCMessage &message) {
  if (message.isInt(2)) {
    unsigned int raw_reading = message.getInt(2);
    twiz_monitor.handleEulerMessage(raw_reading);
  } else if (message.isFloat(2)) {
    twiz_monitor.handleEulerMessage(message.getFloat(2));
  }
}

// Handle for force calibration
void handleForceCalibrate(OSCMessage &message) {
  calibrated = false;
}

// Handler for the override data. Expects the value to be a float between 0.0 and 1.0.
void handleOverrideData(OSCMessage &message) {
  twiz_monitor.handleEulerMessage(message.getFloat(0));
}

// Toggles override based on the value received: greater than 0.5 toggles the
// override on; less than 0.5 toggles it off
void handleOverrideToggle(OSCMessage &message) {
  if (message.getFloat(0) > 0.5) {
    override = true;
  } else {
    override = false;
  }
}

void checkForCalibaration() {
  if( digitalRead(HALL_SWITCH_PIN) == LOW ){
    // stepper has reached the reset point
    calibrated = true;
    // adjust for any movement that hasn't been completed
    stepperOffset -= stepper1.distanceToGo();
    // set the offset to be the difference between the current step poisition
    // and the position coming back from the Twiz
    stepperOffset = twiz_monitor.read() - stepperOffset;
  } else {
    // Not reached the reset point, keep it moving
    if(stepper1.distanceToGo() == 0) {
      stepperOffset += STEPS_PER_ROTATION/100;
    }
    stepper1.moveTo(stepperOffset);
    stepper1.run();
  }
}
