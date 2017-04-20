#ifndef TIMER_HPP
#define TIMER_HPP

#include <string>
#include <memory>
#include <chrono>

namespace enhuiz
{
namespace engine
{
struct Timer
{
  public:
    using time = std::chrono::high_resolution_clock;

    Timer()
    {
        mDeltaTime = 0;
        mStartTime = time::now();
    }

    void tick()
    {
        mDeltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(time::now() - mLastTime).count();
        mLastTime = time::now();
    }

    float getDeltaTime()
    {
        return mDeltaTime;
    }

    time::time_point mStartTime;
    time::time_point mLastTime;
    float mDeltaTime;
};
}
}

#endif