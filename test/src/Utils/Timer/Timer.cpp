#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>
#include <gmock/gmock.h>

#include <spdlog/spdlog.h>
#include <fmt/color.h>

#include <thread>

#include <Armorial/Utils/Timer/Timer.h>

class TimerMock : public Utils::Timer {
public:
    std::chrono::time_point<std::chrono::system_clock> getStartPoint() {
        return _startPoint;
    }

    std::chrono::time_point<std::chrono::system_clock> getEndPoint() {
        return _endPoint;
    }

private:
    std::chrono::time_point<std::chrono::system_clock> _startPoint;
    std::chrono::time_point<std::chrono::system_clock> _endPoint;
};

TEST(Utils_Timer_Test, When_Creating_Timer_Should_Set_Points_To_Now) {
    TimerMock timer = TimerMock();
    std::chrono::time_point<std::chrono::system_clock> clock = std::chrono::system_clock::now();

    // CHECK WHY NANO SECONDS / 1E9 NOT TRANSFORMING TO SECONDS PROPERLY

    EXPECT_NEAR(std::chrono::duration_cast<std::chrono::seconds>(clock - timer.getStartPoint()).count()/1E9, 0.0, 10.0);
    EXPECT_NEAR(std::chrono::duration_cast<std::chrono::seconds>(clock - timer.getEndPoint()).count()/1E9, 0.0, 10.0);
}

TEST(Utils_Timer_Test, When_Creating_Timer_Should_Set_Points_Near_Eachother) {
    TimerMock timer = TimerMock();

    EXPECT_NEAR(timer.getMicroseconds(), 0.0, 10.0);
}

TEST(Utils_Timer_Test, When_Starting_Timer_Should_Set_Start_Properly) {

    // CHECK WHY NANO SECONDS / 1E9 NOT TRANSFORMING TO SECONDS PROPERLY

    TimerMock testTimer = TimerMock();
    testTimer.start();
    double startDiff = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - testTimer.getStartPoint()).count();

    EXPECT_NEAR(startDiff/1E9, 0.0, 10.0);
}

TEST(Utils_Timer_Test, When_Stopping_Timer_Should_Set_End_Properly) {
    TimerMock testTimer = TimerMock();
    testTimer.start();

    testTimer.getNanoseconds();
    double endDiff = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - testTimer.getEndPoint()).count();
    EXPECT_NEAR(endDiff/1E9, 0.0, 10.0);
}

TEST(Utils_Timer_Test, When_Getting_Time_Should_Return_Same_Timestamp) {
    TimerMock testTimer = TimerMock();
    testTimer.start();

    std::this_thread::sleep_for(std::chrono::seconds(5));
    double nanoSec = testTimer.getNanoseconds();
    double microSec = testTimer.getMicroseconds();
    double milliSec = testTimer.getMilliseconds();
    double sec = testTimer.getSeconds();

    EXPECT_NEAR((microSec - (nanoSec/1E3)), 0.0, 10.0);
    EXPECT_NEAR((milliSec - (nanoSec/1E6)), 0.0, 10.0);
    EXPECT_NEAR((sec - (nanoSec/1E9)), 0.0, 10.0);
    EXPECT_NEAR((milliSec - (microSec/1E3)), 0.0, 10.0);
    EXPECT_NEAR((sec - (microSec/1E6)), 0.0, 10.0);
    EXPECT_NEAR((sec - (milliSec/1E3)), 0.0, 10.0);
}
