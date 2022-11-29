#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Armorial/Geometry/Vector2D/Vector2D.h>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/bundled/color.h>

//class Vector2DTest : public ::testing::Test {
//protected:
//    // Test class constructor to setup each test
//    Vector2DTest() {
//    }

//    // Called right after constructor and before each test
//    void SetUp() override {
//    }

//    // In case you need a not default destructor, define an override destructor right above,
//    // followed by a 'TearDown' override function (if you need) which is called right after each test and before constructor
//};

TEST(Teste_Geometry_Vector2D, QuandoFuncaoDistChamada_NuncaDeveriaRetornarValorNegativo) {

    Geometry::Vector2D vectorBase(1.0, 1.0);
    for (int i = 0; i < 1; i++) {
        SCOPED_TRACE(fmt::format(fmt::emphasis::bold, "\n[Vector2DTest] Vector2D::dist(const Vector2D &other) const ===> Dist Function not Negative (Case 0)"));
        Geometry::Vector2D v0(i, i);
        EXPECT_GE(vectorBase.dist(v0), 0.0);
    }

    // Still needs a better way to separate scopes of the same test

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            SCOPED_TRACE(fmt::format(fmt::emphasis::bold, "\n[Vector2DTest] Vector2D::dist(const Vector2D &other) const ===> Dist Function not Negative (Case 1)"));
            Geometry::Vector2D vpp(i, j);
            EXPECT_GE(vectorBase.dist(vpp), 0.0);
        }
        for (int j = 0; j > -5; j--) {
            SCOPED_TRACE(fmt::format(fmt::emphasis::bold, "\n[Vector2DTest] Vector2D::dist(const Vector2D &other) const ===> Dist Function not Negative (Case 2)"));
            Geometry::Vector2D vpn(i, j);
            EXPECT_GE(vectorBase.dist(vpn), 0.0);
        }
    }
    for (int i = 0; i > -5; i--) {
        for (int j = 0; j > 5; j++){
            SCOPED_TRACE(fmt::format(fmt::emphasis::bold, "\n[Vector2DTest] Vector2D::dist(const Vector2D &other) const ===> Dist Function not Negative (Case 3)"));
            Geometry::Vector2D vnp(i, j);
            EXPECT_GE(vectorBase.dist(vnp), 0.0);
        }
        for (int j = 0; j > -5; j--){
            SCOPED_TRACE(fmt::format(fmt::emphasis::bold, "\n[Vector2DTest] Vector2D::dist(const Vector2D &other) const ===> Dist Function not Negative (Case 4)"));
            Geometry::Vector2D vnn(i, j);
            EXPECT_GE(vectorBase.dist(vnn), 0.0);
        }
    }
    Geometry::Vector2D vop(-1.0, -1.0);
    Geometry::Vector2D vox(-1.0, 1.0);
    Geometry::Vector2D voy(1.0, -1.0);

    EXPECT_GE(vectorBase.dist(vop), 0.0);
    EXPECT_GE(vectorBase.dist(vox), 0.0);
    EXPECT_GE(vectorBase.dist(voy), 0.0);
}
