#include "visual/external_signal_source.hpp"

#include <cmath>
#include <iostream>

namespace
{
bool nearlyEqual(float a, float b)
{
    return std::fabs(a - b) < 0.0001f;
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
    bool passed = true;

    prettyscope::ExternalSignalSource source;
    prettyscope::SignalBuffer signal(4);

    source.setMonoInput(nullptr, 8);
    source.advance(signal, 0.0f);
    passed = expectEqual("null mono left", signal[0], 0.0f) && passed;
    passed = expectEqual("null mono right", signal.right(0), 0.0f) && passed;

    const float mono[] = {0.1f, 0.2f, 0.3f, 0.4f};
    source.setMonoInput(mono, 4);
    source.advance(signal, 0.0f);
    passed = expectEqual("mono left", signal[2], 0.3f) && passed;
    passed = expectEqual("mono right mirrors left", signal.right(2), 0.3f) && passed;

    const float left[] = {-0.5f, -0.25f, 0.25f, 0.5f};
    const float right[] = {0.5f, 0.25f, -0.25f, -0.5f};
    source.setStereoInput(left, right, 4);
    source.advance(signal, 0.0f);
    passed = expectEqual("stereo left", signal[3], 0.5f) && passed;
    passed = expectEqual("stereo right", signal.right(3), -0.5f) && passed;

    source.setStereoInput(left, nullptr, 4);
    source.advance(signal, 0.0f);
    passed = expectEqual("missing right mirrors left", signal.right(1), -0.25f) && passed;

    source.setStereoInput(nullptr, right, 4);
    source.advance(signal, 0.0f);
    passed = expectEqual("missing left mirrors right", signal[1], 0.25f) && passed;

    return passed ? 0 : 1;
}
