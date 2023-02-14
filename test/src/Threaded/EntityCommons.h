#ifndef ENTITYCOMMONS_H
#define ENTITYCOMMONS_H

#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>
#include <gmock/gmock.h>

#include <spdlog/spdlog.h>
#include <fmt/color.h>

#include <Armorial/Threaded/Entity/Entity.h>
#include <Armorial/Threaded/EntityManager/EntityManager.h>

namespace EntityCommons {
    class Entidade : public Threaded::Entity {
    public:
        Entidade();

        virtual ~Entidade();

        void setStatus(QString newStatus) {
            _curStatus = newStatus;
        }

        virtual QString getStatus();

        void setValueCheck(int newValueCheck) {
            _valueCheck = newValueCheck;
        }

        virtual int getValueCheck();

        virtual void toInit();

        virtual void toLoop();

        virtual void toEnd();

        virtual void toRun();

        virtual void increaseIt(int val);

    private:
        virtual void run();

        void initialization();

        void loop();

        void finalization();

        virtual void startTimer();

        virtual long getRemainingTime();

        Utils::Timer _entityTimer;
        QMutex _entityMutex;

        QString _curStatus;
        int _valueCheck;
        int _autoEnd;
    };

    class Teste : public Threaded::Entity {
    public:
        Teste();

    private:
        void initialization() {}

        void loop() {}

        void finalization() {}
    };

    class Teste2 : public Threaded::Entity {
    public:
        Teste2();

    private:
        void initialization() {}

        void loop() {}

        void finalization() {}
    };

    class EntityMock : public Entidade {
    public:
        MOCK_METHOD(void, initialization, (), (override));
        MOCK_METHOD(void, loop, (), (override));
        MOCK_METHOD(void, finalization, (), (override));
        MOCK_METHOD(QString, getStatus, (), (override));
        MOCK_METHOD(int, getValueCheck, (), (override));
    };

    class TesteMock : public EntityMock {

    };

    class Teste2Mock : public EntityMock {

    };

    class ManagerMockable : public Threaded::EntityManager {
    public:
        ManagerMockable() = default;

        void addEntity(EntityMock *entity, int entityPriority = 0);

        void startEntities();

        void disableEntities();

    private:
        QMultiMap<int, EntityMock*> _priorityMap;
    };

    class ManagerMock : public ManagerMockable {
//        MOCK_METHOD(void, addEntity, (EntityMock *entity, int entityPriority), (override));
//        MOCK_METHOD(void, startEntities, (), (override));
//        MOCK_METHOD(void, disableEntities, (), (override));
    };
}

#endif // ENTITYCOMMONS_H
