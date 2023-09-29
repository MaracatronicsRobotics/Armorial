#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Armorial/Geometry/Arc/Arc.h>
#include <spdlog/spdlog.h>
#include <fmt/color.h>

TEST(Geometry_Arc_Tests, GivenAnArc_CenterGetter_ShouldWork) {
    Geometry::Arc arcBase(Geometry::Vector2D(1.0f, -1.0f), 1.0f);
    EXPECT_EQ(arcBase.center(), Geometry::Vector2D(1.0f, -1.0f)) << "Circle center does not match";
}

TEST(Geometry_Arc_Tests, GivenAnArc_RadiusGetter_ShouldWork) {
    Geometry::Arc arcBase(Geometry::Vector2D(0.0f, 0.0f), 1.0f);
    ASSERT_GE(arcBase.radius(), 0.0f) << "Arc radius has a negative value";
    EXPECT_FLOAT_EQ(arcBase.radius(), 1.0f) << "Arc radius does not match";
}

TEST(Geometry_Arc_Tests, GivenAnArc_AngleGetters_ShouldWork) {
    Geometry::Arc arcBase1(Geometry::Vector2D(1.0f, -1.0f), 1.0f);
    Geometry::Arc arcBase2(Geometry::Vector2D(0.0f, 0.0f), 1.0f, Geometry::Angle(Geometry::Angle::PI/4.0f), Geometry::Angle(-Geometry::Angle::PI/4.0f));

    {
        SCOPED_TRACE("Start angles");
        EXPECT_EQ(arcBase1.startAngle(), Geometry::Angle(-Geometry::Angle::PI)) << "Start angle does not match";
        EXPECT_EQ(arcBase2.startAngle(), Geometry::Angle(Geometry::Angle::PI/4.0f)) << "Start angle does not match";
    }
    {
        SCOPED_TRACE("End angles");
        EXPECT_EQ(arcBase1.endAngle(), Geometry::Angle(Geometry::Angle::PI)) << "End angle does not match";
        EXPECT_EQ(arcBase2.endAngle(), Geometry::Angle(-Geometry::Angle::PI/4.0f)) << "End angle does not match";
    }
}

TEST(Geometry_Arc_Tests, GivenAnArc_CircleChecker_ShouldWork) {
    Geometry::Arc arcBase1(Geometry::Vector2D(1.0f, -1.0f), 1.0f);
    Geometry::Arc arcBase2(Geometry::Vector2D(0.0f, 0.0f), 1.0f, Geometry::Angle(Geometry::Angle::PI/4.0f), Geometry::Angle(-Geometry::Angle::PI/4.0f));

    EXPECT_EQ(arcBase1.isCircle(), true) << "Arc is not a circle";
    EXPECT_EQ(arcBase2.isCircle(), false) << "Arc is a circle";
}

TEST(Geometry_Arc_Tests, GivenAnArc_AngleWithinArcChecker_ShouldWork) {
    Geometry::Arc arcBase1(Geometry::Vector2D(0.0f, 0.0f), 1.0f, Geometry::Angle(Geometry::Angle::PI/2.0f), Geometry::Angle(-Geometry::Angle::PI/2.0f));
    Geometry::Arc arcBase2(Geometry::Vector2D(0.0f, 0.0f), 1.0f, Geometry::Angle(-Geometry::Angle::PI/2.0f), Geometry::Angle(Geometry::Angle::PI/2.0f));

    EXPECT_EQ(arcBase1.angleWithinArc(Geometry::Angle(Geometry::Angle::PI)), true);
    EXPECT_EQ(arcBase2.angleWithinArc(Geometry::Angle(0.0f)), true) << "Angle outside arc";
}

TEST(Geometry_Arc_Tests, GivenAnArc_AngleOutsideArcChecker_ShouldWork) {
    Geometry::Arc arcBase1(Geometry::Vector2D(0.0f, 0.0f), 1.0f, Geometry::Angle(Geometry::Angle::PI/2.0f), Geometry::Angle(-Geometry::Angle::PI/2.0f));
    Geometry::Arc arcBase2(Geometry::Vector2D(0.0f, 0.0f), 1.0f, Geometry::Angle(-Geometry::Angle::PI/2.0f), Geometry::Angle(Geometry::Angle::PI/2.0f));

    EXPECT_EQ(arcBase1.angleWithinArc(Geometry::Angle(0.0f)), false) << "Angle within arc";
    EXPECT_EQ(arcBase2.angleWithinArc(Geometry::Angle(Geometry::Angle::PI)), false) << "Angle within arc";
}

TEST(Geometry_Arc_Tests, GivenAnArc_PointInArcChecker_ShouldWork) {
    Geometry::Arc arcBase1(Geometry::Vector2D(0.0f, 0.0f), 1.0f, Geometry::Angle(Geometry::Angle::PI/2.0f), Geometry::Angle(-Geometry::Angle::PI/2.0f));
    Geometry::Arc arcBase2(Geometry::Vector2D(0.0f, 0.0f), 1.0f, Geometry::Angle(-Geometry::Angle::PI/2.0f), Geometry::Angle(Geometry::Angle::PI/2.0f));

    EXPECT_EQ(arcBase1.pointInArc(Geometry::Vector2D(-1.0f, 0.0f)), true) << "Point not in arc";
    EXPECT_EQ(arcBase2.pointInArc(Geometry::Vector2D(1.0f, 0.0f)), true) << "Point not in arc";
}

TEST(Geometry_Arc_Tests, GivenAnArc_PointNotInArcChecker_ShouldWork) {
    Geometry::Arc arcBase1(Geometry::Vector2D(0.0f, 0.0f), 1.0f, Geometry::Angle(Geometry::Angle::PI/2.0f), Geometry::Angle(-Geometry::Angle::PI/2.0f));
    Geometry::Arc arcBase2(Geometry::Vector2D(0.0f, 0.0f), 1.0f, Geometry::Angle(-Geometry::Angle::PI/2.0f), Geometry::Angle(Geometry::Angle::PI/2.0f));

    EXPECT_EQ(arcBase1.pointInArc(Geometry::Vector2D(1.0f, 0.0f)), false) << "Point in arc";
    EXPECT_EQ(arcBase2.pointInArc(Geometry::Vector2D(-1.0f, 0.0f)), false) << "Point in arc";
}

TEST(Geometry_Arc_Tests, GivenAnArc_IntersectionGetter_ShouldWork) {
    Geometry::LineSegment intersectionLine(Geometry::Vector2D(5.0f, 2.0f), Geometry::Vector2D(0.5f, -1.0f));
    std::vector<Geometry::Vector2D> arcIntersections({Geometry::Vector2D(2.0f, 0.0f),
                                                      Geometry::Vector2D(3.384615f, 0.923077f)});
    Geometry::Arc arcBase(Geometry::Vector2D(3.0f, 0.0f), 1.0f, Geometry::Angle::PI, Geometry::Angle::PI/2.0f);
    std::vector<Geometry::Vector2D> intersections = arcBase.intersectionWithLine(intersectionLine);

    ASSERT_EQ(arcIntersections.size(), intersections.size()) << "Wrong arc intersections quantity";
    for(const auto& arcIntersection : arcIntersections) {
        EXPECT_NE(std::find(intersections.begin(), intersections.end(), arcIntersection), std::end(intersections))
                << "Arc intersections do not match";
    }
}
