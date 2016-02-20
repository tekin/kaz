require 'test/unit'
require_relative 'euler_step_counter'

class EulerStepCounterTest < Test::Unit::TestCase
  def setup
    @counter = EulerStepCounter.new
  end

  def test_initializes_attributes
    assert_equal 0.0, @counter.current_angle
    assert_equal 0.0, @counter.previous_angle
    assert_equal 0.0, @counter.diff
    assert_equal 0.0, @counter.rotations
  end

  def test_linear_position_on_clockwise_rotation
    @counter.update(0.2)
    assert_equal 0.2, @counter.linear_position

    @counter.update(0.4)
    assert_equal 0.4, @counter.linear_position

    @counter.update(0.6)
    assert_equal 0.6, @counter.linear_position

    @counter.update(0.89)
    assert_equal 0.89, @counter.linear_position
  end

  def test_linear_position_on_clockwise_transition_is_incremental
    @counter.update(0.2)
    assert_equal 0.2, @counter.linear_position

    @counter.update(0.4)
    assert_equal 0.4, @counter.linear_position

    @counter.update(0.6)
    assert_equal 0.6, @counter.linear_position

    @counter.update(0.89)
    assert_equal 0.89, @counter.linear_position

    @counter.update(0.1)
    assert_equal 1.1, @counter.linear_position

    @counter.update(0.3)
    assert_equal 1.3, @counter.linear_position
  end

  def test_linear_position_with_change_of_direction
    @counter.update(0.1)
    assert_equal 0.1, @counter.linear_position

    @counter.update(0.3)
    assert_equal 0.3, @counter.linear_position

    @counter.update(0.6)
    assert_equal 0.6, @counter.linear_position

    @counter.update(0.8)
    assert_equal 0.8, @counter.linear_position

    @counter.update(0.2)
    assert_equal 1.2, @counter.linear_position

    @counter.update(0.4)
    assert_equal 1.4, @counter.linear_position

    @counter.update(0.7)
    assert_equal 1.7, @counter.linear_position

    @counter.update(0.4)
    assert_equal 1.4, @counter.linear_position

    @counter.update(0.3)
    assert_equal 1.3, @counter.linear_position

    @counter.update(0.1)
    assert_equal 1.1, @counter.linear_position

    @counter.update(0.8)
    assert_equal 2.8, @counter.linear_position
  end

  def test_handles_anti_clockwise_start
    @counter.update(0.8)
    assert_equal 0.8, @counter.linear_position
  end
end
