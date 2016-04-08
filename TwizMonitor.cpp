#include "TwizMonitor.h"

#define TWIZ_ROTATION_MAX 65535
#define TRANSITION_TOLERANCE 0.8

TwizMonitor::TwizMonitor(int scale) :
  _scale(scale),
  _previousDecimal(0.0),
  _rotations(0)
  { }

void TwizMonitor::handleEulerMessage(float decimal) {
  _previousDecimal = getDecimal();
  _currentDecimal = decimal;
  calculateRotations();
}

void TwizMonitor::handleEulerMessage(unsigned int raw_reading) {
  _previousDecimal = getDecimal();
  _currentDecimal = ((float) raw_reading) / TWIZ_ROTATION_MAX;
  calculateRotations();
}

void TwizMonitor::calculateRotations() {
  if( _previousDecimal > TRANSITION_TOLERANCE && _currentDecimal < (1-TRANSITION_TOLERANCE) ) {
    _rotations++;
  } else if( _previousDecimal < (1-TRANSITION_TOLERANCE) && _currentDecimal > TRANSITION_TOLERANCE) {
    _rotations--;

  }
}

int TwizMonitor::read() { return((getDecimal() + getRotations()) * _scale); }
float TwizMonitor::getRotations() { return(_rotations); }
float TwizMonitor::getDecimal() { return(_currentDecimal); }
