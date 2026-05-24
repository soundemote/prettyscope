#include "visual/frame_stats.hpp"

#include <iostream>

namespace
{
bool nearlyEqual(float a, float b)
{
    const float diff = a - b;
    return diff > -0.0001f && diff < 0.0001f;
}

bool expectEqual(const char* name, float actual, float expected)
{
    if (nearlyEqual(actual, expected))
    {
        return true;
    }

    std::cerr << name << " expected " << expected << " but got " << actual << '\n';
    return false;
}
}

int main()
{
    prettyscope::FrameStats stats;

    bool passed = true;
    passed = expectEqual("initial fps", stats.fps(), 60.0f) && passed;

    stats.advance(0.0f);
    passed = expectEqual("zero dt ignored", stats.fps(), 60.0f) && passed;

    stats.advance(0.5f);
    passed = expectEqual("smoothed low fps", stats.fps(), 55.36f) && passed;

    stats.reset(120.0f);
    passed = expectEqual("reset fps", stats.fps(), 120.0f) && passed;

    return passed ? 0 : 1;
}
