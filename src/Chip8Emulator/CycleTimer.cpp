#include "CycleTimer.h"

#include <thread>

void CycleTimer::maintainCycleRate() const
{
    const auto endTime = std::chrono::system_clock::now();
    const auto durationMillis = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - this->_startTime).count();
    const auto sleepTime = (1000 / this->_hertz) - durationMillis;

    if (sleepTime > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
    }
}