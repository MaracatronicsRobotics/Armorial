#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Armorial/Geometry/Polygon/Polygon.h>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/bundled/color.h>

std::vector<Geometry::Vector2D> polygonVertices = {Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(1.0f, 2.0f),
                                                   Geometry::Vector2D(2.0f, 0.0f), Geometry::Vector2D(4.0f, 0.0f),
                                                   Geometry::Vector2D(2.5f, -1.5f), Geometry::Vector2D(3.0f, -3.75f),
                                                   Geometry::Vector2D(1.0f, -2.5f), Geometry::Vector2D(-1.0f, -3.75f),
                                                   Geometry::Vector2D(-0.5f, -1.5f), Geometry::Vector2D(-2.0f, 0.0f)};
Geometry::Polygon polygonBase(polygonVertices);

TEST(Geometry_Polygon_Tests, GivenAPolygon_VerticesCounter_ShouldWork) {
    EXPECT_EQ(polygonBase.amountOfVertices(), 10) << "Polygon vertices quantity does not match";
}

TEST(Geometry_Polygon_Tests, GivenAPolygon_VerticesGetter_ShouldWork) {
    for (uint i = 0; i < polygonVertices.size(); i++) {
        EXPECT_EQ(polygonBase.vertices()[i], polygonVertices[i]) << "Polygon vertices does not match";
    }
}

TEST(Geometry_Polygon_Tests, GivenAPolygon_IteratorOperator_ShouldWork) {
    for (uint i = 0; i < polygonVertices.size(); i++) {
        EXPECT_EQ(polygonBase[i], polygonVertices[i]) << "Polygon vertices does not match";
    }
}

TEST(Geometry_Polygon_Tests, GivenAPolygon_InsertVertice_ShouldWork) {
    polygonBase.insertVertice(Geometry::Vector2D(0.0f, 2.0f));
    polygonVertices.push_back(Geometry::Vector2D(0.0f, 2.0f));
    for (uint i = 0; i < polygonVertices.size(); i++) {
        EXPECT_EQ(polygonBase.vertices()[i], polygonVertices[i]) << "Polygon vertices does not match";
    }
}

TEST(Geometry_Polygon_Tests, GivenAPolygon_RemoveVertice_ShouldWork) {
    polygonBase.removeVertice(polygonBase.vertices().size() - 1);
    polygonVertices.pop_back();
    for (uint i = 0; i < polygonVertices.size(); i++) {
        EXPECT_EQ(polygonBase.vertices()[i], polygonVertices[i]) << "Polygon vertices does not match";
    }
}

TEST(Geometry_Polygon_Tests, GivenAPolygon_Moving_ShouldWork) {
    std::vector<Geometry::Vector2D> movedVertices = {Geometry::Vector2D(1.0f, 1.0f), Geometry::Vector2D(2.0f, 3.0f),
                                                     Geometry::Vector2D(3.0f, 1.0f), Geometry::Vector2D(5.0f, 1.0f),
                                                     Geometry::Vector2D(3.5f, -0.5f), Geometry::Vector2D(4.0f, -2.75f),
                                                     Geometry::Vector2D(2.0f, -1.5f), Geometry::Vector2D(0.0f, -2.75f),
                                                     Geometry::Vector2D(0.5f, -0.5f), Geometry::Vector2D(-1.0f, 1.0f)};
    polygonBase.move(Geometry::Vector2D(1.0f, 1.0f));
    for (uint i = 0; i < movedVertices.size(); i++) {
        EXPECT_EQ(polygonBase.vertices()[i], polygonVertices[i]) << "Moved polygon vertices does not match";
    }
}

TEST(Geometry_Polygon_Tests, GivenAPolygon_CentroidGetter_ShouldWork) {
    Geometry::Vector2D centroid(1.0f, -1.12758f);
    EXPECT_EQ(polygonBase.centroid(), centroid) << "Polygon centroid does not match";
}

TEST(Geometry_Polygon_Tests, GivenAnInvalidPolygon_CentroidGetter_ShouldFail) {
    Geometry::Polygon invalidPolygon({Geometry::Vector2D(0.0f, 0.0f)});
    EXPECT_EQ(std::isnan(invalidPolygon.centroid().x()), true);
    EXPECT_EQ(std::isnan(invalidPolygon.centroid().y()), true);
}

TEST(Geometry_Polygon_Tests, GivenAPolygon_PerimeterGetter_ShouldWork) {
    float polygonPerimeter = 22.04154f;
    ASSERT_GE(polygonBase.area(), 0.0f) << "Polygon perimeter has a negative value";
    EXPECT_FLOAT_EQ(polygonBase.perimeterLength(), polygonPerimeter) << "Polygon perimeter does not match";
}

TEST(Geometry_Polygon_Tests, GivenAPolygon_AreaGetter_ShouldWork) {
    float polygonArea = 14.125f;
    ASSERT_GE(polygonBase.area(), 0.0f) << "Polygon area has a negative value";
    EXPECT_FLOAT_EQ(polygonBase.area(), polygonArea) << "Polygon area does not match";
}

TEST(Geometry_Polygon_Tests, GivenAPolygon_BoundaryGetter_ShouldWork) {
    std::vector<Geometry::LineSegment> polygonBoundary = {
        Geometry::LineSegment(Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(1.0f, 2.0f)),
        Geometry::LineSegment(Geometry::Vector2D(1.0f, 2.0f), Geometry::Vector2D(2.0f, 0.0f)),
        Geometry::LineSegment(Geometry::Vector2D(2.0f, 0.0f), Geometry::Vector2D(4.0f, 0.0f)),
        Geometry::LineSegment(Geometry::Vector2D(4.0f, 0.0f), Geometry::Vector2D(2.5f, -1.5f)),
        Geometry::LineSegment(Geometry::Vector2D(2.5f, -1.5f), Geometry::Vector2D(3.0f, -3.75f)),
        Geometry::LineSegment(Geometry::Vector2D(3.0f, -3.75f), Geometry::Vector2D(1.0f, -2.5f)),
        Geometry::LineSegment(Geometry::Vector2D(1.0f, -2.5f), Geometry::Vector2D(-1.0f, -3.75f)),
        Geometry::LineSegment(Geometry::Vector2D(-1.0f, -3.75f), Geometry::Vector2D(-0.5f, -1.5f)),
        Geometry::LineSegment(Geometry::Vector2D(-0.5f, -1.5f), Geometry::Vector2D(-2.0f, 0.0f)),
        Geometry::LineSegment(Geometry::Vector2D(-2.0f, 0.0f), Geometry::Vector2D(0.0f, 0.0f))};

    for (uint i = 0; i < polygonBoundary.size(); i++) {
        EXPECT_EQ(polygonBase.boundary()[i], polygonBoundary[i]) << "Polygon boundary does not match";
    }
}

TEST(Geometry_Polygon_Tests, GivenAPolygon_PointInBoundaryChecker_ShouldWork) {
    Geometry::Vector2D pointOnBoundaryExample(0.0f, 0.0f);
    Geometry::Vector2D pointNotOnBoundaryExample(1.0f, 1.0f);
    EXPECT_EQ(polygonBase.isOnBoundary(pointOnBoundaryExample), true) << "Point is not on polygon boundary";
    EXPECT_EQ(polygonBase.isOnBoundary(pointNotOnBoundaryExample), false) << "Point is on polygon boundary";
}

TEST(Geometry_Polygon_Tests, GivenAPolygon_PointInPolygonChecker_ShouldWork) {
    Geometry::Vector2D pointInPolygonExample(-1.0f, -1.0f);
    Geometry::Vector2D pointNotInPolygonExample(2.0f, 1.0f);
    EXPECT_EQ(polygonBase.contains(pointInPolygonExample), true) << "Point is not in polygon";
    EXPECT_EQ(polygonBase.contains(pointNotInPolygonExample), false) << "Point is in polygon";
}

TEST(Geometry_Polygon_Tests, GivenAPolygon_SimpleChecker_ShouldWork) {
    Geometry::Polygon counterpartPolygon({Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(2.0f, 0.0f),
                                          Geometry::Vector2D(0.0f, -2.0f), Geometry::Vector2D(0.5f, 1.0f)});

    EXPECT_EQ(polygonBase.isSimple(), true) << "Polygon is not simple";
    EXPECT_EQ(counterpartPolygon.isSimple(), false) << "Polygon is simple";
}

TEST(Geometry_Polygon_Tests, GivenAPolygon_ConvexChecker_ShouldWork) {
    Geometry::Polygon counterpartPolygon({Geometry::Vector2D(0.0f, 0.0f), Geometry::Vector2D(1.0f, 1.0f),
                                          Geometry::Vector2D(2.0f, -0.5f), Geometry::Vector2D(0.5f, -2.0f)});

    EXPECT_EQ(polygonBase.isConvex(), false) << "Polygon is convex";
    EXPECT_EQ(counterpartPolygon.isConvex(), true) << "Polygon is not convex";
}

TEST(Geometry_Polygon_Tests, GivenAPolygon_LineIntersectionChecker_ShouldWork) {
    Geometry::LineSegment intersectionLineExample(Geometry::Vector2D(-3.0f, 2.0f), Geometry::Vector2D(0.0f, -4.0f));
    Geometry::LineSegment notIntersectionLineExample(Geometry::Vector2D(0.0f, 3.0f), Geometry::Vector2D(3.0f, 3.0f));

    EXPECT_EQ(polygonBase.doesIntersect(intersectionLineExample), true) << "Line does not intersect polygon";
    EXPECT_EQ(polygonBase.doesIntersect(notIntersectionLineExample), false) << "Line does intersect polygon";
}

TEST(Geometry_Polygon_Tests, GivenAPolygon_IntersectionGetter_ShouldWork) {
    Geometry::LineSegment intersectionLine(Geometry::Vector2D(5.0f, 2.0f), Geometry::Vector2D(1.0f, -6.0f));
    std::vector<Geometry::Vector2D> polIntersections({Geometry::Vector2D(4.0f, 0.0f), Geometry::Vector2D(7.0f/3, -10.0f/3),
                                                      Geometry::Vector2D(19.0f/26 + 2.0f, 19.0f/13 - 4.0f)});
    std::vector<Geometry::Vector2D> intersections = polygonBase.getIntersections(intersectionLine);

//    for (uint i = 0; i < inter.size(); i++) {
//        spdlog::info("{}st interception: coord. x: {}; coord. y: {}", i+1, inter[i].x(), inter[i].y());
//    }
    ASSERT_EQ(polIntersections.size(), intersections.size()) << "Wrong polygon intersections quantity";
    for(const auto& polIntersection : polIntersections) {
        EXPECT_NE(std::find(intersections.begin(), intersections.end(), polIntersection), std::end(intersections))
                << "Polygon intersections do not match";
    }
}
