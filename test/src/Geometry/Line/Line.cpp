#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Armorial/Geometry/Line/Line.h>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/bundled/color.h>

TEST(Geometry_Line_Tests, GivenALine_DistanceToPoint_ShouldWork) {
    Geometry::Line lineBase(Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(1.0f, 1.0f));
    Geometry::Vector2D referencePoint(0.0f, 6.0f);
    ASSERT_GE(lineBase.distanceToLine(referencePoint), 0.0f) << "Distance of line to point has a negative value";
    EXPECT_EQ(lineBase.distanceToLine(referencePoint), 3*sqrtf(2)) << "Distance of line to point does not match";
}

TEST(Geometry_Line_Tests, GivenAnUndefinedLine_DistanceToPoint_ShouldFail) {
    Geometry::Line lineBase(Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(0.0f, 0.0f));
    Geometry::Vector2D referencePoint(0.0f, 6.0f);
    EXPECT_EQ(std::isnan(lineBase.distanceToLine(referencePoint)), true);
}

TEST(Geometry_Line_Tests, GivenALine_PointProjection_ShouldWork) {
    Geometry::Line lineBase1(Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(1.0f, 1.0f));
    Geometry::Line lineBase2(Geometry::Vector2D(0.0f, -1.0f), Geometry::Vector2D(-1.0f, sqrtf(3) - 1));
    Geometry::Vector2D referencePoint(0.0f, 3.0f);
    EXPECT_EQ(lineBase1.project(referencePoint), Geometry::Vector2D(1.5f, 1.5f)) << "Point projection do not work";
    EXPECT_EQ(lineBase2.project(referencePoint), Geometry::Vector2D(-sqrtf(3), 2.0f)) << "Point projection do not work";
}

TEST(Geometry_Line_Tests, GivenAnUndefinedLine_PointProjection_ShouldFail) {
    Geometry::Line lineBase1(Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(0.0f, 0.0f));
    Geometry::Vector2D referencePoint(0.0f, 3.0f);
    EXPECT_EQ(std::isnan(lineBase1.project(referencePoint).x()), true);
    EXPECT_EQ(std::isnan(lineBase1.project(referencePoint).x()), true);
}

TEST(Geometry_Line_Tests, GivenALine_IsOnLineChecker_ShouldWork) {
    Geometry::Line lineBase1(Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(1.0f, 1.0f));
    Geometry::Line lineBase2(Geometry::Vector2D(0.0f, -1.0f), Geometry::Vector2D(-1.0f, sqrtf(3) - 1));
    Geometry::Vector2D referencePoint(-1.0f / (sqrtf(3) + 1.0f), -1.0f / (sqrtf(3) + 1.0f));
    EXPECT_EQ(lineBase1.isOnLine(referencePoint), true) << "Point is not in line";
    EXPECT_EQ(lineBase2.isOnLine(referencePoint), true) << "Point is not in line";
}

TEST(Geometry_Line_Tests, GivenALine_IntercectionOfNonParallelLines_ShouldWork) {
    Geometry::Line lineBase1(Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(1.0f, 1.0f));
    Geometry::Line lineBase2(Geometry::Vector2D(0.0f, -1.0f), Geometry::Vector2D(-1.0f, sqrtf(3) - 1.0f));
    Geometry::Line lineBase3(Geometry::Vector2D(-sqrtf(3) - 1.0f, -1.0f), Geometry::Vector2D(sqrtf(3) - 1.0f, 1.0f));
    Geometry::Vector2D referencePoint1(-1.0f / (sqrtf(3) + 1.0f), -1.0f / (sqrtf(3) + 1.0f));
    Geometry::Vector2D referencePoint2((-sqrtf(3) - 1.0f)/4, (sqrtf(3) - 1.0f)/4);
    EXPECT_EQ(lineBase1.intersect(lineBase2), referencePoint1) << "Lines do not intersect at the given point";
    EXPECT_EQ(lineBase2.intersect(lineBase3), referencePoint2) << "Lines do not intersect at the given point";
}

TEST(Geometry_Line_Tests, GivenALine_IntercectionOfParallelLines_ShouldFail) {
    Geometry::Line lineBase1(Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(1.0f, 1.0f));
    Geometry::Line lineBase2(Geometry::Vector2D(0.0f, 1.0f), Geometry::Vector2D(1.0f, 2.0f));
    Geometry::Line lineBase3(Geometry::Vector2D(0.0f, -1.0f), Geometry::Vector2D(-1.0f, sqrtf(3) - 1.0f));
    Geometry::Line lineBase4(Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(-1.0f, sqrtf(3)));
    EXPECT_EQ(lineBase1.intersect(lineBase2), std::nullopt) << "The lines are not paallel";
    EXPECT_EQ(lineBase3.intersect(lineBase4), std::nullopt) << "The lines are not paallel";
}

TEST(Geometry_Line_Tests, Given2Lines_Comparison_ShouldWork) {
    Geometry::Line lineBase1(Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(1.0f, 1.0f));
    Geometry::Line lineBase2(Geometry::Vector2D(-3.0f, -3.0f), Geometry::Vector2D(-4.0f, -4.0f));
    Geometry::Line lineBase3(Geometry::Vector2D(-1.0f, -1.0f), Geometry::Vector2D(0.0f, 1.0f));
    EXPECT_EQ(lineBase1 == lineBase2, true) << "The lines are not the same";
    EXPECT_EQ(lineBase1 == lineBase3, false) << "The lines are the same";
}
