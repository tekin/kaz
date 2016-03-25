
#include <SPI.h>
#include "TwizMonitor.h"
#include <AccelStepper.h>

#define STEPS_PER_ROTATION 200

byte arduino_mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE,  0xED } ;
byte arduino_ip[] = { 192, 168, 0, 100 };
int serverPort = 10000;

EthernetUDP Udp;
TwizMonitor twiz_z_rotation(&Udp, "/rotation", 2, STEPS_PER_ROTATION);
AccelStepper stepper1(1, 7, 6);

void setup() {
  Ethernet.begin(arduino_mac, arduino_ip);
  Udp.begin(serverPort);
  stepper1.setMaxSpeed(900.0);
  stepper1.setAcceleration(900.0);
}

void loop() {
  twiz_z_rotation.update();
  stepper1.moveTo(twiz_z_rotation.read());
  stepper1.run();
}
