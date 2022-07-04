#ifndef ARMORIAL_UTILS_TIMER_H
#define ARMORIAL_UTILS_TIMER_H

#include <chrono>

namespace Utils {
    /*!
     * \brief The Utils::Timer class provides a interface to manage time intervals using its
     * start() and stop() methods.
     */
    class Timer
    {
    public:
        /*!
         * \brief Default constructor for Timer instance.
         */
        Timer() = default;

        /*!
         * \brief Start the interval measurement, setting the Timer::_startPoint variable with the current time.
         */
        void start();

        /*!
         * \brief Stop the interval measurement, setting the Timer::_endPoint variable with the current time.
         */
        void stop();

        /*!
         * \brief Get interval measurement (_endPoint - _startPoint) as seconds.
         * \return A double variable containing the interval measurement as seconds.
         */
        double getSeconds();

        /*!
         * \brief Get interval measurement (_endPoint - _startPoint) as milliseconds.
         * \return A double variable containing the interval measurement as milliseconds.
         */
        double getMilliseconds();

        /*!
         * \brief Get interval measurement (_endPoint - _startPoint) as microseconds.
         * \return A double variable containing the interval measurement as microseconds.
         */
        double getMicroseconds();

        /*!
         * \brief Get interval measurement (_endPoint - _startPoint) as nanoseconds.
         * \return A double variable containing the interval measurement as nanoseconds.
         */
        double getNanoseconds();

    private:
        /*!
         * \brief Stores the chrono start point.
         */
        std::chrono::time_point<std::chrono::system_clock> _startPoint;
        /*!
         * \brief Stores the chrono end point.
         */
        std::chrono::time_point<std::chrono::system_clock> _endPoint;
    };
}

#endif // ARMORIAL_UTILS_TIMER_H
