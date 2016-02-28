#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <OSCBundle.h>
#include "EulerStepCounter.h"
#include <AccelStepper.h>

// you can find this written on the board of some Arduino Ethernets or shields
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED } ;
// NOTE: Alternatively, you can assign a fixed IP to configure your
//       Ethernet shield.
byte ip[] = { 192, 168, 1, 100 };

//TouchOSC (incoming port)
int serverPort = 10000;
EthernetUDP Udp;
EulerStepCounter stepCounter;
AccelStepper stepper1(1, 7, 6);
float previous_reading = 0;

void setup() {
  Ethernet.begin(mac, ip);
  Udp.begin(serverPort);
  stepper1.setMaxSpeed(900.0);
  stepper1.setAcceleration(900.0);
}

void loop() {
  float reading = parseOSCMessage();

  if( reading != -1.0  && abs(reading - previous_reading) > 0.05) {
    stepCounter.update(reading);
    float position = stepCounter.linear_position();
    // adjust for the steppers scale (200 per revolution)
    int linear_position = (int)(position * 200 * -1);
    stepper1.moveTo(linear_position);
  }
  previous_reading = reading;

  stepper1.run();
}

// either returns the euler angle or -1.0 if packet not received
float parseOSCMessage() {
  OSCMessage msgIn;
  int size;

  if ((size = Udp.parsePacket()) > 0) {
    while (size--)
      msgIn.fill(Udp.read());

    return(msgIn.getFloat(0));
  } else {
    return(-1.0);
  }
}
