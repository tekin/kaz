#include "TwizMonitor.h"

#define TWIZ_ROTATION_MAX 65535
#define TRANSITION_TOLERANCE 0.8
#define EULER_ADDRESS "/twiz"
#define EULER_Z_INDEX 2

TwizMonitor::TwizMonitor(EthernetUDP *udp, int scale) :
  _udp(udp),
  _scale(scale),
  _previousDecimal(0.0),
  _rotations(0)
  { }

void TwizMonitor::update() {
  OSCMessage message;
  int size;

  if ((size = _udp->parsePacket()) > 0) {
    while (size--) {
      message.fill(_udp->read());
    }

    if(message.fullMatch(EULER_ADDRESS)) {
      handleEulerMessage(message);
    }
  }
}

void TwizMonitor::handleEulerMessage(OSCMessage &message) {
  unsigned int raw_reading = message.getInt(EULER_Z_INDEX);

  _previousDecimal = getDecimal();
  _currentDecimal = ((float) raw_reading) / TWIZ_ROTATION_MAX;

  if( _previousDecimal > TRANSITION_TOLERANCE && _currentDecimal < (1-TRANSITION_TOLERANCE) ) {
    _rotations++;
  } else if( _previousDecimal < (1-TRANSITION_TOLERANCE) && _currentDecimal > TRANSITION_TOLERANCE) {
    _rotations--;

  }
}

int TwizMonitor::read() { return((getDecimal() + getRotations()) * _scale); }
float TwizMonitor::getRotations() { return(_rotations); }
float TwizMonitor::getDecimal() { return(_currentDecimal); }
