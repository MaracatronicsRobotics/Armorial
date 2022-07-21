#ifndef ARMORIAL_UTILS_EXITHANDLER_H
#define ARMORIAL_UTILS_EXITHANDLER_H

#include <QObject>
#include <QCoreApplication>

namespace Utils {
    /*!
     * \brief The Utils::ExitHandler class provides a interface to threat the
     * interrupt signals from the qt application
     */
    class ExitHandler : public QObject
    {
    public:
        /*!
         * \brief Set the application which the ExitHandler will listen to.
         * \param app The application pointer.
         */
        static void setApplication(QCoreApplication *app);

        /*!
         * \brief Setup the application which the ExitHandler will listen to.
         */
        static void setup();

        /*!
         * \brief Run the ExitHandler (to handle the sigint calls from the application).
         */
        static void run(int s);

    private:
        static QCoreApplication *_app;
        static int _counter;
    };

}

#endif // ARMORIAL_UTILS_EXITHANDLER_H
