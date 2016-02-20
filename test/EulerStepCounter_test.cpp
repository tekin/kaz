#include "EulerStepCounter.h"
#include "gtest/gtest.h"

TEST(EulerStepCounterTest, clockwiseRotation) {
  EulerStepCounter instance;

  instance.update(0.2);
  ASSERT_FLOAT_EQ(0.2, instance.linear_position());

  instance.update(0.4);
  ASSERT_FLOAT_EQ(0.4, instance.linear_position());

  instance.update(0.6);
  ASSERT_FLOAT_EQ(0.6, instance.linear_position());

  instance.update(0.89);
  ASSERT_FLOAT_EQ(0.89, instance.linear_position());

}

TEST(EulerStepCounterTest, clockwiseRotationWithFullRotation) {
  EulerStepCounter instance;

  instance.update(0.2);
  ASSERT_FLOAT_EQ(0.2, instance.linear_position());

  instance.update(0.4);
  ASSERT_FLOAT_EQ(0.4, instance.linear_position());

  instance.update(0.6);
  ASSERT_FLOAT_EQ(0.6, instance.linear_position());

  instance.update(0.89);
  ASSERT_FLOAT_EQ(0.89, instance.linear_position());

  instance.update(0.2);
  ASSERT_FLOAT_EQ(1.2, instance.linear_position());

  instance.update(0.4);
  ASSERT_FLOAT_EQ(1.4, instance.linear_position());
}


TEST(EulerStepCounterTest, clockwiseRotationWithDirectionChange) {
  EulerStepCounter instance;

  instance.update(0.1);
  ASSERT_FLOAT_EQ(0.1, instance.linear_position());

  instance.update(0.3);
  ASSERT_FLOAT_EQ(0.3, instance.linear_position());

  instance.update(0.6);
  ASSERT_FLOAT_EQ(0.6, instance.linear_position());

  instance.update(0.8);
  ASSERT_FLOAT_EQ(0.8, instance.linear_position());

  instance.update(0.2);
  ASSERT_FLOAT_EQ(1.2, instance.linear_position());

  instance.update(0.4);
  ASSERT_FLOAT_EQ(1.4, instance.linear_position());

  instance.update(0.7);
  ASSERT_FLOAT_EQ(1.7, instance.linear_position());

  instance.update(0.4);
  ASSERT_FLOAT_EQ(1.4, instance.linear_position());

  instance.update(0.3);
  ASSERT_FLOAT_EQ(1.3, instance.linear_position());

  instance.update(0.1);
  ASSERT_FLOAT_EQ(1.1, instance.linear_position());
}

TEST(EulerStepCounterTest, handlesReverseDirection) {
  EulerStepCounter instance;

  instance.update(0.1);
  ASSERT_FLOAT_EQ(0.1, instance.linear_position());

  instance.update(0.3);
  ASSERT_FLOAT_EQ(0.3, instance.linear_position());

  instance.update(0.6);
  ASSERT_FLOAT_EQ(0.6, instance.linear_position());

  instance.update(0.8);
  ASSERT_FLOAT_EQ(0.8, instance.linear_position());

  instance.update(0.2);
  ASSERT_FLOAT_EQ(1.2, instance.linear_position());

  instance.update(0.4);
  ASSERT_FLOAT_EQ(1.4, instance.linear_position());

  instance.update(0.7);
  ASSERT_FLOAT_EQ(1.7, instance.linear_position());

  instance.update(0.4);
  ASSERT_FLOAT_EQ(1.4, instance.linear_position());

  instance.update(0.3);
  ASSERT_FLOAT_EQ(1.3, instance.linear_position());

  instance.update(0.1);
  ASSERT_FLOAT_EQ(1.1, instance.linear_position());

  instance.update(0.3);
  ASSERT_FLOAT_EQ(1.3, instance.linear_position());

  instance.update(0.7);
  ASSERT_FLOAT_EQ(1.7, instance.linear_position());

  instance.update(0.9);
  ASSERT_FLOAT_EQ(1.9, instance.linear_position());

  instance.update(0.1);
  ASSERT_FLOAT_EQ(2.1, instance.linear_position());

  instance.update(0.8);
  ASSERT_FLOAT_EQ(1.8, instance.linear_position());
}
