#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Armorial/Geometry/LineSegment/LineSegment.h>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/bundled/color.h>

TEST(Geometry_LineSegment_Tests, GivenASegment_Getters_ShouldWork) {
    Geometry::LineSegment segmentBase(Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(1.0f, 1.0f));
    {
        SCOPED_TRACE("Start Point");
        EXPECT_EQ(segmentBase.start(), Geometry::Vector2D(0.0f, 0.0f));
    }
    {
        SCOPED_TRACE("End Point");
        EXPECT_EQ(segmentBase.end(), Geometry::Vector2D(1.0f, 1.0f));
    }
}

TEST(Geometry_LineSegment_Tests, GivenASegment_PointVerification_ShouldWork) {
    Geometry::LineSegment segmentBase(Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(0.0f, 0.0f));
    EXPECT_EQ(segmentBase.isPoint(), true) << "LineSegment is not a point";
}

TEST(Geometry_LineSegment_Test, GivenASegment_DistanceToPoint_ShouldWork) {
    Geometry::LineSegment segmentBase(Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(1.0f, 1.0f));
    Geometry::Vector2D referencePoint1(0.0f, 1.0f);
    Geometry::Vector2D referencePoint2(0.0f, 3.0f);

    ASSERT_GE(segmentBase.distanceToPoint(referencePoint1), 0.0f) << "Distance of segment to point has a negative value";
    EXPECT_FLOAT_EQ(segmentBase.distanceToPoint(referencePoint1), sqrtf(2)/2) << "Distance to point does not match";
    ASSERT_GE(segmentBase.distanceToPoint(referencePoint2), 0.0f) << "Distance of segment to point has a negative value";
    EXPECT_FLOAT_EQ(segmentBase.distanceToPoint(referencePoint2), sqrtf(5)) << "Distance to point does not match";
}

TEST(Geometry_LineSegment_Test, GivenASegment_LineSegmentLength_ShouldWork) {
    Geometry::LineSegment segmentBase(Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(1.0f, 1.0f));    
    ASSERT_GE(segmentBase.length(), 0.0) << "Length of segment has a negative value";
    EXPECT_GE(segmentBase.length(), sqrtf(2)) << "Length of segment does not match";
}

TEST(Geometry_LineSegment_Tests, GivenASegment_IsOnLineChecker_ShouldWork) {
    Geometry::LineSegment segmentBase1(Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(1.0f, 1.0f));
    Geometry::LineSegment segmentBase2(Geometry::Vector2D(0.0f, -1.0f), Geometry::Vector2D(-1.0f, sqrtf(3) - 1));
    Geometry::Vector2D referencePoint(-1.0f / (sqrtf(3) + 1.0f), -1.0f / (sqrtf(3) + 1.0f));
    EXPECT_EQ(segmentBase1.isOnLine(referencePoint), false) << "Point is in segment";
    EXPECT_EQ(segmentBase2.isOnLine(referencePoint), true) << "Point is not in segment";
}

TEST(Geometry_LineSegment_Tests, GivenASegment_Projection_ShouldWork) {
    Geometry::LineSegment segmentBase(Geometry::Vector2D(-2.0f, -2.0f), Geometry::Vector2D(1.0f, 1.0f));
    Geometry::Vector2D referencePoint1(0.5f, -1.5f);
    Geometry::Vector2D referencePoint2(7.0f, 4.0f);
    Geometry::Vector2D referencePoint3(-8.0f, -5.0f);
    EXPECT_EQ(segmentBase.project(referencePoint1), Geometry::Vector2D(-0.5f, -0.5f)) << "Projection does not work";
    EXPECT_EQ(segmentBase.project(referencePoint2), Geometry::Vector2D(1.0f, 1.0f)) << "Projection does not work";
    EXPECT_EQ(segmentBase.project(referencePoint3), Geometry::Vector2D(-2.0f, -2.0f)) << "Projection does not work";
}

TEST(Geometry_LineSegment_Tests, GivenSegments_IntersectionVerification_ShouldWork) {
    Geometry::LineSegment segmentBase1(Geometry::Vector2D(-2.0f, -2.0f), Geometry::Vector2D(1.0f, 1.0f));
    Geometry::LineSegment segmentBase2(Geometry::Vector2D(0.0f, -1.0f), Geometry::Vector2D(-1.0f, sqrtf(3) - 1));
    Geometry::LineSegment segmentBase3(Geometry::Vector2D(3.0f, 0.0f), Geometry::Vector2D(0.0f, 3.0f));
    EXPECT_EQ(segmentBase1.doesIntersect(segmentBase2), true) << "Segments do not intercept";
    EXPECT_EQ(segmentBase1.doesIntersect(segmentBase3), false) << "Segments do intercept";
}

TEST(Geometry_LineSegment_Tests, GivenConnectedSegments_Intersection_ShouldWork) {
    Geometry::LineSegment segmentBase1(Geometry::Vector2D(-2.0f, -2.0f), Geometry::Vector2D(1.0f, 1.0f));
    Geometry::LineSegment segmentBase2(Geometry::Vector2D(0.0f, -1.0f), Geometry::Vector2D(-1.0f, sqrtf(3) - 1));
    Geometry::Vector2D referencePoint(-1.0f / (sqrtf(3) + 1.0f), -1.0f / (sqrtf(3) + 1.0f));
    EXPECT_EQ(segmentBase1.intersects(segmentBase2), referencePoint) << "Point is not an interception of segments";
    EXPECT_EQ(segmentBase2.isOnLine(referencePoint), true) << "Point is not in segment";
}

TEST(Geometry_LineSegment_Tests, GivenNonConnectedSegments_Intersection_ShouldFail) {
    Geometry::LineSegment segmentBase1(Geometry::Vector2D(-2.0f, -2.0f), Geometry::Vector2D(1.0f, 1.0f));
    Geometry::LineSegment segmentBase2(Geometry::Vector2D(0.0f, -1.0f), Geometry::Vector2D(1.0f, sqrtf(3) - 1));
    Geometry::LineSegment segmentBase3(Geometry::Vector2D(3.0f, 0.0f), Geometry::Vector2D(0.0f, 3.0f));
    EXPECT_EQ(segmentBase1.intersects(segmentBase2), std::nullopt) << "Interception has ocurred";
    EXPECT_EQ(segmentBase1.intersects(segmentBase3), std::nullopt) << "Interception has ocurred";
}

TEST(Geometry_LineSegment_Tests, GivenASegmentAndColinearPoint_RelativePosition_ShouldWork) {
    Geometry::LineSegment segmentBase1(Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(1.0f, 1.0f));
    Geometry::LineSegment segmentBase2(Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(2.0f, 1.0f));
    Geometry::Vector2D referencePoint1(0.4f, 0.4f);
    Geometry::Vector2D referencePoint2(-1.0f, -0.5f);

    EXPECT_FLOAT_EQ(segmentBase1.relativePosition(referencePoint1).value(), 0.4f) << "Point is not colinear with segment";
    EXPECT_FLOAT_EQ(segmentBase2.relativePosition(referencePoint2).value(), -0.5f) << "Point is not colinear with segment";
}

TEST(Geometry_LineSegment_Tests, GivenASegmentAndNonColinearPoint_RelativePosition_ShouldFail) {
    Geometry::LineSegment segmentBase1(Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(1.0f, 1.0f));
    Geometry::LineSegment segmentBase2(Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(2.0f, 1.0f));
    Geometry::Vector2D referencePoint1(0.4f, 0.0f);
    Geometry::Vector2D referencePoint2(0.0f, 1.5f);

    EXPECT_EQ(segmentBase1.relativePosition(referencePoint1).has_value(), false) << "Point is not colinear with segment";
    EXPECT_EQ(segmentBase2.relativePosition(referencePoint2).has_value(), false) << "Point is not colinear with segment";
}

TEST(Geometry_LineSegment_Tests, Given2Segments_Comparison_ShouldWork) {
    Geometry::LineSegment segmentBase1(Geometry::Vector2D(-2.0f, -2.0f), Geometry::Vector2D(1.0f, 1.0f));
    Geometry::LineSegment segmentBase2(Geometry::Vector2D(-2.00001f, -2.00001f), Geometry::Vector2D(1.00001f, 1.00001f));
    Geometry::LineSegment segmentBase3(Geometry::Vector2D(3.0f, 0.0f), Geometry::Vector2D(0.0f, 3.0f));

    EXPECT_EQ(segmentBase1 == segmentBase2, true) << "Segments are not the same";
    EXPECT_EQ(segmentBase1 == segmentBase3, false) << "Segments are the same";
}
