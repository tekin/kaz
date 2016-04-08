
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <OSCBundle.h>
#include "TwizMonitor.h"
#include <AccelStepper.h>

#define STEPS_PER_ROTATION 3200
#define HALL_SWITCH_PIN 7

byte arduino_mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE,  0xED } ;
byte arduino_ip[] = { 192, 168, 0, 100 };

bool calibarated = false;
int stepperOffset = 0;

EthernetUDP TwizUdp;
int TwizUdpPort = 100;

TwizMonitor twiz_monitor(STEPS_PER_ROTATION);
AccelStepper stepper1(1, 6, 5);

void setup() {
  Ethernet.begin(arduino_mac, arduino_ip);
  TwizUdp.begin(TwizUdpPort);

  stepper1.setMaxSpeed(10000.0);
  stepper1.setAcceleration(10000.0);
}

void loop() {
  handleOSCMessage();

  if( calibarated == true ){
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

void handleOSCMessage() {
  int size;

  if ((size = TwizUdp.parsePacket()) > 0) {
    OSCMessage message;

    while (size--) {
      message.fill(TwizUdp.read());
    }
    message.dispatch("/twiz", handleTwizData);
  }
}

void handleTwizData(OSCMessage &message) {
  unsigned int raw_reading = message.getInt(2);

  twiz_monitor.handleEulerMessage(raw_reading);
}

void handleResetMessage(OSCMessage &message) {

}

void checkForCalibaration() {
  if( digitalRead(HALL_SWITCH_PIN) == LOW ){
    // stepper has reached the reset point
    calibarated = true;
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
