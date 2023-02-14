#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Armorial/Geometry/Circle/Circle.h>
#include <spdlog/spdlog.h>

#include <fmt/color.h>

Geometry::Circle circleBase(Geometry::Vector2D(2.0f, 0.0f), 2.0f);

TEST(Geometry_Circle_Tests, GivenACircle_CenterGetter_ShouldWork) {
    Geometry::Vector2D circleCenter(2.0f, 0.0f);
    EXPECT_EQ(circleBase.center(), circleCenter) << "Circle center does not match";
}

TEST(Geometry_Circle_Tests, GivenACircle_RadiusGetter_ShouldWork) {
    float circleRadius = 2.0f;
    ASSERT_GE(circleBase.radius(), 0.0f) << "Circle radius has a negative value";
    EXPECT_FLOAT_EQ(circleBase.radius(), circleRadius) << "Circle radius does not match";
}

TEST(Geometry_Circle_Tests, GivenACircle_PointInCircleChecker_ShouldWork) {
    Geometry::Vector2D pointInCircleExample(1.0f, 1.0f);
    Geometry::Vector2D pointNotInCircleExample(1.0f, 2.0f);
    EXPECT_EQ(circleBase.contains(pointInCircleExample), true) << "Point is not in circle";
    EXPECT_EQ(circleBase.contains(pointNotInCircleExample), false) << "Point is in circle";
}

TEST(Geometry_Circle_Tests, GivenACircle_LineIntersectionChecker_ShouldWork) {
    Geometry::LineSegment intersectionLineExample(Geometry::Vector2D(5.0f, 2.0f), Geometry::Vector2D(-2.0f, 0.0f));
    Geometry::LineSegment notIntersectionLineExample(Geometry::Vector2D(-1.0f, 2.0f), Geometry::Vector2D(1.0f, -3.0f));

    EXPECT_EQ(circleBase.doesIntersect(intersectionLineExample), true) << "Line does not intersect circle";
    EXPECT_EQ(circleBase.doesIntersect(notIntersectionLineExample), false) << "Line does intersect circle";
}

TEST(Geometry_Circle_Tests, GivenACircle_IntersectionGetter_ShouldWork) {
    Geometry::LineSegment intersectionLine(Geometry::Vector2D(5.0f, 2.0f), Geometry::Vector2D(-2.0f, 0.0f));
    std::vector<Geometry::Vector2D> circleIntersections({Geometry::Vector2D(0.091346f, 0.59753f),
                                                         Geometry::Vector2D(3.30488f, 1.51568f)});
    std::vector<Geometry::Vector2D> intersections = circleBase.intersects(intersectionLine);

    ASSERT_EQ(circleIntersections.size(), intersections.size()) << "Wrong circle intersections quantity";
    for(const auto& circleIntersection : circleIntersections) {
        EXPECT_NE(std::find(intersections.begin(), intersections.end(), circleIntersection), std::end(intersections))
                << "Circle intersections do not match";
    }
}

TEST(Geometry_Circle_Tests, GivenACircle_Projection_ShouldWork) {
    Geometry::Vector2D referencePoint1(3.6641f, 1.1094f);
    Geometry::Vector2D referencePoint2(1.36754f, -1.89737f);

    EXPECT_EQ(circleBase.project(Geometry::Vector2D(5.0f, 2.0f)), referencePoint1) << "Projection point does not match";
    EXPECT_EQ(circleBase.project(Geometry::Vector2D(1.0f, -3.0f)), referencePoint2) << "Projection point does not match";
}

TEST(Geometry_Circle_Tests, GivenACircle_Comparison_ShouldWork) {
    {
        SCOPED_TRACE("Equality operator");

        Geometry::Circle referenceCircle(Geometry::Vector2D(2.0, 0.0f), 2.0f);
        EXPECT_EQ(circleBase == referenceCircle, true) << "Equality operator does not work";
    }
    {
        SCOPED_TRACE("Inequality operator");

        Geometry::Circle referenceCircle(Geometry::Vector2D(0.0, 0.0f), 10.0f);
        EXPECT_EQ(circleBase != referenceCircle, true) << "Inequality operator does not work";
    }
}

TEST(Geometry_Circle_Tests, GivenACircle_AdditionOperators_ShouldWork) {
    Geometry::Circle referenceCircle(Geometry::Vector2D(0.0, 0.0f), 2.0f);
    Geometry::Circle newCircle = referenceCircle + Geometry::Vector2D(2.0f, 0.0f);
    EXPECT_EQ(newCircle, circleBase) << "Addition operator does not work";
    EXPECT_EQ(referenceCircle += Geometry::Vector2D(2.0f, 0.0f), circleBase) << "Addition operator does not work";
}

TEST(Geometry_Circle_Tests, GivenACircle_SubtractionOperators_ShouldWork) {
    Geometry::Circle referenceCircle(Geometry::Vector2D(4.0, 0.0f), 2.0f);
    Geometry::Circle newCircle = referenceCircle - Geometry::Vector2D(2.0f, 0.0f);
    EXPECT_EQ(newCircle, circleBase) << "Subtraction operator does not work";
    EXPECT_EQ(referenceCircle -= Geometry::Vector2D(2.0f, 0.0f), circleBase) << "Subtraction operator does not work";
}

TEST(Geometry_Circle_Tests, GivenACircle_MultiplicationOperators_ShouldWork) {
    Geometry::Circle referenceCircle(Geometry::Vector2D(2.0, 0.0f), 0.5f);
    Geometry::Circle newCircle = referenceCircle * 4.0f;
    EXPECT_EQ(newCircle, circleBase) << "Multiplication operator does not work";
    EXPECT_EQ(referenceCircle *= 4.0f, circleBase) << "Multiplication operator does not work";
}

TEST(Geometry_Circle_Tests, GivenACircle_DivisionOperators_ShouldWork) {
    Geometry::Circle referenceCircle(Geometry::Vector2D(2.0, 0.0f), 6.0f);
    Geometry::Circle newCircle = referenceCircle / 3.0f;
    EXPECT_EQ(newCircle, circleBase) << "Division operator does not work";
    EXPECT_EQ(referenceCircle /= 3.0f, circleBase) << "Division operator does not work";
}

TEST(Geometry_Circle_Tests, GivenACircle_Moving_ShouldWork) {
    Geometry::Circle movedCircle(Geometry::Vector2D(3.0f, 1.0f), 2.0f);
    circleBase.move(Geometry::Vector2D(1.0f, 1.0f));
    EXPECT_EQ(circleBase, movedCircle) << "Moved circle does not match";
}
