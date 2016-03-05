#include "TwizMonitor.h"
#define AVERAGE_SAMPLE_SIZE 8
#define TWIZ_ROTATION_MAX 65535

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

    if( _previousDecimal > 0.8 && _currentDecimal < 0.2 ) {
      _rotations++;
      _Average.clear();
    } else if( _previousDecimal < 0.2 && _currentDecimal > 0.8) {
      _rotations--;
      _Average.clear();
    }

    _Average.addValue(_currentDecimal);
  }
}

int TwizMonitor::read() { return((getDecimal() + getRotations()) * _scale); }
float TwizMonitor::getRotations() { return(_rotations); }
float TwizMonitor::getDecimal() { return(_Average.getAverage()); }
