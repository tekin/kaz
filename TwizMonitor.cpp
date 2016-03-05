#include "TwizMonitor.h"
#define AVERAGE_SAMPLE_SIZE 8
#define TWIZ_ROTATION_MAX 65535
#define TRANSITION_TOLERANCE 0.8

TwizMonitor::TwizMonitor(EthernetUDP *udp, const char * address, int messageIndex, int scale) :
  _udp(udp),
  _address(address),
  _messageIndex(messageIndex),
  _scale(scale * -1),
  _Average(RunningAverage(AVERAGE_SAMPLE_SIZE)),
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
    unsigned int raw_reading = message.getInt(_messageIndex);

    _previousDecimal = getDecimal();
    _currentDecimal = ((float) raw_reading) / TWIZ_ROTATION_MAX;

    if( _previousDecimal > TRANSITION_TOLERANCE && _currentDecimal < (1-TRANSITION_TOLERANCE) ) {
      _rotations++;
      _Average.clear();
    } else if( _previousDecimal < (1-TRANSITION_TOLERANCE) && _currentDecimal > TRANSITION_TOLERANCE) {
      _rotations--;
      _Average.clear();
    }

    _Average.addValue(_currentDecimal);
  }
}

int TwizMonitor::read() { return((getDecimal() + getRotations()) * _scale); }
float TwizMonitor::getRotations() { return(_rotations); }
float TwizMonitor::getDecimal() { return(_Average.getAverage()); }
