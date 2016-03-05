#include "TwizMonitor.h"
#define AVERAGE_SAMPLE_SIZE 8
#define TWIZ_ROTATION_MAX 65535

TwizMonitor::TwizMonitor(EthernetUDP *udp, const char * address, int scale) :
  _udp(udp),
  _address(address),
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

    _Average.addValue((unsigned int) message.getInt(2));
  }
}

int TwizMonitor::read() { return(getScaled()); }
float TwizMonitor::getRotations() { return(_rotations); }
float TwizMonitor::getRaw() { return(_Average.getAverage()); }
float TwizMonitor::getDecimal() { return(getRaw() / TWIZ_ROTATION_MAX); }
int TwizMonitor::getScaled() { return(getDecimal() * _scale); }

