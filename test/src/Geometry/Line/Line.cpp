#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Armorial/Geometry/Line/Line.h>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/bundled/color.h>

TEST(Geometry_Line_Tests, GivenALine_DistanceToPoint_ShouldWork) {
    Geometry::Line lineBase(Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(1.0f, 1.0f));
    Geometry::Vector2D referencePoint(0.0f, 6.0f);
    EXPECT_EQ(lineBase.distanceToLine(referencePoint), 3*sqrtf(2)) << "Distance of line to point does not match";
    ASSERT_GE(lineBase.distanceToLine(referencePoint), 0.0) << "Distance of line to point has a negative value";
}

TEST(Geometry_Line_Tests, GivenALine_ProjectionWithLine_ShouldWork) {
    Geometry::Line lineBase1(Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(1.0f, 1.0f));
    Geometry::Line lineBase2(Geometry::Vector2D(0.0f, -1.0f), Geometry::Vector2D(-1.0f, sqrtf(3) - 1));
    Geometry::Vector2D referencePoint(0.0f, 3.0f);
    EXPECT_EQ(lineBase1.project(referencePoint), Geometry::Vector2D(1.5f, 1.5f)) << "Point projection do not work";
    EXPECT_EQ(lineBase2.project(referencePoint), Geometry::Vector2D(-sqrtf(3), 2.0f)) << "Point projection do not work";
}

TEST(Geometry_Line_Tests, GivenALine_IsOnLineChecker_ShouldWork) {
    Geometry::Line lineBase1(Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(1.0f, 1.0f));
    Geometry::Line lineBase2(Geometry::Vector2D(0.0f, -1.0f), Geometry::Vector2D(-1.0f, sqrtf(3) - 1));
    Geometry::Vector2D referencePoint(-1.0f / (sqrtf(3) + 1.0f), -1.0f / (sqrtf(3) + 1.0f));
    EXPECT_EQ(lineBase1.isOnLine(referencePoint), true) << "Point is not in line";
    EXPECT_EQ(lineBase2.isOnLine(referencePoint), true) << "Point is not in line";
}

TEST(Geometry_Line_Tests, GivenALine_InterceptionOfNonParallelLines_ShouldWork) {
    Geometry::Line lineBase1(Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(1.0f, 1.0f));
    Geometry::Line lineBase2(Geometry::Vector2D(0.0f, -1.0f), Geometry::Vector2D(-1.0f, sqrtf(3) - 1.0f));
    Geometry::Line lineBase3(Geometry::Vector2D(-sqrtf(3) - 1.0f, -1.0f), Geometry::Vector2D(sqrtf(3) - 1.0f, 1.0f));
    Geometry::Vector2D referencePoint1(-1.0f / (sqrtf(3) + 1.0f), -1.0f / (sqrtf(3) + 1.0f));
    Geometry::Vector2D referencePoint2((-1.0f - sqrtf(3))/4, (3.0f + sqrtf(3))/4 - 1.0f);
    EXPECT_EQ(lineBase1.intersect(lineBase2), referencePoint1) << "Line do not intersects at the given point";
    EXPECT_EQ(lineBase2.intersect(lineBase3), referencePoint2) << "Line do not intersects at the given point";
}

//TEST(Geometry_Line_Tests, GivenALine_InterceptionOfParallelLines_ShouldFail) {
//    Geometry::Line lineBase1(Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(1.0f, 1.0f));
//    Geometry::Line lineBase2(Geometry::Vector2D(0.0f, 1.0f), Geometry::Vector2D(1.0f, 2.0f));
//    Geometry::Line lineBase3(Geometry::Vector2D(0.0f, -1.0f), Geometry::Vector2D(-1.0f, sqrtf(3) - 1.0f));
//    Geometry::Line lineBase4(Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(-1.0f, sqrtf(3)));
//    EXPECT_DEATH(lineBase1.intersect(lineBase2), "Assertion*.*failed");
//    EXPECT_DEATH(lineBase3.intersect(lineBase4), "Assertion*.*failed");
//}
