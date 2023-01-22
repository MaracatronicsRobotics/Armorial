#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Armorial/Geometry/Triangle/Triangle.h>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/bundled/color.h>

Geometry::Triangle triangleBase(Geometry::Vector2D(-2.0f, -1.0f), Geometry::Vector2D(1.0f, 2.0f),
                                Geometry::Vector2D(3.0f, -2.0f));

TEST(Geometry_Triangle_Tests, GivenATriangle_CornersGetter_ShouldWork) {
    std::vector<Geometry::Vector2D> triangleCorners = {Geometry::Vector2D(-2.0f, -1.0f), Geometry::Vector2D(1.0f, 2.0f),
                                                       Geometry::Vector2D(3.0f, -2.0f)};
    std::vector<Geometry::Vector2D> corners = triangleBase.corners();

    ASSERT_EQ(corners.size(), triangleCorners.size()) << "Wrong triangle corners quantity";
    for(const auto& triangleCorner : triangleCorners) {
        EXPECT_NE(std::find(corners.begin(), corners.end(), triangleCorner), std::end(corners)) << "Corner does not match";
    }
}

TEST(Geometry_Triangle_Tests, GivenATriangle_PointInTriangleChecker_ShouldWork) {
    Geometry::Vector2D pointInTriangleExample(-1.0f, -1.0f);
    Geometry::Vector2D pointNotInTriangleExample(2.0f, 1.0f);
    EXPECT_EQ(triangleBase.contains(pointInTriangleExample), true) << "Point is not in triangle";
    EXPECT_EQ(triangleBase.contains(pointNotInTriangleExample), false) << "Point is in triangle";
}

TEST(Geometry_Triangle_Tests, GivenATriangle_AreaGetter_ShouldWork) {
    float triangleArea = 9.0f;
    ASSERT_GE(triangleBase.area(), 0.0f) << "Triangle area has a negative value";
    EXPECT_FLOAT_EQ(triangleBase.area(), triangleArea) << "Triangle area does not match";
}

TEST(Geometry_Triangle_Tests, GivenATriangle_BoundaryGetter_ShouldWork) {
    std::vector<Geometry::LineSegment> triangleBoundary = {
        Geometry::LineSegment(Geometry::Vector2D(-2.0f, -1.0f), Geometry::Vector2D(1.0f, 2.0f)),
        Geometry::LineSegment(Geometry::Vector2D(1.0f, 2.0f), Geometry::Vector2D(3.0f, -2.0f)),
        Geometry::LineSegment(Geometry::Vector2D(3.0f, -2.0f), Geometry::Vector2D(-2.0f, -1.0f))};
    std::vector<Geometry::LineSegment> boundary = triangleBase.boundary();

    ASSERT_EQ(triangleBase.boundary().size(), triangleBoundary.size()) << "Wrong triangle boundary lines quantity";
    for(const auto& line : triangleBoundary) {
        EXPECT_NE(std::find(boundary.begin(), boundary.end(), line), std::end(boundary)) << "Boundary does not match";
    }
}

TEST(Geometry_Triangle_Tests, GivenATriangle_LineIntersectionChecker_ShouldWork) {
    Geometry::LineSegment intersectionLineExample(Geometry::Vector2D(3.0f, 1.0f), Geometry::Vector2D(0.0f, -2.0f));
    Geometry::LineSegment notIntersectionLineExample(Geometry::Vector2D(0.0f, 3.0f), Geometry::Vector2D(3.0f, 3.0f));

    EXPECT_EQ(triangleBase.doesIntersect(intersectionLineExample), true) << "Line does not intersect triangle";
    EXPECT_EQ(triangleBase.doesIntersect(notIntersectionLineExample), false) << "Line does intersect triangle";
}

TEST(Geometry_Triangle_Tests, GivenATriangle_IntersectionGetter_ShouldWork) {
    Geometry::LineSegment intersectionLine(Geometry::Vector2D(3.0f, 1.0f), Geometry::Vector2D(0.0f, -2.0f));
    std::vector<Geometry::Vector2D> triangleIntersects({Geometry::Vector2D(2.0f, 0.0f), Geometry::Vector2D(0.5f, -1.5f)});
    std::vector<Geometry::Vector2D> intersects = triangleBase.intersect(intersectionLine);

//    for (uint i = 0; i < inter.size(); i++) {
//        spdlog::info("{}st interception: coord. x: {}; coord. y: {}", i+1, inter[i].x(), inter[i].y());
//    }
    ASSERT_EQ(intersects.size(), triangleIntersects.size()) << "Wrong triangle intersections quantity";
    for(const auto& triangleIntersect : triangleIntersects) {
        EXPECT_NE(std::find(intersects.begin(), intersects.end(), triangleIntersect), std::end(intersects))
                << "Triangle intersections do not match";
    }
}
