#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>
#include <gmock/gmock.h>

#include <Armorial/Common/Types/Object/Object.h>
using namespace Common::Types;

TEST(Common_Object_Test, Object_Constructor_Should_Work){
    const Geometry::Vector2D position(50.0f,50.0f);
    const Geometry::Vector2D velocity(3.0f,2.0f);
    const Geometry::Vector2D acceleration(3.5f,0.0f);
    const Geometry::Angle orientation(35.0f);
    const float angularSpeed = 2.5f;

    Object random(position, velocity,acceleration,orientation,angularSpeed);

    EXPECT_EQ(random.getAcceleration(), acceleration);
    EXPECT_EQ(random.getAngularSpeed(), angularSpeed);
    EXPECT_EQ(random.getOrientation(), orientation);
    EXPECT_EQ(random.getPosition(), position);
    EXPECT_EQ(random.getVelocity(), velocity);
}

TEST(Common_Object_Test, Object_Copy_ShouldWork){
    const Geometry::Vector2D position(50.0f,50.0f);
    const Geometry::Vector2D velocity(3.0f,2.0f);
    const Geometry::Vector2D acceleration(3.5f,0.0f);
    const Geometry::Angle orientation(35.0f);
    const float angularSpeed = 2.5f;

    Object another(position, velocity,acceleration,orientation,angularSpeed);

    Object random(another);

    EXPECT_EQ(random.getAcceleration(), acceleration);
    EXPECT_EQ(random.getAngularSpeed(), angularSpeed);
    EXPECT_EQ(random.getOrientation(), orientation);
    EXPECT_EQ(random.getPosition(), position);
    EXPECT_EQ(random.getVelocity(), velocity);
}

TEST(Common_Object_Test, Equal_Operator_ShouldWork){
    const Geometry::Vector2D position(50.0f,50.0f);
    const Geometry::Vector2D velocity(3.0f,2.0f);
    const Geometry::Vector2D acceleration(3.5f,0.0f);
    const Geometry::Angle orientation(35.0f);
    const float angularSpeed = 2.5f;

    Object another(position, velocity,acceleration,orientation,angularSpeed);

    Object random;

    random = another;

    EXPECT_EQ(random.getAcceleration(), acceleration);
    EXPECT_EQ(random.getAngularSpeed(), angularSpeed);
    EXPECT_EQ(random.getOrientation(), orientation);
    EXPECT_EQ(random.getPosition(), position);
    EXPECT_EQ(random.getVelocity(), velocity);
}
