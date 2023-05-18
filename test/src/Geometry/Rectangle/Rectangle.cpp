#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Armorial/Geometry/Rectangle/Rectangle.h>
#include <spdlog/spdlog.h>

Geometry::Rectangle rectangleBase(Geometry::Vector2D(-2.0f, 1.0f), Geometry::Vector2D(2.0f, -1.0f));

TEST(Geometry_Rectangle_Tests, GivenARectangle_WidthGetter_ShouldWork) {
    float rectangleWidth = 4.0f;
    ASSERT_GE(rectangleBase.width(), 0.0f) << "Rectangle width has a negative value";
    EXPECT_FLOAT_EQ(rectangleBase.width(), rectangleWidth) << "Rectangle width does not match";
}

TEST(Geometry_Rectangle_Tests, GivenARectangle_HeightGetter_ShouldWork) {
    float rectangleHeight = 2.0f;
    ASSERT_GE(rectangleBase.height(), 0.0f) << "Rectangle height has a negative value";
    EXPECT_FLOAT_EQ(rectangleBase.height(), rectangleHeight) << "Rectangle width does not match";
}

TEST(Geometry_Rectangle_Tests, GivenARectangle_CenterGetter_ShouldWork) {
    Geometry::Vector2D rectangleCenter(0.0f, 0.0f);
    EXPECT_EQ(rectangleBase.center(), rectangleCenter) << "Rectangle center does not match";
}

TEST(Geometry_Rectangle_Tests, GivenARectangle_TopLeftCorner_ShouldWork) {
    Geometry::Vector2D topLeftCorner(-2.0f, 1.0f);
    EXPECT_EQ(rectangleBase.topLeft(), topLeftCorner) << "Top left corner does not match";
}

TEST(Geometry_Rectangle_Tests, GivenARectangle_TopRightCorner_ShouldWork) {
    Geometry::Vector2D topRightCorner(2.0f, 1.0f);
    EXPECT_EQ(rectangleBase.topRight(), topRightCorner) << "Top right corner does not match";
}

TEST(Geometry_Rectangle_Tests, GivenARectangle_BottomLeftCorner_ShouldWork) {
    Geometry::Vector2D bottomLeftCorner(-2.0f, -1.0f);
    EXPECT_EQ(rectangleBase.bottomLeft(), bottomLeftCorner) << "Bottom left corner does not match";
}

TEST(Geometry_Rectangle_Tests, GivenARectangle_BottomRightCorner_ShouldWork) {
    Geometry::Vector2D bottomRightCorner(2.0f, -1.0f);
    EXPECT_EQ(rectangleBase.bottomRight(), bottomRightCorner) << "Bottom right corner does not match";
}

TEST(Geometry_Rectangle_Tests, GivenARectangle_TopLine_ShouldWork) {
    Geometry::LineSegment topLine(Geometry::Vector2D(-2.0f, 1.0f), Geometry::Vector2D(2.0f, 1.0f));
    EXPECT_EQ(rectangleBase.topLine(), topLine) << "Top line does not match";
}

TEST(Geometry_Rectangle_Tests, GivenARectangle_BottomLine_ShouldWork) {
    Geometry::LineSegment bottomLine(Geometry::Vector2D(-2.0f, -1.0f), Geometry::Vector2D(2.0f, -1.0f));
    EXPECT_EQ(rectangleBase.bottomLine(), bottomLine) << "Bottom line does not match";
}

TEST(Geometry_Rectangle_Tests, GivenARectangle_LeftLine_ShouldWork) {
    Geometry::LineSegment leftLine(Geometry::Vector2D(-2.0f, 1.0f), Geometry::Vector2D(-2.0f, -1.0f));
    EXPECT_EQ(rectangleBase.leftLine(), leftLine) << "Left line does not match";
}

TEST(Geometry_Rectangle_Tests, GivenARectangle_RightLine_ShouldWork) {
    Geometry::LineSegment rightLine(Geometry::Vector2D(2.0f, 1.0f), Geometry::Vector2D(2.0f, -1.0f));
    EXPECT_EQ(rectangleBase.rightLine(), rightLine) << "Right line does not match";
}

TEST(Geometry_Rectangle_Tests, GivenARectangle_BoundaryGetter_ShouldWork) {
    std::vector<Geometry::LineSegment> rectangleBoundary = {
        Geometry::LineSegment(Geometry::Vector2D(-2.0f, 1.0f), Geometry::Vector2D(2.0f, 1.0f)),
        Geometry::LineSegment(Geometry::Vector2D(-2.0f, -1.0f), Geometry::Vector2D(2.0f, -1.0f)),
        Geometry::LineSegment(Geometry::Vector2D(-2.0f, 1.0f), Geometry::Vector2D(-2.0f, -1.0f)),
        Geometry::LineSegment(Geometry::Vector2D(2.0f, 1.0f), Geometry::Vector2D(2.0f, -1.0f))};
    std::vector<Geometry::LineSegment> boundary = rectangleBase.boundary();

    ASSERT_EQ(boundary.size(), rectangleBoundary.size()) << "Wrong boundary lines quantity";
    for(const auto& rectangleLine : rectangleBoundary) {
        EXPECT_NE(std::find(boundary.begin(), boundary.end(), rectangleLine), std::end(boundary)) << "Line does not match";
    }
}

TEST(Geometry_Rectangle_Tests, GivenARectangle_PointInRectangleChecker_ShouldWork) {
    Geometry::Vector2D referencePoint1(0.0f, 0.0f);
    Geometry::Vector2D referencePoint2(0.0f, 1.0f);
    Geometry::Vector2D referencePoint3(0.0f, 2.0f);
    EXPECT_EQ(rectangleBase.contains(referencePoint1), true) << "Rectangle does not contain the point";
    EXPECT_EQ(rectangleBase.contains(referencePoint2), true) << "Rectangle does not contain the point";
    EXPECT_EQ(rectangleBase.contains(referencePoint3), false) << "Rectangle contains the point";
    EXPECT_EQ(rectangleBase.contains(referencePoint3, 1.0f), true) << "Rectangle does not contain the point";
}

TEST(Geometry_Rectangle_Tests, GivenARectangle_UpdatingCorners_ShouldWork) {
    rectangleBase.updateCorners(Geometry::Vector2D(0.0f, 4.0f), Geometry::Vector2D(1.0f, 0.0f));
    Geometry::Rectangle referenceRectangle(Geometry::Vector2D(0.0f, 4.0f), Geometry::Vector2D(1.0f, 0.0f));
    EXPECT_EQ(rectangleBase, referenceRectangle) << "Update rectangle do not work";
}
