#include "TwizEulerMonitor.h"
#define AVERAGE_SAMPLE_SIZE 8
#define TWIZ_ROTATION_MAX 65535

TwizEulerMonitor::TwizEulerMonitor(EthernetUDP *udp, const char * address, int scale) :
  _udp(udp),
  _address(address),
  _scale(scale * -1),
  _xAverage(RunningAverage(AVERAGE_SAMPLE_SIZE)),
  _yAverage(RunningAverage(AVERAGE_SAMPLE_SIZE)),
  _zAverage(RunningAverage(AVERAGE_SAMPLE_SIZE))
  {


  }

void TwizEulerMonitor::update() {
  OSCMessage message;
  int size;

  if ((size = _udp->parsePacket()) > 0) {
    while (size--) {
      message.fill(_udp->read());
    }

    _xAverage.addValue((unsigned int) message.getInt(0));
    _yAverage.addValue((unsigned int) message.getInt(1));
    _zAverage.addValue((unsigned int) message.getInt(2));
  }
}

float TwizEulerMonitor::getRawX() { return(_xAverage.getAverage()); }
float TwizEulerMonitor::getRawY() { return(_yAverage.getAverage()); }
float TwizEulerMonitor::getRawZ() { return(_zAverage.getAverage()); }

float TwizEulerMonitor::getRawXDecimal() { return(getRawX() / TWIZ_ROTATION_MAX); }
float TwizEulerMonitor::getRawYDecimal() { return(getRawY() / TWIZ_ROTATION_MAX); }
float TwizEulerMonitor::getRawZDecimal() { return(getRawZ() / TWIZ_ROTATION_MAX); }

int TwizEulerMonitor::getRawXScaled() { return(getRawXDecimal() * _scale); }
int TwizEulerMonitor::getRawYScaled() { return(getRawYDecimal() * _scale); }
int TwizEulerMonitor::getRawZScaled() { return(getRawZDecimal() * _scale); }

int TwizEulerMonitor::getX() { return(getRawXScaled()); }
int TwizEulerMonitor::getY() { return(getRawYScaled()); }
int TwizEulerMonitor::getZ() { return(getRawZScaled()); }
