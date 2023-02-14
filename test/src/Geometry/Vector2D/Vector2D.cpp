#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Armorial/Geometry/Vector2D/Vector2D.h>
#include <spdlog/spdlog.h>
#include <fmt/color.h>

TEST(Geometry_Vector2D_Tests, GivenAVector_CoordinateGetters_ShouldWork) {
    Geometry::Vector2D vectorBase(1.0f, 1.0f);
    {
        SCOPED_TRACE("Coordinate X");
        EXPECT_EQ(vectorBase.x(), 1.0f);
    }
    {
        SCOPED_TRACE("Coordinate Y");
        EXPECT_EQ(vectorBase.y(), 1.0f);
    }
}

TEST(Geometry_Vector2D_Tests, GivenAVector_DistanceToPoint_ShouldWork) {
    Geometry::Vector2D vectorBase(1.0f, 0.0f);
    ASSERT_GE(vectorBase.dist(Geometry::Vector2D(0.0f, 0.0f)), 0.0f) << "Distance of points has a negative value";
    EXPECT_FLOAT_EQ(vectorBase.dist(Geometry::Vector2D(0.0f, 0.0f)), 1.0f) << "Distance value does not match";
}
TEST(Geometry_Vector2D_Tests, GivenAVector_VectorLength_ShouldWork) {
    Geometry::Vector2D vectorBase(1.0f, 1.0f);
    ASSERT_GE(vectorBase.length(), 0.0f) << "Distance of points has a negative value";
    EXPECT_FLOAT_EQ(vectorBase.length(), sqrtf(2)) << "Distance value does not match";
}

TEST(Geometry_Vector2D_Tests, GivenAVector_DotProduct_ShouldWork) {
    Geometry::Vector2D vectorBase1(1.0f, 0.0f);
    Geometry::Vector2D vectorBase2(0.0f, 1.0f);
    Geometry::Vector2D vectorBase3(1.0f, 1.0f);
    EXPECT_EQ(vectorBase1.dotProduct(vectorBase2), 0.0f) << "Dot Product does not match (should be 0)";
    EXPECT_EQ(vectorBase2.dotProduct(vectorBase3), 1.0f) << "Dot Product does not match (should be 1)";
    EXPECT_EQ(vectorBase3.dotProduct(vectorBase3), 2.0f) << "Dot Product does not match (should be 2)";
}

TEST(Geometry_Vector2D_Tests, GivenAVector_CrossProduct_ShouldWork) {
    Geometry::Vector2D vectorBase1(1.0f, 0.0f);
    Geometry::Vector2D vectorBase2(0.0f, 1.0f);
    Geometry::Vector2D vectorBase3(1.0f, 1.0f);
    EXPECT_EQ(vectorBase1.crossProductMagnitude(vectorBase2), 1.0f) << "Cross Product does not match (should be 1)";
    EXPECT_EQ(vectorBase2.crossProductMagnitude(vectorBase3), 1.0f) << "Cross Product does not match (should be 1)";
    EXPECT_EQ(vectorBase3.crossProductMagnitude(vectorBase3), 0.0f) << "Cross Product does not match (should be 0)";
}

TEST(Geometry_Vector2D_Tests, GivenAVector_Scalation_ShouldWork) {
    Geometry::Vector2D vectorBase(1.0f, 0.0f);
    EXPECT_EQ(vectorBase.scale(2), Geometry::Vector2D(2.0f, 0.0f)) << "Scalation failed";
}

TEST(Geometry_Vector2D_Tests, GivenANonNullVector_Normalization_ShouldWork) {
    Geometry::Vector2D vectorBase(1.0f, 1.0f);
    EXPECT_EQ(vectorBase.normalize(), Geometry::Vector2D(sqrtf(2)/2, sqrtf(2)/2)) << "Normalization failed";
}

TEST(Geometry_Vector2D_Tests, GivenANullVector_Normalization_ShouldFail) {
    Geometry::Vector2D vectorBase(0.0f, 0.0f);
    EXPECT_EQ(vectorBase.normalize(), Geometry::Vector2D(0.0f, 0.0f));
}

TEST(Geometry_Vector2D_Tests, GivenANonNullVector_StretchToLength_ShouldWork) {
    Geometry::Vector2D vectorBase(1.0f, 1.0f);
    EXPECT_EQ(vectorBase.stretchToLength(sqrtf(8)), Geometry::Vector2D(2.0f, 2.0f)) << "Stretchion failed";
}

TEST(Geometry_Vector2D_Tests, GivenANullVector_StretchToLength_ShouldFail) {
    Geometry::Vector2D vectorBase(0.0f, 0.0f);
    EXPECT_EQ(vectorBase.stretchToLength(5.0f), Geometry::Vector2D(0.0f, 0.0f));
}

TEST(Geometry_Vector2D_Tests, GivenAVector_GetAngle_ShouldWork) {
    Geometry::Vector2D vectorBase(1.0f, 1.0f);
    EXPECT_FLOAT_EQ(vectorBase.angle(), M_PI_4) << "Vector angle value do not match";
}

TEST(Geometry_Vector2D_Tests, GivenAVector_Angulization_ShouldWork) {
    Geometry::Vector2D vectorBase(1.0f, 1.0f);
    EXPECT_EQ(vectorBase.toAngle(), Geometry::Angle(M_PI_4)) << "Vector angle do not match";
}

TEST(Geometry_Vector2D_Tests, GivenAVector_RotationFromOrigin_ShouldWork) {
    Geometry::Vector2D vectorBase1(sqrtf(2), 0.0f);
    Geometry::Vector2D vectorBase2(1.0f, 1.0f);
    EXPECT_EQ(vectorBase1.rotate(M_PI_4), Geometry::Vector2D(1.0f, 1.0f)) << "Vector rotation do not match";
    EXPECT_EQ(vectorBase2.rotate(-M_PI_2), Geometry::Vector2D(1.0f, -1.0f)) << "Vector rotation do not match";
}

TEST(Geometry_Vector2D_Tests, GivenAVector_RotationFromPoint_ShouldWork) {
    Geometry::Vector2D vectorBase1(0.0f, 0.0f);
    Geometry::Vector2D vectorBase2(1.0f, 1.0f);
    Geometry::Vector2D referencePoint(2.0f, 2.0f);
    EXPECT_EQ(vectorBase1.rotateAroundPoint(-M_PI_2, referencePoint), Geometry::Vector2D(0.0f, 4.0f)) << "Vector rotation from point do not match";
    EXPECT_EQ(vectorBase2.rotateAroundPoint(M_PI, referencePoint), Geometry::Vector2D(3.0f, 3.0f)) << "Vector rotation from point do not match";
}

TEST(Geometry_Vector2D_Tests, GivenAVector_ProjectionWithLine_ShouldWork) {
    Geometry::Vector2D vectorBase1(0.0f, 0.0f);
    Geometry::Vector2D vectorBase2(2.0f - 2*sqrtf(3), 2.0f);
    EXPECT_EQ(vectorBase1.project(Geometry::Vector2D(1.0f, 0.0f), Geometry::Vector2D(0.0f, -1.0f)),
              Geometry::Vector2D(0.5f, -0.5f)) << "Vector projection do not work";
    EXPECT_EQ(vectorBase2.project(Geometry::Vector2D(3.0f, sqrtf(3)), Geometry::Vector2D(1.0f, -sqrtf(3))),
              Geometry::Vector2D(2.0f, 0.0f)) << "Vector projection do not work";
}

TEST(Geometry_Vector2D_Tests, GivenAVector_OperatorsWithVectors_ShouldWork) {
    Geometry::Vector2D vectorBase(1.0f, 1.0f);
    {
        SCOPED_TRACE("Vectors sum");

        Geometry::Vector2D vectorSum(sqrtf(3) + 1.0f, 1.0f + M_PI);
        EXPECT_EQ(vectorBase + Geometry::Vector2D(sqrtf(3), M_PI), vectorSum);
    }
    {
        SCOPED_TRACE("Vectors subtraction");

        Geometry::Vector2D vectorSubtraction(1.0f - sqrtf(3), 1.0f - M_PI);
        EXPECT_EQ(vectorBase - Geometry::Vector2D(sqrtf(3), M_PI), vectorSubtraction);
    }
    {
        SCOPED_TRACE("Vectors multiplication");

        Geometry::Vector2D vectorMultiplication(sqrtf(3), M_PI);
        EXPECT_EQ(vectorBase * Geometry::Vector2D(sqrtf(3), M_PI), vectorMultiplication);
    }
    {
        SCOPED_TRACE("Vectors division");

        Geometry::Vector2D vectorDivision(1.0f/sqrtf(3), 1.0f/M_PI);
        EXPECT_EQ(vectorBase / Geometry::Vector2D(sqrtf(3), M_PI), vectorDivision);
    }
}

TEST(Geometry_Vector2D_Tests, GivenAVector_OperatorsWithScalars_ShouldWork) {
    Geometry::Vector2D vectorBase(1.0f, 1.0f);
    {
        SCOPED_TRACE("Vector sum");

        Geometry::Vector2D vectorSum(4.0f, 4.0f);
        EXPECT_EQ(vectorBase + 3.0f, vectorSum);
    }
    {
        SCOPED_TRACE("Vector subtraction");

        Geometry::Vector2D vectorSubtraction(-2.0f, -2.0f);
        EXPECT_EQ(vectorBase - 3.0f, vectorSubtraction);
    }
    {
        SCOPED_TRACE("Vector multiplication");

        Geometry::Vector2D vectorMultiplication(M_PI, M_PI);
        EXPECT_EQ(vectorBase * M_PI, vectorMultiplication);
    }
    {
        SCOPED_TRACE("Vector division");

        Geometry::Vector2D vectorDivision(0.5f, 0.5f);
        EXPECT_EQ(vectorBase / 2.0f, vectorDivision);
    }
}

TEST(Geometry_Vector2D_Tests, GivenAVector_DivisionWithNullParametersVector_ShouldFail) {
    Geometry::Vector2D vectorBase(1.0f, 1.0f);
    {
        SCOPED_TRACE("Null coordinate X");
        Geometry::Vector2D vectorDivision = vectorBase / Geometry::Vector2D(0.0f, 1.0f);
        EXPECT_EQ(std::isinf(vectorDivision.x()), true);
    }
    {
        SCOPED_TRACE("Null coordinate Y");
        Geometry::Vector2D vectorDivision = vectorBase / Geometry::Vector2D(1.0f, 0.0f);
        EXPECT_EQ(std::isinf(vectorDivision.y()), true);
    }
    {
        SCOPED_TRACE("Nulls coordinate X and Y");
        Geometry::Vector2D vectorDivision = vectorBase / Geometry::Vector2D(0.0f, 0.0f);
        EXPECT_EQ(std::isinf(vectorDivision.x()), true);
        EXPECT_EQ(std::isinf(vectorDivision.y()), true);
    }
}

TEST(Geometry_Vector2D_Tests, GivenAVector_DivisionWithNullScalar_ShouldFail) {
    Geometry::Vector2D vectorBase(1.0f, 1.0f);
    Geometry::Vector2D vectorDivision = vectorBase / 0.0f;
    EXPECT_EQ(std::isinf(vectorDivision.x()), true);
    EXPECT_EQ(std::isinf(vectorDivision.y()), true);
}
