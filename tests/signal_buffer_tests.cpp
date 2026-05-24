#include "visual/signal_buffer.hpp"

#include <iostream>

namespace
{
bool expectEqual(const char* name, int actual, int expected)
{
    if (actual == expected)
    {
        return true;
    }

    std::cerr << name << " expected " << expected << " but got " << actual << '\n';
    return false;
}

bool expectEqual(const char* name, float actual, float expected)
{
    if (actual == expected)
    {
        return true;
    }

    std::cerr << name << " expected " << expected << " but got " << actual << '\n';
    return false;
}
}

int main()
{
    prettyscope::SignalBuffer signal(1);

    bool passed = true;
    passed = expectEqual("minimum size", signal.size(), 2) && passed;

    signal[0] = 0.75f;
    signal.right(0) = -0.25f;
    passed = expectEqual("left data pointer", signal.data()[0], 0.75f) && passed;
    passed = expectEqual("right data pointer", signal.rightData()[0], -0.25f) && passed;

    signal.resize(8);
    passed = expectEqual("resized size", signal.size(), 8) && passed;
    passed = expectEqual("resized left clears", signal[0], 0.0f) && passed;
    passed = expectEqual("resized right clears", signal.right(0), 0.0f) && passed;

    signal.resize(-4);
    passed = expectEqual("negative resize minimum", signal.size(), 2) && passed;

    return passed ? 0 : 1;
}
