#ifndef ARMORIAL_THREADED_ENTITYMANAGER_H
#define ARMORIAL_THREADED_ENTITYMANAGER_H

#include <QMultiMap>

#include <Armorial/Threaded/Entity/Entity.h>

namespace Threaded {
    /*!
     * \brief The Threaded::EntityManager class provides a interface to create and manage Threaded::Entity
     * instances in the project. <br>
     * The key idea for this module is to allow a more robust and clear way to start and finish the entities
     * following a concept of priority, reducing considerably the code overhead. <br>
     */
    class EntityManager
    {
    public:
        /*!
         * \brief Constructs a default instance of EntityManager.
         */
        EntityManager() = default;

        /*!
         * \brief Add a Entity instance to the mapping with a given priority.
         * \param entity
         * \param entityPriority
         * \note The priority is used as follows: <br>
         *       - The EntityManager will start the Entities following the higher to lower priority; <br>
         *       - The most priority Entity will be the one with highest priority value; <br>
         *       - In case that two or more Entity instances have the same priority, the one that was inserted
         * first is considered the one with highest priority. <br>
         *
         */
        void addEntity(Entity *entity, int entityPriority = 0);

        /*!
         * \brief Start all registered Entity instances following the high to lower priority;
         */
        void startEntities();

        /*!
         * \brief Disable all registered Entity instances following the lower to high priority.
         */
        void disableEntities();

        /*!
         * \return Return a list containing all registered entities.
         */
        QList<Entity*> getEntities();

    private:
        /*!
         * \brief The map that will store the entities by given priority.
         */
        QMultiMap<int, Entity*> _priorityMap;
    };
}

#endif // ARMORIAL_THREADED_ENTITYMANAGER_H
