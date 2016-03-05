#ifndef TWIZMONITOR_H
#define TWIZMONITOR_H

#include <Ethernet.h>
#include <EthernetUdp.h>
#include <OSCBundle.h>
#include "RunningAverage.h"
#include "EulerStepCounter.h"

class TwizMonitor {
  public:
    TwizMonitor(EthernetUDP *udp, const char * address, int messageIndex, int scale);
    void update();
    int read();
    float getDecimal();
    float getRotations();

  private:
    EthernetUDP *_udp;
    const char * _address;
    int _messageIndex;
    int _scale;
    RunningAverage _Average;
    float _previousDecimal;
    float _currentDecimal;
    int _rotations;
};

#endif
