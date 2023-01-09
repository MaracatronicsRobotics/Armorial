#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>
#include <gmock/gmock.h>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/bundled/color.h>

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

    double startDiff = std::chrono::duration_cast<std::chrono::nanoseconds>(clock - timer.getStartPoint()).count();
    double endDiff = std::chrono::duration_cast<std::chrono::nanoseconds>(clock - timer.getEndPoint()).count();

    EXPECT_NEAR(startDiff/1E18, 0.0, 10.0);
    EXPECT_NEAR(endDiff/1E18, 0.0, 10.0);
}
