#ifndef EULERSTEPCOUNTER_H
#define EULERSTEPCOUNTER_H

class EulerStepCounter {
  public:
    EulerStepCounter();
    void update(float angle);
    float linear_position();
    float current_diff();
    float absolute_diff();
    bool completed_a_revolution();
    bool transitioned();
    bool change_exceeds_threshold();
    float direction();

  private:
    float _current_angle;
    float _previous_angle;
    float _previous_diff;
    float _rotations;
};

#endif
