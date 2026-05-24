#pragma once

namespace prettyscope
{
class FrameStats
{
public:
    explicit FrameStats(float initialFps = 60.0f);

    void reset(float fps = 60.0f);
    void advance(float dtSeconds);
    float fps() const;

private:
    float smoothedFps_ = 60.0f;
};
}
