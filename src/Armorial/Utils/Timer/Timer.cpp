#include <Armorial/Utils/Timer/Timer.h>

namespace Utils {

void Timer::start() {
    _startPoint = std::chrono::system_clock::now();
}

void Timer::stop() {
    _endPoint = std::chrono::system_clock::now();
}

double Timer::getSeconds() {
    return (getNanoseconds()/1E9);
}

double Timer::getMilliseconds() {
    return (getNanoseconds()/1E6);
}

double Timer::getMicroseconds() {
    return (getNanoseconds()/1E3);
}

double Timer::getNanoseconds() {
    stop();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(_endPoint - _startPoint).count();
}

}
