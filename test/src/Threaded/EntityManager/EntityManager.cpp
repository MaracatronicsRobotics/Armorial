#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>
#include <gmock/gmock.h>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/bundled/color.h>

#include <src/Threaded/EntityCommons.h>

#include <Armorial/Threaded/EntityManager/EntityManager.h>

TEST(Threaded_Entity_Manager_Test, When_Adding_New_Entity_Should_Store_With_Correct_Priority) {
//    EntityCommons::EntityMock *entidade1 = (EntityCommons::EntityMock*) new EntityCommons::Entidade();
//    EntityCommons::EntityMock *entidade2 = (EntityCommons::EntityMock*) new EntityCommons::Teste();
//    EntityCommons::EntityMock *entidade3 = (EntityCommons::EntityMock*) new EntityCommons::Fon();

//    EntityCommons::ManagerMockable *manager = new EntityCommons::ManagerMockable();

//    testing::ExpectationSet entity1;
//    entity1 += EXPECT_CALL(*entidade1, initialization()).Times(testing::AtLeast(1));

//    testing::ExpectationSet entity2;
//    entity2 += EXPECT_CALL(*entidade2, initialization()).Times(testing::AtLeast(1)).After(entity1);

//    testing::ExpectationSet entity3;
//    entity3 += EXPECT_CALL(*entidade3, initialization()).Times(testing::AtLeast(1)).After(entity2);

//    manager->addEntity(entidade1, 0);
//    manager->addEntity(entidade2, 1);
//    manager->addEntity(entidade3, 2);

//    manager->startEntities();
//    manager->disableEntities();
}
