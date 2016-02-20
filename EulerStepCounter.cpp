#include "EulerStepCounter.h"

#define EULER_TRANSITION_TOLERANCE 0.6

EulerStepCounter::EulerStepCounter() :_previous_angle(0.0), _current_angle(0.0), _diff(0.0), _rotations(0.0) {}

void EulerStepCounter::update(float angle) {
  _previous_angle = _current_angle;
  _current_angle = angle;

  if( completed_a_revolution() == true) {
    _rotations = _rotations + 1.0;
  }

  _diff = current_diff();
}

float EulerStepCounter::linear_position() {
  return(_current_angle + _rotations);
}

float EulerStepCounter::current_diff() {
  return(_current_angle - _previous_angle);
}

float EulerStepCounter::absolute_diff() {
  if(_current_angle > _previous_angle)
    return(current_diff());
  else
    return(_previous_angle - _current_angle);
}

bool EulerStepCounter::completed_a_revolution() {
  return(transitioned() == true && change_exceeds_threshold() == true);
}

bool EulerStepCounter::transitioned() {
  return(current_diff() < 0.0 && _diff > 0.0 || current_diff() > 0.0 && _diff < 0.0);
}

bool EulerStepCounter::change_exceeds_threshold() {
  return(absolute_diff() >= EULER_TRANSITION_TOLERANCE);
}
