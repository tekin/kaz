
#include <SPI.h>
#include "TwizMonitor.h"
#include <AccelStepper.h>

byte arduino_mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE,  0xED } ;
byte arduino_ip[] = { 192, 168, 1, 100 };
int serverPort = 10000;

EthernetUDP Udp;
TwizMonitor twiz1_rotation(&Udp, "/rotation", 200);
AccelStepper stepper1(1, 7, 6);

void setup() {
  Ethernet.begin(arduino_mac, arduino_ip);
  Udp.begin(serverPort);
  stepper1.setMaxSpeed(900.0);
  stepper1.setAcceleration(900.0);
}

void loop() {
  twiz1_rotation.update();
  stepper1.moveTo(twiz1_rotation.read());
  stepper1.run();
}
