#ifndef TWIZEULERMONITOR_H
#define TWIZEULERMONITOR_H

#include <Ethernet.h>
#include <EthernetUdp.h>
#include <OSCBundle.h>
#include "RunningAverage.h"
#include "EulerStepCounter.h"

class TwizEulerMonitor {
  public:
    TwizEulerMonitor(EthernetUDP *udp, const char * address, int scale);
    void update();
    float getRawX();
    float getRawY();
    float getRawZ();
    float getRawXDecimal();
    float getRawYDecimal();
    float getRawZDecimal();
    int getRawXScaled();
    int getRawYScaled();
    int getRawZScaled();
    int getX();
    int getY();
    int getZ();

  private:
    EthernetUDP *_udp;
    const char * _address;
    int _scale;
    RunningAverage _xAverage;
    RunningAverage _yAverage;
    RunningAverage _zAverage;
};

#endif
