#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>
#include <gmock/gmock.h>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/bundled/color.h>

#include <thread>

#include <src/Threaded/EntityCommons.h>

#include <Armorial/Threaded/EntityManager/EntityManager.h>

TEST(Threaded_Entity_Manager_Test, When_Adding_New_Entity_Should_Store_With_Correct_Priority) {
    testing::NiceMock<EntityCommons::TesteMock> *entidade1 = new testing::NiceMock<EntityCommons::TesteMock>();
    testing::NiceMock<EntityCommons::Teste2Mock> *entidade2 = new testing::NiceMock<EntityCommons::Teste2Mock>();

    EntityCommons::ManagerMockable *manager = new EntityCommons::ManagerMockable();

    testing::ExpectationSet exptSet;
    exptSet += EXPECT_CALL(*entidade1, initialization()).Times(testing::AtLeast(1));

    // Never used, but needed to be created as an object to work properly
    testing::Expectation expectation = EXPECT_CALL(*entidade2, initialization()).Times(testing::AtLeast(1)).After(exptSet);
//    EXPECT_CALL(*entidade2, initialization()).Times(testing::AtLeast(1)).After(exptSet);

    manager->addEntity(entidade1, 0);
    manager->addEntity(entidade2, 1);

    manager->startEntities();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    manager->disableEntities();
}

TEST(Threaded_Entity_Manager_Test, When_Starting_Entities_All_Initialization_Should_Be_Called) {
    testing::NiceMock<EntityCommons::TesteMock> *entidadeLoop1 = new testing::NiceMock<EntityCommons::TesteMock>();
    testing::NiceMock<EntityCommons::Teste2Mock> *entidadeLoop2 = new testing::NiceMock<EntityCommons::Teste2Mock>();

    EntityCommons::ManagerMockable *manager = new EntityCommons::ManagerMockable();

    EXPECT_CALL(*entidadeLoop1, initialization()).Times(testing::AtLeast(1));

    EXPECT_CALL(*entidadeLoop2, initialization()).Times(testing::AtLeast(1));

    manager->addEntity(entidadeLoop1, 0);
    manager->addEntity(entidadeLoop2, 0);

    manager->startEntities();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    manager->disableEntities();
}

TEST(Threaded_Entity_Manager_Test, After_Start_Entities_All_Loops_Should_Be_Called) {
    testing::NiceMock<EntityCommons::TesteMock> *entidadeLoop1 = new testing::NiceMock<EntityCommons::TesteMock>();
    testing::NiceMock<EntityCommons::Teste2Mock> *entidadeLoop2 = new testing::NiceMock<EntityCommons::Teste2Mock>();

    EntityCommons::ManagerMockable *manager = new EntityCommons::ManagerMockable();

    EXPECT_CALL(*entidadeLoop1, loop()).Times(testing::AtLeast(1));

    EXPECT_CALL(*entidadeLoop2, loop()).Times(testing::AtLeast(1));

    manager->addEntity(entidadeLoop1, 0);
    manager->addEntity(entidadeLoop2, 0);

    manager->startEntities();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    manager->disableEntities();
}

TEST(Threaded_Entity_Manager_Test, After_Run_When_Disabling_Entities_All_Finalizations_Should_Be_Called) {
    testing::NiceMock<EntityCommons::TesteMock> *entidade1 = new testing::NiceMock<EntityCommons::TesteMock>();
    testing::NiceMock<EntityCommons::Teste2Mock> *entidade2 = new testing::NiceMock<EntityCommons::Teste2Mock>();

    EntityCommons::ManagerMockable manager = EntityCommons::ManagerMockable();

    EXPECT_CALL(*entidade1, finalization()).Times(testing::AtLeast(1));

    EXPECT_CALL(*entidade2, finalization()).Times(testing::AtLeast(1));

    manager.addEntity(entidade1, 0);
    manager.addEntity(entidade2, 0);

    manager.startEntities();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    manager.disableEntities();
}

TEST(Threaded_Entity_Manager_Test, When_Running_Entities_It_Should_Respect_Its_Flow) {
    testing::NiceMock<EntityCommons::TesteMock> *entidade1 = new testing::NiceMock<EntityCommons::TesteMock>();
    testing::NiceMock<EntityCommons::Teste2Mock> *entidade2 = new testing::NiceMock<EntityCommons::Teste2Mock>();

    EntityCommons::ManagerMockable manager = EntityCommons::ManagerMockable();

    testing::ExpectationSet exptSet1;
    testing::ExpectationSet exptSet2;
    exptSet1 += EXPECT_CALL(*entidade1, initialization()).Times(testing::AtLeast(1));

    exptSet2 += EXPECT_CALL(*entidade2, initialization()).Times(testing::AtLeast(1));

    exptSet1 += EXPECT_CALL(*entidade1, loop()).Times(testing::AtLeast(1)).After(exptSet1);

    exptSet2 += EXPECT_CALL(*entidade2, loop()).Times(testing::AtLeast(1)).After(exptSet2);

    testing::Expectation expectation1 = EXPECT_CALL(*entidade1, finalization()).Times(testing::AtLeast(1)).After(exptSet1);

    testing::Expectation expectation2 = EXPECT_CALL(*entidade2, finalization()).Times(testing::AtLeast(1)).After(exptSet2);

    manager.addEntity(entidade1, 0);
    manager.addEntity(entidade2, 0);

    manager.startEntities();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    manager.disableEntities();
}
