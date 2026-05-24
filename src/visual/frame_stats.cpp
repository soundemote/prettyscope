#include "visual/frame_stats.hpp"

namespace prettyscope
{
FrameStats::FrameStats(float initialFps)
    : smoothedFps_(initialFps)
{
}

void FrameStats::reset(float fps)
{
    smoothedFps_ = fps;
}

void FrameStats::advance(float dtSeconds)
{
    if (dtSeconds <= 0.0f)
    {
        return;
    }

    const float instantFps = 1.0f / dtSeconds;
    smoothedFps_ = smoothedFps_ * 0.92f + instantFps * 0.08f;
}

float FrameStats::fps() const
{
    return smoothedFps_;
}
}
