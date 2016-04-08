#ifndef TWIZMONITOR_H
#define TWIZMONITOR_H

#include <Ethernet.h>
#include <EthernetUdp.h>
#include <OSCBundle.h>
#include "RunningAverage.h"
#include "EulerStepCounter.h"

class TwizMonitor {
  public:
    TwizMonitor(EthernetUDP *udp, int scale);
    void update();
    int read();
    float getDecimal();
    float getRotations();

  private:
    void handleEulerMessage(OSCMessage &message);
    EthernetUDP *_udp;
    int _scale;
    RunningAverage _Average;
    float _previousDecimal;
    float _currentDecimal;
    int _rotations;
};

#endif
