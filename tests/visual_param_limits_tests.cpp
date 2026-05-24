#include "visual/visual_param_limits.hpp"

#include <iostream>

namespace
{
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
    prettyscope::VisualParams params;
    params.backgroundColor = {-1.0f, 0.5f, 2.0f};
    params.traceColor = {1.2f, -0.1f, 0.3f};
    params.glowColor = {0.2f, 3.0f, -2.0f};
    params.traceGain = 10.0f;
    params.glowStrength = -1.0f;
    params.traceWidth = 20.0f;
    params.glowWidth = 2.0f;
    params.persistence = 1.0f;
    params.fastDecay = -0.2f;
    params.afterglow = 2.0f;
    params.gridIntensity = 4.0f;

    prettyscope::clampVisualParams(params);

    bool passed = true;
    passed = expectEqual("background red", params.backgroundColor.r, 0.0f) && passed;
    passed = expectEqual("background blue", params.backgroundColor.b, 1.0f) && passed;
    passed = expectEqual("trace green", params.traceColor.g, 0.0f) && passed;
    passed = expectEqual("glow green", params.glowColor.g, 1.0f) && passed;
    passed = expectEqual("trace gain", params.traceGain, prettyscope::kMaxTraceGain) && passed;
    passed = expectEqual("glow strength", params.glowStrength, prettyscope::kMinGlowStrength) && passed;
    passed = expectEqual("trace width", params.traceWidth, prettyscope::kMaxTraceWidth) && passed;
    passed = expectEqual("glow width follows trace width", params.glowWidth, prettyscope::kMaxTraceWidth) && passed;
    passed = expectEqual("persistence", params.persistence, prettyscope::kMaxPersistence) && passed;
    passed = expectEqual("fast decay", params.fastDecay, prettyscope::kMinDecayAmount) && passed;
    passed = expectEqual("afterglow", params.afterglow, prettyscope::kMaxDecayAmount) && passed;
    passed = expectEqual("grid intensity", params.gridIntensity, 1.0f) && passed;

    return passed ? 0 : 1;
}
