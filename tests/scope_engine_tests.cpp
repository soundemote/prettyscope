#include "visual/scope_engine.hpp"

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

bool expectTrue(const char* name, bool value)
{
    if (value)
    {
        return true;
    }

    std::cerr << name << " expected true\n";
    return false;
}
}

int main()
{
    prettyscope::ScopeEngine scope(1);

    bool passed = true;
    passed = expectEqual("minimum sample count", scope.sampleCount(), 2) && passed;
    passed = expectTrue("starts uninitialized", !scope.initialized()) && passed;

    scope.setSampleCount(2048);
    passed = expectEqual("expanded sample count", scope.sampleCount(), 2048) && passed;
    passed = expectEqual("signal size follows sample count", scope.signal().size(), 2048) && passed;

    prettyscope::SignalBuffer signal(4);
    signal[0] = -0.5f;
    signal.right(0) = 0.5f;
    signal[3] = 0.25f;
    signal.right(3) = -0.25f;
    scope.setSignal(signal);
    passed = expectEqual("set signal resizes", scope.sampleCount(), 4) && passed;
    passed = expectEqual("set signal left", static_cast<int>(scope.signal()[0] * 100.0f), -50) && passed;
    passed = expectEqual("set signal right", static_cast<int>(scope.signal().right(3) * 100.0f), -25) && passed;

    scope.setSampleCount(-8);
    passed = expectEqual("negative sample count clamps", scope.sampleCount(), 2) && passed;

    prettyscope::VisualParams params;
    params.traceGain = 99.0f;
    params.clearRevision = 42;
    scope.setParams(params);
    passed = expectEqual("set params clamps gain", static_cast<int>(scope.params().traceGain), 4) && passed;
    passed = expectEqual("set params preserves clear revision", scope.params().clearRevision, 0) && passed;

    scope.requestClear();
    passed = expectEqual("request clear increments revision", scope.params().clearRevision, 1) && passed;

    return passed ? 0 : 1;
}
