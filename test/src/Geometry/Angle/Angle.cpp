#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Armorial/Geometry/Angle/Angle.h>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/bundled/color.h>

TEST(Geometry_Angle_Tests, MinimumAngleLimitTest) {
    Geometry::Angle angleBase(0.0f);
    EXPECT_GE(angleBase.value(), -M_PI) << "Angle under minimum angle limit";
}

TEST(Geometry_Angle_Tests, MaximumAngleLimitTest) {
    Geometry::Angle angleBase(0.0f);
    EXPECT_LE(angleBase.value(), M_PI) << "Angle over maximum angle limit";
}

TEST(Geometry_Angle_Tests, OperatorsTest) {
    Geometry::Angle angleBase(0.0f);

    {
        SCOPED_TRACE("Angles sum");

        Geometry::Angle angleSum(3.5f - 2*M_PI);
        EXPECT_EQ(angleBase + Geometry::Angle(3.5f) == angleSum, true) << "AngleBase: " << angleBase.value();
    }
    {
        SCOPED_TRACE("Angles subtrator");

        Geometry::Angle angleSubtractor(2*M_PI - 3.5f);
        EXPECT_EQ(angleBase - Geometry::Angle(3.5f) == angleSubtractor, true) << "AngleBase: " << angleBase.value();
    }
    {
        SCOPED_TRACE("Angle equalization");

        Geometry::Angle newAngle(3.5f -2*M_PI);
        angleBase = 3.5f;
        EXPECT_EQ(angleBase == newAngle, true) << "AngleBase: " << angleBase.value();
    }
}
