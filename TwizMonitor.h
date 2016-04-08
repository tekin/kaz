#ifndef TWIZMONITOR_H
#define TWIZMONITOR_H

class TwizMonitor {
  public:
    TwizMonitor(int scale);
    int read();
    float getDecimal();
    float getRotations();
    void handleEulerMessage(unsigned int raw_reading);
    void handleEulerMessage(float decimal);
    void calculateRotations();

  private:
    int _scale;
    float _previousDecimal;
    float _currentDecimal;
    int _rotations;
};

#endif
