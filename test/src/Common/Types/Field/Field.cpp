#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>
#include <gmock/gmock.h>
#include <spdlog/spdlog.h>
#include <fmt/color.h>

#include <Armorial/Common/Types/Field/Field.h>
using namespace Common::Types;

// Getters and Constructor Tests (GC) //
TEST(Common_Field_Test, GivenField_ConstructorGetters_ShouldWork){
    float centerRadius = 50.0f,
          field_length = 1000.0f, field_width = 500.0f,
          goal_depth = 10.0f, goal_width = 30.0f,
          penalty_depth = 100.0f, penalty_width = 50.0f,
          penalty_MarkDistance = 75.0f;

    Field Teste_Field = Field(Common::Enums::SIDE_LEFT, centerRadius, field_length, field_width,
            goal_depth,goal_width, penalty_depth,penalty_width,penalty_MarkDistance);

    EXPECT_EQ(Teste_Field.playingLeftSide(),true);
    EXPECT_FLOAT_EQ(Teste_Field.centerRadius(), centerRadius);
    EXPECT_FLOAT_EQ(Teste_Field.length(),field_length);
    EXPECT_FLOAT_EQ(Teste_Field.width(),field_width);
    EXPECT_FLOAT_EQ(Teste_Field.goalDepth(),goal_depth);
    EXPECT_FLOAT_EQ(Teste_Field.goalWidth(),goal_width);
    EXPECT_FLOAT_EQ(Teste_Field.penaltyDepth(),penalty_depth);
    EXPECT_FLOAT_EQ(Teste_Field.penaltyWidth(),penalty_width);
    EXPECT_FLOAT_EQ(Teste_Field.penaltyMarkDistanceFromGoal(),penalty_MarkDistance);
}

TEST(Common_Field_Test, Field_Cricle_ShouldWork){
    float centerRadius = 50.0f;

    Geometry::Circle Circle(Geometry::Vector2D(0, 0), centerRadius);
    Field Teste_Field = Field(Common::Enums::SIDE_LEFT, centerRadius, 1000.0f, 500.0f,
                                  10.0f,30.0f, 100.0f,50.0f,75.0f);

    EXPECT_EQ(Teste_Field.centerCircle(), Circle);
}

TEST(Common_Field_Test, Field_PlayingSide_ShouldWork){
    Field Teste_Field1 = Field(Common::Enums::SIDE_LEFT, 50.0f, 1000.0f, 500.0f,
                                  10.0f,30.0f, 10.0f, 30.0f,75.0f);
    Field Teste_Field2 = Field(Common::Enums::SIDE_RIGHT, 50.0f, 1000.0f, 500.0f,
                                  10.0f,30.0f, 10.0f, 30.0f,75.0f);

    EXPECT_EQ(Teste_Field1.playingLeftSide(), true) << "Field 1 returning False when should be True";
    EXPECT_EQ(Teste_Field2.playingLeftSide(), false) << "Field 2 returning True when should be False";
}

TEST(Common_Field_Test, Field_MinMaxX_ShouldWork){
    Field Teste_Field = Field(Common::Enums::SIDE_LEFT, 50.0f, 1000.0f, 500.0f, 10.0f,30.0f, 100.0f,50.0f,75.0f);
    EXPECT_FLOAT_EQ(Teste_Field.minX(), -500.0f) << "Min is not working";
    EXPECT_FLOAT_EQ(Teste_Field.maxX(), 500.0f) << "Max is not working";
}

TEST(Common_Field_Test, Field_MinMaxY_ShouldWork){
    Field Teste_Field = Field(Common::Enums::SIDE_LEFT, 50.0f, 1000.0f, 500.0f, 10.0f,30.0f, 100.0f,50.0f,75.0f);
    EXPECT_FLOAT_EQ(Teste_Field.minY(), -250.0f)  << "Min is not working";
    EXPECT_FLOAT_EQ(Teste_Field.maxY(), 250.0f)  << "Max is not working";
}

TEST(Common_Field_Test, Our_and_Their_Field_Should_Work){
    Field Teste_Field = Field(Common::Enums::SIDE_LEFT, 50.0f, 1000.0f, 500.0f,
                                  10.0f,30.0f, 100.0f,50.0f,75.0f);
    Field Teste_Field2 = Field(Common::Enums::SIDE_RIGHT, 50.0f, 1000.0f, 500.0f,
                                  10.0f,30.0f, 100.0f,50.0f,75.0f);

    Geometry::Rectangle leftField(Geometry::Vector2D(-500.0f,250.0f), Geometry::Vector2D(0.0f, -250.0f));
    Geometry::Rectangle rightField(Geometry::Vector2D(0.0f, 250.0f), Geometry::Vector2D(500.0f,-250.0f));

    Geometry::Rectangle ourField = Teste_Field.ourField();
    Geometry::Rectangle ourField2 = Teste_Field2.ourField();
    Geometry::Rectangle theirField = Teste_Field.theirField();
    Geometry::Rectangle theirField2 = Teste_Field2.theirField();

    {
        SCOPED_TRACE("[CommonFieldTest] Geometry::Rectangle Field::ourField() const "
                                 "===> Our field should return the correct rectangle");

        EXPECT_TRUE(ourField == leftField);
        EXPECT_TRUE(ourField2 == rightField);
    }

    {
        SCOPED_TRACE("[CommonFieldTest] Geometry::Rectangle Field::theirField() const "
                                 "===> Their field should return the correct rectangle");

        EXPECT_TRUE(theirField == rightField);
        EXPECT_TRUE(theirField2 == leftField);
    }

}

// Field Rectangle Methods Tests (FR)//

TEST(Common_Field_Test, Field_Rectangle_ShouldWork){
    float field_length = 1000.0f, field_width = 500.0f;

    Geometry::Vector2D topLeft(-field_length/2.0, field_width/2.0);
    Geometry::Vector2D bottomRight(field_length/2.0, -field_width/2.0);
    Geometry::Rectangle Rect(topLeft,bottomRight);

    Field Teste_Field = Field(Common::Enums::SIDE_LEFT, 50.0f, field_length, field_width,
                                  10.0f,30.0f, 100.0f,50.0f,75.0f);

    EXPECT_EQ(Teste_Field.field(), Rect);
}

TEST(Common_Field_Test, LeftField_Rectangle_ShouldWork){
    float field_length = 1000.0f, field_width = 500.0f;

    Geometry::Vector2D topLeft(-field_length/2.0, field_width/2.0);
    Geometry::Vector2D midBottomRight(0.0f, -field_width/2.0);
    Geometry::Rectangle Rect(topLeft,midBottomRight);

    Field Teste_Field = Field(Common::Enums::SIDE_LEFT, 50.0f, field_length, field_width,
                                  10.0f,30.0f, 100.0f,50.0f,75.0f);

    EXPECT_EQ(Teste_Field.leftField(), Rect);
}

TEST(Common_Field_Test, RightField_Rectangle_ShouldWork){
    float field_length = 1000.0f, field_width = 500.0f;

    Geometry::Vector2D topLeft(0.0f, field_width/2.0);
    Geometry::Vector2D midBottomRight(field_length/2.0, -field_width/2.0);
    Geometry::Rectangle Rect(topLeft,midBottomRight);

    Field Teste_Field = Field(Common::Enums::SIDE_LEFT, 50.0f, field_length, field_width,
                                  10.0f,30.0f, 100.0f,50.0f,75.0f);

    EXPECT_EQ(Teste_Field.rightField(), Rect);
}

TEST(Common_Field_Test, LeftPenalty_Rectangle_ShouldWork){
    float field_length = 1000.0f, penalty_width = 50.0f, penalty_depth = 100.0f;

    Geometry::Vector2D leftPenaltyTopLeftCorner(-field_length/2.0, penalty_width/2.0);
    Geometry::Vector2D leftPenaltyBottomRightCorner(-field_length/2.0 + penalty_depth, -penalty_width/2.0);
    Geometry::Rectangle Rect (leftPenaltyTopLeftCorner, leftPenaltyBottomRightCorner);

    Field Teste_Field = Field(Common::Enums::SIDE_LEFT, 50.0f, field_length, 500.0f,
                                  10.0f,30.0f, penalty_depth,penalty_width,75.0f);

    EXPECT_EQ(Teste_Field.leftPenaltyArea(), Rect);
}

TEST(Common_Field_Test, RightPenalty_Rectangle_ShouldWork){
    float field_length = 1000.0f, penalty_width = 50.0f, penalty_depth = 100.0f;

    Geometry::Vector2D leftPenaltyTopLeftCorner(field_length/2.0 - penalty_depth, penalty_width/2.0);
    Geometry::Vector2D leftPenaltyBottomRightCorner(field_length/2.0 , -penalty_width/2.0);
    Geometry::Rectangle Rect (leftPenaltyTopLeftCorner, leftPenaltyBottomRightCorner);

    Field Teste_Field = Field(Common::Enums::SIDE_LEFT, 50.0f, field_length, 500.0f,
                                  10.0f,30.0f, penalty_depth, penalty_width,75.0f);

    EXPECT_EQ(Teste_Field.rightPenaltyArea(), Rect);
}

TEST(Common_Field_Test, OurAndTheirPenalty_Rectangle_ShouldWork){
    Field Teste_Field = Field(Common::Enums::SIDE_LEFT, 50.0f, 1000.0f, 500.0f,
                                  10.0f,30.0f, 100.0f,50.0f,75.0f);
    Field Teste_Field2 = Field(Common::Enums::SIDE_RIGHT, 50.0f, 1000.0f, 500.0f,
                                  10.0f,30.0f, 100.0f,50.0f,75.0f);

    Geometry::Rectangle LeftPenaltyArea (Geometry::Vector2D(-500.0f,25.0f), Geometry::Vector2D(-400.0f,-25.0f));
    Geometry::Rectangle RightPenaltyArea (Geometry::Vector2D(400.0f,25.0f), Geometry::Vector2D(500.0f,-25.0f));

    {
        SCOPED_TRACE(fmt::format(fmt::emphasis::bold,
                                 "[CommonFieldTest] Geometry::Rectangle Field::ourPenaltyArea() const ===> Our penalty area should return the correct rectangle"));

        EXPECT_EQ(Teste_Field.ourPenaltyArea(), LeftPenaltyArea);
        EXPECT_EQ(Teste_Field2.ourPenaltyArea(), RightPenaltyArea);
    }

    {
        SCOPED_TRACE(fmt::format(fmt::emphasis::bold,
                                 "[CommonFieldTest] Geometry::Rectangle Field::theirPenaltyArea() const ===> Their penalty area should return the correct rectangle"));

        EXPECT_EQ(Teste_Field2.theirPenaltyArea(), LeftPenaltyArea);
        EXPECT_EQ(Teste_Field.theirPenaltyArea(), RightPenaltyArea);
    }
}

// Field Vector2D Methods Tests (V2D) //

TEST(Common_Field_Test, OurAndTheir_GoalCenter_ShouldWork){
    Field teste_Field = Field(Common::Enums::SIDE_LEFT, 50.0f, 1000.0f, 500.0f,
                                  10.0f,30.0f, 100.0f,50.0f,75.0f);
    Field teste_Field2 = Field(Common::Enums::SIDE_RIGHT, 50.0f, 1000.0f, 500.0f,
                                  10.0f,30.0f, 100.0f,50.0f,75.0f);
    
    { // our Left Side
        Geometry::Vector2D GoalCenter(-teste_Field.length()/2.0f, 0.0f);
        EXPECT_EQ(GoalCenter, teste_Field.ourGoalCenter());
    }
    
    { // our Right Side
        Geometry::Vector2D GoalCenter(teste_Field2.length()/2.0f, 0.0f);
        EXPECT_EQ(GoalCenter, teste_Field2.ourGoalCenter());
    }
    
    { // their Left Side
        Geometry::Vector2D GoalCenter(-teste_Field2.length()/2.0f, 0.0f);
        EXPECT_EQ(GoalCenter, teste_Field2.theirGoalCenter());
    }
    
    { // their Right Side
        Geometry::Vector2D GoalCenter(teste_Field2.length()/2.0f, 0.0f);
        EXPECT_EQ(GoalCenter, teste_Field.theirGoalCenter());
    }
}

TEST(Common_Field_Test, Our_LeftAndRightPosts_ShouldWork){
    Field teste_Field = Field(Common::Enums::SIDE_LEFT, 50.0f, 1000.0f, 500.0f,
                                  10.0f,30.0f, 100.0f,50.0f,75.0f);
    Field teste_Field2 = Field(Common::Enums::SIDE_RIGHT, 50.0f, 1000.0f, 500.0f,
                                  10.0f,30.0f, 100.0f,50.0f,75.0f);
    
    Geometry::Vector2D goalCenterL = teste_Field.ourGoalCenter();
    Geometry::Vector2D goalCenterR = teste_Field2.ourGoalCenter();
    
    float offsetLeftSide = teste_Field.goalWidth()/2;
    float offsetRightSide = -teste_Field.goalWidth()/2;
    
    {
        EXPECT_EQ(teste_Field.ourGoalRightPost(), Geometry::Vector2D(goalCenterL.x(), goalCenterL.y() + offsetLeftSide));
        EXPECT_EQ(teste_Field2.ourGoalRightPost(), Geometry::Vector2D(goalCenterR.x(), goalCenterR.y() + offsetRightSide));
    }
    
    
    {
        EXPECT_EQ(teste_Field.ourGoalLeftPost(), Geometry::Vector2D(goalCenterL.x(), goalCenterL.y() - offsetLeftSide));
        EXPECT_EQ(teste_Field2.ourGoalLeftPost(), Geometry::Vector2D(goalCenterR.x(), goalCenterR.y() - offsetRightSide));
    }
    
}

TEST(Common_Field_Test, Their_LeftAndRightPosts_ShouldWork){
    Field teste_Field = Field(Common::Enums::SIDE_LEFT, 50.0f, 1000.0f, 500.0f,
                                  10.0f,30.0f, 100.0f,50.0f,75.0f);
    Field teste_Field2 = Field(Common::Enums::SIDE_RIGHT, 50.0f, 1000.0f, 500.0f,
                                  10.0f,30.0f, 100.0f,50.0f,75.0f);

    Geometry::Vector2D goalCenterL = teste_Field.theirGoalCenter();
    Geometry::Vector2D goalCenterR = teste_Field2.theirGoalCenter();

    float offsetLeftSide = -teste_Field.goalWidth()/2;
    float offsetRightSide = teste_Field.goalWidth()/2;

    {
        EXPECT_EQ(teste_Field.theirGoalRightPost(), Geometry::Vector2D(goalCenterL.x(), goalCenterL.y() + offsetLeftSide));
        EXPECT_EQ(teste_Field2.theirGoalRightPost(), Geometry::Vector2D(goalCenterR.x(), goalCenterR.y() + offsetRightSide));
    }


    {
        EXPECT_EQ(teste_Field.theirGoalLeftPost(), Geometry::Vector2D(goalCenterL.x(), goalCenterL.y() - offsetLeftSide));
        EXPECT_EQ(teste_Field2.theirGoalLeftPost(), Geometry::Vector2D(goalCenterR.x(), goalCenterR.y() - offsetRightSide));
    }

}

TEST(Common_Field_Test, OurAndTheir_PenaltyMark_Should_Work){
    Field Teste_Field = Field(Common::Enums::SIDE_LEFT, 50.0f, 1000.0f, 500.0f,
                                  10.0f,30.0f, 100.0f,50.0f,75.0f);
    Field Teste_Field2 = Field(Common::Enums::SIDE_RIGHT, 50.0f, 1000.0f, 500.0f,
                                  10.0f,30.0f, 100.0f,50.0f,75.0f);





    {
        SCOPED_TRACE("[CommonFieldTest] Geometry::Vector2D Field::ourPenaltyMark() const "
                     "===> Fuction should return correct vector2D using the left side");

        Geometry::Vector2D goalCenter1 = Teste_Field.theirGoalCenter();
        float offset1 = (Teste_Field.playingLeftSide() ? -Teste_Field.penaltyMarkDistanceFromGoal() : Teste_Field.penaltyMarkDistanceFromGoal());

        Geometry::Vector2D mark1(goalCenter1.x() - offset1, goalCenter1.y());

        EXPECT_EQ(Teste_Field.ourPenaltyMark(), mark1);
    }

    {
        SCOPED_TRACE("[CommonFieldTest] Geometry::Vector2D Field::ourPenaltyMark() const "
                                 "===> Fuction should return correct vector2D using the right side");

        Geometry::Vector2D goalCenter2 = Teste_Field2.theirGoalCenter();
        float offset2 = (Teste_Field2.playingLeftSide() ? -Teste_Field2.penaltyMarkDistanceFromGoal() : Teste_Field2.penaltyMarkDistanceFromGoal());

        Geometry::Vector2D mark2(goalCenter2.x() - offset2, goalCenter2.y());

        EXPECT_EQ(Teste_Field2.ourPenaltyMark(), mark2);
    }

    //Their Penalty Mark

    {
        SCOPED_TRACE("[CommonFieldTest] Geometry::Vector2D Field::theirPenaltyMark() const "
                                 "===> Fuction should return correct vector2D using the left side");

        Geometry::Vector2D goalCenter1 = Teste_Field.ourGoalCenter();
        float offset1 = (Teste_Field.playingLeftSide() ? Teste_Field.penaltyMarkDistanceFromGoal() : -Teste_Field.penaltyMarkDistanceFromGoal());

        Geometry::Vector2D mark1(goalCenter1.x() - offset1, goalCenter1.y());

        EXPECT_EQ(Teste_Field.theirPenaltyMark(), mark1);
    }

    {
        SCOPED_TRACE("[CommonFieldTest] Geometry::Vector2D Field::theirPenaltyMark() const "
                     "===> Fuction should return correct vector2D using the right side");

        Geometry::Vector2D goalCenter2 = Teste_Field2.ourGoalCenter();
        float offset2 = (Teste_Field2.playingLeftSide() ? Teste_Field2.penaltyMarkDistanceFromGoal() : -Teste_Field2.penaltyMarkDistanceFromGoal());

        Geometry::Vector2D mark2(goalCenter2.x() - offset2, goalCenter2.y());

        EXPECT_EQ(Teste_Field2.theirPenaltyMark(), mark2);
    }
}

TEST(Common_Field_Test, Quadrants_Should_Work){
    Field Teste_Field = Field(Common::Enums::SIDE_LEFT, 50.0f, 900.0f, 600.0f,
                                  10.0f,30.0f, 100.0f,50.0f,75.0f);
    float width = 600.0f;
    float length = 900.0f;

    Geometry::Rectangle FirstQ({0.0, width / 2.0f}, {length / 2.0f, 0.0});
    Geometry::Rectangle SecondQ({-(length / 2.0f), width / 2.0f}, {0.0, 0.0});
    Geometry::Rectangle ThirdQ({-(length / 2.0f), 0.0}, {0.0, -(width / 2.0f)});
    Geometry::Rectangle FourthQ({0.0, 0.0}, {length / 2.0f, -(width / 2.0f)});

    EXPECT_EQ(FirstQ, Teste_Field.topRightQuadrant());
    EXPECT_EQ(SecondQ, Teste_Field.topLeftQuadrant());
    EXPECT_EQ(ThirdQ, Teste_Field.bottomLeftQuadrant());
    EXPECT_EQ(FourthQ, Teste_Field.bottomRightQuadrant());
}

TEST(Common_Field_Test, Corners_Should_Work) {
    Field Teste_Field = Field(Common::Enums::SIDE_LEFT, 50.0f, 900.0f, 600.0f,
                              10.0f,30.0f, 100.0f,50.0f,75.0f);
    float width = 600.0f;
    float length = 900.0f;

    Geometry::Vector2D TopLeftC(-length / 2.0f, width / 2.0f);
    Geometry::Vector2D TopRightC(length / 2.0f, width / 2.0f);
    Geometry::Vector2D BottomLeftC(-length / 2.0f, -width / 2.0f);
    Geometry::Vector2D BottomRightC(length / 2.0f, -width / 2.0f);

    EXPECT_EQ(TopLeftC, Teste_Field.topLeftCorner());
    EXPECT_EQ(TopRightC, Teste_Field.topRightCorner());
    EXPECT_EQ(BottomLeftC, Teste_Field.bottomLeftCorner());
    EXPECT_EQ(BottomRightC, Teste_Field.bottomRightCorner());
}

TEST(Common_Field_Test, isInsideField_Should_Work) {
    Field Teste_Field = Field(Common::Enums::SIDE_LEFT, 50.0f, 900.0f, 600.0f,
                              10.0f,30.0f, 100.0f,50.0f,75.0f);
    float width = 600.0f;
    float length = 900.0f;

    Geometry::Vector2D insidePointQ1(-length / 4.0f, width / 4.0f);
    Geometry::Vector2D insidePointQ2(length / 4.0f, width / 4.0f);
    Geometry::Vector2D insidePointQ3(-length / 4.0f, -width / 4.0f);
    Geometry::Vector2D insidePointQ4(length / 4.0f, -width / 4.0f);

    Geometry::Vector2D outsidePointQ1(-length, width);
    Geometry::Vector2D outsidePointQ2(length, width);
    Geometry::Vector2D outsidePointQ3(-length, -width);
    Geometry::Vector2D outsidePointQ4(length, -width);

    EXPECT_TRUE(Teste_Field.isInsideField(insidePointQ1));
    EXPECT_TRUE(Teste_Field.isInsideField(insidePointQ2));
    EXPECT_TRUE(Teste_Field.isInsideField(insidePointQ3));
    EXPECT_TRUE(Teste_Field.isInsideField(insidePointQ4));

    EXPECT_FALSE(Teste_Field.isInsideField(outsidePointQ1));
    EXPECT_FALSE(Teste_Field.isInsideField(outsidePointQ2));
    EXPECT_FALSE(Teste_Field.isInsideField(outsidePointQ3));
    EXPECT_FALSE(Teste_Field.isInsideField(outsidePointQ4));
}

TEST(Common_Field_Test, isInsideOurPenaltyArea_Should_Work) {
    Field Teste_Field = Field(Common::Enums::SIDE_LEFT, 50.0f, 900.0f, 600.0f,
                              10.0f,30.0f, 100.0f,50.0f,75.0f);
    float length = 900.0f;
    float penaltyDistanceFromGoal = 75.0f;
    float penaltyWidth = 50.0f;
    float ourSide = Teste_Field.playingLeftSide() ? -1.0f : 1.0f;

    Geometry::Vector2D insidePoint(ourSide*((length / 2.0f) - penaltyDistanceFromGoal), penaltyWidth / 4.0f);

    Geometry::Vector2D outsidePoint1((-ourSide)*((length / 2.0f) - penaltyDistanceFromGoal), penaltyWidth / 4.0f);
    Geometry::Vector2D outsidePoint2(ourSide*((length / 2.0f) - penaltyDistanceFromGoal), penaltyWidth * 2.0f);
    Geometry::Vector2D outsidePoint3((-ourSide)*((length / 2.0f) - penaltyDistanceFromGoal), penaltyWidth * 2.0f);

    EXPECT_TRUE(Teste_Field.isInsideOurPenaltyArea(insidePoint));

    EXPECT_FALSE(Teste_Field.isInsideOurPenaltyArea(outsidePoint1));
    EXPECT_FALSE(Teste_Field.isInsideOurPenaltyArea(outsidePoint2));
    EXPECT_FALSE(Teste_Field.isInsideOurPenaltyArea(outsidePoint3));
}

TEST(Common_Field_Test, isInsideTheirPenaltyArea_Should_Work) {
    Field Teste_Field = Field(Common::Enums::SIDE_LEFT, 50.0f, 900.0f, 600.0f,
                              10.0f,30.0f, 100.0f,50.0f,75.0f);
    float length = 900.0f;
    float penaltyDistanceFromGoal = 75.0f;
    float penaltyWidth = 50.0f;
    float ourSide = Teste_Field.playingLeftSide() ? 1.0f : -1.0f;

    Geometry::Vector2D insidePoint(ourSide*((length / 2.0f) - penaltyDistanceFromGoal), penaltyWidth / 4.0f);

    Geometry::Vector2D outsidePoint1((-ourSide)*((length / 2.0f) - penaltyDistanceFromGoal), penaltyWidth / 4.0f);
    Geometry::Vector2D outsidePoint2(ourSide*((length / 2.0f) - penaltyDistanceFromGoal), penaltyWidth * 2.0f);
    Geometry::Vector2D outsidePoint3((-ourSide)*((length / 2.0f) - penaltyDistanceFromGoal), penaltyWidth * 2.0f);

    EXPECT_TRUE(Teste_Field.isInsideTheirPenaltyArea(insidePoint));

    EXPECT_FALSE(Teste_Field.isInsideTheirPenaltyArea(outsidePoint1));
    EXPECT_FALSE(Teste_Field.isInsideTheirPenaltyArea(outsidePoint2));
    EXPECT_FALSE(Teste_Field.isInsideTheirPenaltyArea(outsidePoint3));
}

TEST(Common_Field_Test, isInsideOurField_Should_Work) {
    Field Teste_Field = Field(Common::Enums::SIDE_LEFT, 50.0f, 900.0f, 600.0f,
                              10.0f,30.0f, 100.0f,50.0f,75.0f);
    float width = 600.0f;
    float length = 900.0f;
    float ourSide = Teste_Field.playingLeftSide() ? -1.0f : 1.0f;

    Geometry::Vector2D insidePoint1((length / 4.0f)*ourSide, width / 4.0f);
    Geometry::Vector2D insidePoint2((length / 4.0f)*ourSide, -width / 4.0f);

    Geometry::Vector2D outsidePoint1((length / 4.0f)*(-ourSide), width / 4.0f);
    Geometry::Vector2D outsidePoint2((length / 4.0f)*(-ourSide), -width / 4.0f);
    Geometry::Vector2D outsidePoint3((length / 4.0f)*ourSide, width * 2.0f);
    Geometry::Vector2D outsidePoint4((length / 4.0f)*ourSide, -width * 2.0f);

    EXPECT_TRUE(Teste_Field.isInsideOurField(insidePoint1));
    EXPECT_TRUE(Teste_Field.isInsideOurField(insidePoint2));

    EXPECT_FALSE(Teste_Field.isInsideOurField(outsidePoint1));
    EXPECT_FALSE(Teste_Field.isInsideOurField(outsidePoint2));
    EXPECT_FALSE(Teste_Field.isInsideOurField(outsidePoint3));
    EXPECT_FALSE(Teste_Field.isInsideOurField(outsidePoint4));
}

TEST(Common_Field_Test, isInsideTheirField_Should_Work) {
    Field Teste_Field = Field(Common::Enums::SIDE_LEFT, 50.0f, 900.0f, 600.0f,
                              10.0f,30.0f, 100.0f,50.0f,75.0f);
    float width = 600.0f;
    float length = 900.0f;
    float ourSide = Teste_Field.playingLeftSide() ? 1.0f : -1.0f;

    Geometry::Vector2D insidePoint1((length / 4.0f)*ourSide, width / 4.0f);
    Geometry::Vector2D insidePoint2((length / 4.0f)*ourSide, -width / 4.0f);

    Geometry::Vector2D outsidePoint1((length / 4.0f)*(ourSide*-1.0f), width / 4.0f);
    Geometry::Vector2D outsidePoint2((length / 4.0f)*(ourSide*-1.0f), -width / 4.0f);
    Geometry::Vector2D outsidePoint3((length / 4.0f)*ourSide, width * 2.0f);
    Geometry::Vector2D outsidePoint4((length / 4.0f)*ourSide, -width * 2.0f);

    EXPECT_TRUE(Teste_Field.isInsideTheirField(insidePoint1));
    EXPECT_TRUE(Teste_Field.isInsideTheirField(insidePoint2));

    EXPECT_FALSE(Teste_Field.isInsideTheirField(outsidePoint1));
    EXPECT_FALSE(Teste_Field.isInsideTheirField(outsidePoint2));
    EXPECT_FALSE(Teste_Field.isInsideTheirField(outsidePoint3));
    EXPECT_FALSE(Teste_Field.isInsideTheirField(outsidePoint4));
}
