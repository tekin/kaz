#ifndef TWIZMONITOR_H
#define TWIZMONITOR_H

#include <Ethernet.h>
#include <EthernetUdp.h>
#include <OSCBundle.h>
#include "RunningAverage.h"
#include "EulerStepCounter.h"

class TwizMonitor {
  public:
    TwizMonitor(EthernetUDP *udp, const char * address, int scale);
    void update();
    int read();
    float getRaw();
    float getDecimal();
    int getScaled();
    float getRotations();

  private:
    EthernetUDP *_udp;
    const char * _address;
    int _scale;
    RunningAverage _Average;
    float _previousDecimal;
    int _rotations;
};

#endif
