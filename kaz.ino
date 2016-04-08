
#include <SPI.h>
#include "TwizMonitor.h"
#include <AccelStepper.h>

#define STEPS_PER_ROTATION 3200
#define HALL_SWITCH_PIN 7

byte arduino_mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE,  0xED } ;
byte arduino_ip[] = { 192, 168, 0, 100 };
int serverPort = 10000;
bool calibarated = false;
int stepperOffset = 0;

EthernetUDP Udp;
TwizMonitor twiz_monitor(&Udp, STEPS_PER_ROTATION);
AccelStepper stepper1(1, 6, 5);

void setup() {
  Ethernet.begin(arduino_mac, arduino_ip);
  Udp.begin(serverPort);
  stepper1.setMaxSpeed(10000.0);
  stepper1.setAcceleration(10000.0);
}

void loop() {
  twiz_monitor.update();

  if( calibarated == true ){
    int new_position = twiz_monitor.read() - stepperOffset;
    stepper1.moveTo(new_position);
    stepper1.run();
  } else {
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
}

