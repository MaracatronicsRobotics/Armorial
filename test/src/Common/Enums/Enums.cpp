#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>
#include <gmock/gmock.h>

#include <Armorial/Common/Enums/Enums.h>
#include <Armorial/Libs/magic_enum/include/magic_enum.hpp>


// COLOR
TEST(Common_Enums_Test, Check_Correct_Colors_InOrder){
    auto colors = magic_enum::enum_names<Common::Enums::Color>();

    EXPECT_EQ(colors.size(), 3);
    EXPECT_EQ("BLUE", colors[0]) << "Expecting BLUE";
    EXPECT_EQ("YELLOW", colors[1]) << "Expecting YELLOW";
    EXPECT_EQ("UNDEFINED", colors[2]) << "Expecting UNDEFINED";
}


// SIDE

TEST(Common_Enums_Test, Check_Correct_Side_InOrder){
    auto sides = magic_enum::enum_names<Common::Enums::Side>();

    EXPECT_EQ(sides.size(), 2);
    EXPECT_EQ("SIDE_LEFT", sides[0]) << "Expecting SIDE_LEFT";
    EXPECT_EQ("SIDE_RIGHT", sides[1]) << "Expecting SIDE_RIGHT";
}

// Quadrant

TEST(Common_Enums_Test, Check_Correct_Quadrants_InOrder){
    auto quadrants = magic_enum::enum_names<Common::Enums::Quadrant>();

    EXPECT_EQ(quadrants.size(), 5);
    EXPECT_EQ("QUADRANT_TOP_RIGHT", quadrants[0]) << "Expecting QUADRANT_TOP_RIGHT";
    EXPECT_EQ("QUADRANT_TOP_LEFT", quadrants[1]) << "Expecting QUADRANT_TOP_LEFT";
    EXPECT_EQ("QUADRANT_BOTTOM_LEFT", quadrants[2]) << "Expecting QUADRANT_BOTTOM_LEFT";
    EXPECT_EQ("QUADRANT_BOTTOM_RIGHT", quadrants[3]) << "Expecting QUADRANT_BOTTOM_RIGHT";
    EXPECT_EQ("NO_QUADRANT", quadrants[4]) << "Expecting NO_QUADRANT";
}


