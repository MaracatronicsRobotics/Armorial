#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Armorial/Geometry/Angle/Angle.h>
#include <Armorial/Utils/Utils.h>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/bundled/color.h>


TEST(Geometry_Angle_Tests, GivenAnAngle_AngleLimitsChecker_ShouldWork) {
    Geometry::Angle angleBase(0.0f);

    ASSERT_GE(angleBase.value(), -M_PI) << "Angle under minimum angle limit";
    ASSERT_LE(angleBase.value(), M_PI) << "Angle over maximum angle limit";
    EXPECT_EQ(Utils::Compare::isEqual(angleBase.value(), 0.0f), true) << "Angle value does not match";
}

TEST(Geometry_Angle_Tests, GivenAnAngle_Normalization_ShouldWork) {
    Geometry::Angle angleBase(M_PI_4);
    Geometry::Angle referenceAngle1(17 * M_PI_4);
    Geometry::Angle referenceAngle2(-7 * M_PI_4);

    EXPECT_EQ(angleBase, referenceAngle1) << "Normalization does not work";
    EXPECT_EQ(angleBase, referenceAngle2) << "Normalization does not work";
}

TEST(Geometry_Angle_Tests, GivenAnAngle_RotationDirectionGetter_ShouldWork) {
    Geometry::Angle angleBase(0.0f);

    EXPECT_EQ(angleBase.rotateDirection(M_PI - 0.1f), Geometry::Angle::COUNTER_CLOCKWISE) << "Rot. direction does not match";
    EXPECT_EQ(angleBase.rotateDirection(-sqrtf(3)), Geometry::Angle::CLOCKWISE) << "Rot. direction does not match";
}

TEST(Geometry_Angle_Tests, GivenAnAngle_ShotestAngleGetter_ShouldWork) {
    Geometry::Angle angleBase(M_PI);
    EXPECT_FLOAT_EQ(angleBase.shortestAngleDiff(sqrtf(3)), M_PI - sqrtf(3)) << "Angle difference does not match";
    EXPECT_FLOAT_EQ(angleBase.shortestAngleDiff(3*M_PI_2), M_PI_2) << "Angle difference does not match";
}

TEST(Geometry_Angle_Tests, GivenAnAngle_Operators_ShouldWork) {
    Geometry::Angle angleBase(0.0f);

    {
        SCOPED_TRACE("Angle addictors");
        Geometry::Angle referenceAngle(-sqrtf(3));
        Geometry::Angle angleSum = referenceAngle + Geometry::Angle(sqrtf(3));
        EXPECT_EQ(angleSum, angleBase) << "Addition operators do not work";
        EXPECT_EQ(referenceAngle += Geometry::Angle(sqrtf(3)), angleBase) << "Addition operators do not work";
    }
    {
        SCOPED_TRACE("Angle subtrators");
        Geometry::Angle referenceAngle(sqrtf(3));
        Geometry::Angle angleSubtraction = referenceAngle - Geometry::Angle(sqrtf(3));
        EXPECT_EQ(angleSubtraction, angleBase) << "Subtraction operators do not work";
        EXPECT_EQ(referenceAngle -= Geometry::Angle(sqrtf(3)), angleBase) << "Addition operators do not work";
    }
    {
        SCOPED_TRACE("Angle comparison");
        EXPECT_EQ(angleBase == Geometry::Angle(0.0f), true) << "Equality operator does not work";
        EXPECT_EQ(angleBase != Geometry::Angle(sqrtf(3)), true) << "Inequality operator does not work";
    }
    {
        SCOPED_TRACE("Angle assignment");
        Geometry::Angle referenceAngle = sqrtf(3);
        EXPECT_NE(angleBase, referenceAngle) << "Angles should not match";
        referenceAngle = 0.0f;
        EXPECT_EQ(angleBase, referenceAngle) << "Angles should match";
    }
}
