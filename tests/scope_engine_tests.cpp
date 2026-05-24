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
}

int main()
{
    prettyscope::ScopeEngine scope(1);

    bool passed = true;
    passed = expectEqual("minimum sample count", scope.sampleCount(), 2) && passed;

    scope.setSampleCount(2048);
    passed = expectEqual("expanded sample count", scope.sampleCount(), 2048) && passed;
    passed = expectEqual("signal size follows sample count", scope.signal().size(), 2048) && passed;

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
