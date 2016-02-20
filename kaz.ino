#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <OSCBundle.h>
#include "EulerStepCounter.h"

// you can find this written on the board of some Arduino Ethernets or shields
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED } ;
// NOTE: Alternatively, you can assign a fixed IP to configure your
//       Ethernet shield.
byte ip[] = { 192, 168, 1, 100 };

int serverPort = 10000; //TouchOSC (incoming port)
//Create UDP message object
EthernetUDP Udp;
EulerStepCounter stepCounter;

void setup() {
  Serial.begin(250000);
  Ethernet.begin(mac, ip);
  Udp.begin(serverPort);
}

void loop() {
  float reading = parseOSCMessage();

  if( reading != -1.0 )
    stepCounter.update(reading);


  Serial.print("Euler:   ");
  Serial.println(reading);
  Serial.print("Stepper: ");
  Serial.println(stepCounter.linear_position());

  delay(50);
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
