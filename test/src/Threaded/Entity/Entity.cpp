#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>
#include <gmock/gmock.h>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/bundled/color.h>

#include <Armorial/Threaded/Entity/Entity.h>
#include <src/Threaded/EntityCommons.h>

TEST(Threaded_Entity_Test, When_Creating_Entity_Should_Setup_Values_Correctly) {
    EntityCommons::Entidade entity = EntityCommons::Entidade();
    {
        SCOPED_TRACE(fmt::format(fmt::emphasis::bold, QString("\n[Entity] Threaded::Entites::Entity() herd class => stored %1 instead of 'Created'.").arg(entity.getStatus()).toStdString()));
        EXPECT_EQ(entity.getStatus(), QString("Created"));
    }
    {
        SCOPED_TRACE(fmt::format(fmt::emphasis::bold, QString("\n[Entity] Threaded::Entites::Entity() herd class => stored %1 instead of 1.").arg(entity.getValueCheck()).toStdString()));
        EXPECT_EQ(entity.getValueCheck(), 1);
    }
    {
        SCOPED_TRACE(fmt::format(fmt::emphasis::bold, QString("\n[Entity] Threaded::Entites::Entity() herd class => stored %1 instead of 60.").arg(entity.loopFrequency()).toStdString()));
        EXPECT_EQ(entity.loopFrequency(), 60);
    }
    {
        SCOPED_TRACE(fmt::format(fmt::emphasis::bold, QString("\n[Entity] Threaded::Entites::Entity() herd class => stored %1 instead of true.").arg(entity.isEnabled()).toStdString()));
        EXPECT_TRUE(entity.isEnabled());
    }
    {
        SCOPED_TRACE(fmt::format(fmt::emphasis::bold, QString("\n[Entity] Threaded::Entites::Entity() herd class => stored %1 instead of false.").arg(entity.isStopped()).toStdString()));
        EXPECT_FALSE(entity.isStopped());
    }
}

TEST(Threaded_Entity_Test, When_Consulting_Name_Should_Return_Proper_Entity_Name) {
    EntityCommons::Entidade *entity = new EntityCommons::Entidade();
    EntityCommons::Teste *teste = new EntityCommons::Teste();
    EntityCommons::Fon *teste2 = new EntityCommons::Fon();
    {
        SCOPED_TRACE(fmt::format(fmt::emphasis::bold, QString("\n[Entity] Threaded::Entites::entityName() herd class => stored %1 instead of 'EntityCommons::Entidade'.").arg(entity->entityName()).toStdString()));
        EXPECT_EQ(entity->entityName(), QString("EntityCommons::Entidade"));
    }
    {
        SCOPED_TRACE(fmt::format(fmt::emphasis::bold, QString("\n[Entity] Threaded::Entites::entityName() herd class => stored %1 instead of 'EntityCommons::Teste'.").arg(teste->entityName()).toStdString()));
        EXPECT_EQ(teste->entityName(), QString("EntityCommons::Teste"));
    }
    {
        SCOPED_TRACE(fmt::format(fmt::emphasis::bold, QString("\n[Entity] Threaded::Entites::entityName() herd class => stored %1 instead of 'EntityCommons::Fon'.").arg(teste2->entityName()).toStdString()));
        EXPECT_EQ(teste2->entityName(), QString("EntityCommons::Fon"));
    }
}

TEST(Threaded_Entity_Test, When_Setting_Loop_Frequency_Should_Store_Wanted_Value) {
    EntityCommons::Entidade entity = EntityCommons::Entidade();
    entity.setLoopFrequency(30);
    SCOPED_TRACE(fmt::format(fmt::emphasis::bold, QString("\n[Entity] Threaded::Entites::setLoopFrequency() herd class => stored %1 instead of 30.").arg(entity.loopFrequency()).toStdString()));
    EXPECT_EQ(entity.loopFrequency(), 30);
}

TEST(Threaded_Entity_Test, When_Enabling_Entity_Should_Be_Enabled_And_Not_Stopped) {
    EntityCommons::Entidade entity = EntityCommons::Entidade();
    entity.enableEntity();
    if (!entity.isEnabled() && entity.isStopped()) {
        SCOPED_TRACE(fmt::format(fmt::emphasis::bold, QString("\n[Entity] Threaded::Entites::enableEntity() herd class => stored isEnable %1 instead of true and isStopped %2 instead of false.").arg(entity.isEnabled()).arg(entity.isStopped()).toStdString()));
        EXPECT_TRUE(entity.isEnabled() && (!entity.isStopped()));
    } else if (entity.isStopped()) {
        SCOPED_TRACE(fmt::format(fmt::emphasis::bold, QString("\n[Entity] Threaded::Entites::enableEntity() herd class => stored isStopped %1 instead of false.").arg(entity.isStopped()).toStdString()));
        EXPECT_TRUE(entity.isEnabled() && (!entity.isStopped()));
    } else if (!entity.isEnabled()){
        SCOPED_TRACE(fmt::format(fmt::emphasis::bold, QString("\n[Entity] Threaded::Entites::enableEntity() herd class => stored isEnable %1 instead of true.").arg(entity.isEnabled()).toStdString()));
        EXPECT_TRUE(entity.isEnabled() && (!entity.isStopped()));
    }
    EXPECT_TRUE(entity.isEnabled() && (!entity.isStopped()));
}

TEST(Threaded_Entity_Test, When_Disabling_Entity_Should_Not_Be_Enabled) {
    EntityCommons::Entidade entity = EntityCommons::Entidade();
    entity.disableEntity();
    SCOPED_TRACE(fmt::format(fmt::emphasis::bold, QString("\n[Entity] Threaded::Entites::disableEntity() herd class => stored isEnable %1 instead of false.").arg(entity.isEnabled()).toStdString()));
    EXPECT_FALSE(entity.isEnabled());
}

TEST(Threaded_Entity_Test, When_Stopping_Entity_Should_Be_Stopped) {
    EntityCommons::Entidade entity = EntityCommons::Entidade();
    entity.stopEntity();
    SCOPED_TRACE(fmt::format(fmt::emphasis::bold, QString("\n[Entity] Threaded::Entites::disableEntity() herd class => stored isStopped %1 instead of true.").arg(entity.isStopped()).toStdString()));
    EXPECT_TRUE(entity.isStopped());
}

TEST(Threaded_Entity_Test, When_Consulting_Entity_Loop_Frequency_Should_Receive_Current_Frequency) {
    EntityCommons::Entidade entity = EntityCommons::Entidade();
    quint16 freq = 60;
    SCOPED_TRACE(fmt::format(fmt::emphasis::bold, QString("\n[Entity] Threaded::Entites::loopFrequency() herd class => did not returned current value (%1 instead of %2).").arg(entity.loopFrequency()).arg(freq).toStdString()));
    EXPECT_EQ(entity.loopFrequency(), freq);
    freq = 30;
    entity.setLoopFrequency(freq);
    EXPECT_EQ(entity.loopFrequency(), freq);
}

TEST(Threaded_Entity_Test, When_Consulting_Entity_IsEnabled_Should_Receive_Current_IsEnable_Status) {
    EntityCommons::Entidade entity = EntityCommons::Entidade();
    bool enabled = true;
    SCOPED_TRACE(fmt::format(fmt::emphasis::bold, QString("\n[Entity] Threaded::Entites::isEnabled() herd class => did not returned current value (%1 instead of %2).").arg(entity.isEnabled()).arg(enabled).toStdString()));
    EXPECT_EQ(entity.isEnabled(), enabled);
    enabled = false;
    entity.disableEntity();
    EXPECT_EQ(entity.isEnabled(), enabled);
    enabled = true;
    entity.enableEntity();
    EXPECT_EQ(entity.isEnabled(), enabled);
}

TEST(Threaded_Entity_Test, When_Consulting_Entity_IsStopped_Should_Receive_Current_IsStopped_Status) {
    EntityCommons::Entidade entity = EntityCommons::Entidade();
    bool stopped = false;
    SCOPED_TRACE(fmt::format(fmt::emphasis::bold, QString("\n[Entity] Threaded::Entites::isStopped() herd class => did not returned current value (%1 instead of %2).").arg(entity.isStopped()).arg(stopped).toStdString()));
    EXPECT_EQ(entity.isStopped(), stopped);
    stopped = true;
    entity.stopEntity();
    EXPECT_EQ(entity.isStopped(), stopped);
    stopped = false;
    entity.enableEntity();
    EXPECT_EQ(entity.isStopped(), stopped);
}

TEST(Threaded_Entity_Test, When_Initialize_Entity_Should_Initialize_Values_Correctly) {
    EntityCommons::Entidade entity = EntityCommons::Entidade();
    entity.toInit();
    {
        SCOPED_TRACE(fmt::format(fmt::emphasis::bold, QString("\n[Entity] Threaded::Entites::initialization() herd class => stored %1 instead of 'Initialized'.").arg(entity.getStatus()).toStdString()));
        EXPECT_EQ(entity.getStatus(), QString("Initialized"));
    }
    {
        SCOPED_TRACE(fmt::format(fmt::emphasis::bold, QString("\n[Entity] Threaded::Entites::initialization() herd class => stored %1 instead of 2.").arg(entity.getValueCheck()).toStdString()));
        EXPECT_EQ(entity.getValueCheck(), 2);
    }
}

TEST(Threaded_Entity_Test, When_Entity_In_Loop_Should_Update_Values_Correctly) {
    EntityCommons::Entidade entity = EntityCommons::Entidade();
    entity.toLoop();
    {
        SCOPED_TRACE(fmt::format(fmt::emphasis::bold, QString("\n[Entity] Threaded::Entites::loop() herd class => stored %1 instead of 'In Loop'.").arg(entity.getStatus()).toStdString()));
        EXPECT_EQ(entity.getStatus(), QString("In Loop"));
    }
    {
        SCOPED_TRACE(fmt::format(fmt::emphasis::bold, QString("\n[Entity] Threaded::Entites::loop() herd class => stored %1 instead of 3.").arg(entity.getValueCheck()).toStdString()));
        EXPECT_EQ(entity.getValueCheck(), 3);
    }
}

TEST(Threaded_Entity_Test, When_Finalize_Entity_Should_Set_End_Values_Correctly) {
    EntityCommons::Entidade entity = EntityCommons::Entidade();
    entity.toEnd();
    {
        SCOPED_TRACE(fmt::format(fmt::emphasis::bold, QString("\n[Entity] Threaded::Entites::finalization() herd class => stored %1 instead of 'Finalized'.").arg(entity.getStatus()).toStdString()));
        EXPECT_EQ(entity.getStatus(), QString("Finalized"));
    }
    {
        SCOPED_TRACE(fmt::format(fmt::emphasis::bold, QString("\n[Entity] Threaded::Entites::finalization() herd class => stored %1 instead of 4.").arg(entity.getValueCheck()).toStdString()));
        EXPECT_EQ(entity.getValueCheck(), 4);
    }
}

TEST(Threaded_Entity_Test, When_Running_Entity_Should_Run_And_Finish_Properly) {
    EntityCommons::EntityMock entity;
    EXPECT_CALL(entity, initialization()).Times(testing::AtLeast(1));
    EXPECT_CALL(entity, loop()).Times(testing::AtLeast(1));
    EXPECT_CALL(entity, finalization()).Times(testing::AtLeast(1));

    entity.toRun();
}
