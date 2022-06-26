#ifndef ARMORIAL_THREADED_ENTITY_H
#define ARMORIAL_THREADED_ENTITY_H

#include <QObject>
#include <QThread>
#include <QMutex>

#include <Armorial/Utils/Timer/Timer.h>

namespace Threaded {
    /*!
     * \brief The Threaded::Entity class provides a interface for threaded modules.
     */
    class Entity : public QThread
    {
    public:
        /*!
         * \brief Constructs a Entity instance.
         * \note By default, it sets the loop frequency to 60Hz.
         */
        Entity();

        /*!
         * \return Returns the Entity::name() implemented by children of this class.
         */
        virtual QString name() = 0;

        /*!
         * \brief Defines the loop frequency which the Entity instance will run.
         * \param hz The given loop frequency.
         */
        void setLoopFrequency(const quint16 hz);

        /*!
         * \brief Enables the Entity, calling Entity::initialization() and after starting calls to Entity::loop()
         * in the defined frequency.
         */
        void enableEntity();

        /*!
         * \brief Disable the Entity, finishing the calls for Entity::loop() and calling Entity::finalization()
         * implementation.
         * \note This method *finish* the Entity, it is, it finishes the QThread::run() and it implies that this
         * Entity object can not be used anymore for anything. <br>
         * If you want to just stop the Entity (by a moment), you need to call the Entity::stopEntity() method.
         */
        void disableEntity();

        /*!
         * \brief Stop the Entity, freezing the calls for Entity::loop().
         * \note This method *does not finish* the Entity, it is, it does not finishes the QThread::run() calls. <br>
         * If you want to *finish* the Entity (forever), you need to call the Entity::disableEntity() method.
         */
        void stopEntity();

        /*!
         * \brief Get the loop frequency which this Entity instance is running.
         * \return The loop frequency.
         */
        [[nodiscard]] quint16 loopFrequency();

        /*!
         * \brief Check if the Entity instance is enabled.
         * \return True if the Entity is enabled and False otherwise.
         * \note This method will return True only if it is running, i.e. if it is stopped or disabled, it will
         * return False.
         */
        [[nodiscard]] bool isEnabled();

        /*!
         * \brief Check if the Entity instance is stopped.
         * \return True if the Entity is stopped and False otherwise.
         */
        [[nodiscard]] bool isStopped();

    private:
        /*!
         * \brief Reimplementation of QThread::run() which contains the structure to call the virtual methods.
         */
        void run();

        /*!
         * \brief Defines the several initialization steps which need to run in the thread.
         * \note If you have some objects that are thread-related (such as QTimer) you need to initialize
         * them inside this method, as it is called inside the QThread instance (instead of the main thread of
         * the code).
         */
        virtual void initialization() = 0;

        /*!
         * \brief Provides the instructions that will run in loop and called in *hz* times per second.
         * \note As this method is called multiple times, you don't need to implement it using a while, just consider
         * that this calls are already included in a loop-based scope.
         */
        virtual void loop() = 0;

        /*!
         * \brief Defines the several finalization steps which need to run in the thread.
         * \note If you have some objects that are thread-related (such as QTimer) you need to destroy
         * them inside this method, as it is called inside the QThread instance (instead of the main thread of
         * the code). <br>
         * Also, if you have initialized some of these objects in the Entity::initialization() method, they need to be
         * destroyed in the Entity::finalization() method.
         */
        virtual void finalization() = 0;

        /*!
         * \brief Stores the loop frequency of this Entity instance.
         */
        quint16 _loopFrequency;

        /*!
         * \brief Stores the Entity enabled status.
         */
        bool _isEnabled;

        /*!
         * \brief Stores the Entity stopped status.
         */
        bool _isStopped;

        /*!
         * \brief Timer which will be used to execute the loop() method in the desired frequency.
         */
        Utils::Timer _entityTimer;

        /*!
         * \brief Auxiliary method to start the timer.
         */
        void startTimer();

        /*!
         * \brief Auxiliary method to stop the timer.
         */
        void stopTimer();

        /*!
         * \brief Auxiliary method to get the remaining time to the desired frequency.
         * \return The remaining time to the desired frequency.
         * \note As the Entity::loop() call can run in more time than the desired, this
         * method sometimes may return a negative number and this displays a warning in
         * the Entity::run() call.
         */
        long getRemainingTime();

        /*!
         * \brief Mutex to be used in the calls that changes entity members.
         */
        QMutex _entityMutex;
    };
}

#endif // ARMORIAL_THREADED_ENTITY_H
