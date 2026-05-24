#include "visual/visual_parameters.hpp"

#include <iostream>

namespace
{
bool expectTrue(const char* name, bool value)
{
    if (value)
    {
        return true;
    }

    std::cerr << name << " expected true\n";
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
    size_t count = 0;
    const prettyscope::VisualFloatParameter* parameters = prettyscope::visualFloatParameters(count);

    bool passed = true;
    passed = expectTrue("parameters exist", parameters != nullptr) && passed;
    passed = expectTrue("parameter count", count == 8) && passed;

    const prettyscope::VisualFloatParameter* traceGain =
        prettyscope::findVisualFloatParameter(prettyscope::VisualFloatParameterId::TraceGain);
    passed = expectTrue("find trace gain", traceGain != nullptr) && passed;
    if (traceGain != nullptr)
    {
        passed = expectEqual("trace gain default", traceGain->defaultValue, 0.10f) && passed;
    }

    prettyscope::VisualParams params;
    passed = expectTrue(
        "set trace gain",
        prettyscope::setVisualFloatParameter(params, prettyscope::VisualFloatParameterId::TraceGain, 99.0f)) && passed;
    passed = expectEqual(
        "trace gain clamps",
        prettyscope::getVisualFloatParameter(params, prettyscope::VisualFloatParameterId::TraceGain),
        4.0f) && passed;

    passed = expectTrue(
        "set trace width",
        prettyscope::setVisualFloatParameter(params, prettyscope::VisualFloatParameterId::TraceWidth, 12.0f)) && passed;
    passed = expectTrue(
        "set glow width",
        prettyscope::setVisualFloatParameter(params, prettyscope::VisualFloatParameterId::GlowWidth, 1.0f)) && passed;
    passed = expectEqual(
        "glow width follows trace width",
        prettyscope::getVisualFloatParameter(params, prettyscope::VisualFloatParameterId::GlowWidth),
        12.0f) && passed;

    return passed ? 0 : 1;
}
