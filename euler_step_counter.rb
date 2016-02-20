class EulerStepCounter
  TRANSITION_TOLERANCE = 0.6

  attr_reader :current_angle, :previous_angle, :diff, :rotations

  def initialize
    @current_angle = @previous_angle = @diff = @rotations = 0.0
  end

  # Update with the latest euler angle reading
  def update(angle)
    @previous_angle = current_angle
    @current_angle = angle

    if completed_a_revolution?
      @rotations += 1
    end

    @diff = current_diff
  end

  # The current position including rotations
  def linear_position
    current_angle + rotations
  end

private

  def completed_a_revolution?
    transition? && change_exceeds_threshold?
  end

  def current_diff
    current_angle - previous_angle
  end

  def absolute_diff
    if current_angle > previous_angle
      current_angle - previous_angle
    else
      previous_angle - current_angle
    end
  end

  def sign_of(number)
    number <=> 0
  end

  def transition?
    sign_of(current_diff) != sign_of(diff)
  end

  def change_exceeds_threshold?
    absolute_diff >= TRANSITION_TOLERANCE
  end
end
