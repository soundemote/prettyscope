#include "visual/visual_parameters.hpp"

#include <iostream>
#include <string>

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

bool expectEqual(const char* name, const std::string& actual, const char* expected)
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

    passed = expectEqual(
        "normalize minimum",
        prettyscope::normalizeVisualFloatParameter(*traceGain, traceGain->minimum),
        0.0f) && passed;
    passed = expectEqual(
        "normalize maximum",
        prettyscope::normalizeVisualFloatParameter(*traceGain, traceGain->maximum),
        1.0f) && passed;
    passed = expectEqual(
        "denormalize maximum",
        prettyscope::denormalizeVisualFloatParameter(*traceGain, 2.0f),
        traceGain->maximum) && passed;

    passed = expectTrue(
        "set normalized trace gain",
        prettyscope::setNormalizedVisualFloatParameter(params, prettyscope::VisualFloatParameterId::TraceGain, 0.0f)) && passed;
    passed = expectEqual(
        "normalized trace gain value",
        prettyscope::getVisualFloatParameter(params, prettyscope::VisualFloatParameterId::TraceGain),
        traceGain->minimum) && passed;
    passed = expectEqual(
        "get normalized trace gain",
        prettyscope::getNormalizedVisualFloatParameter(params, prettyscope::VisualFloatParameterId::TraceGain),
        0.0f) && passed;
    passed = expectEqual(
        "format trace gain",
        prettyscope::formatVisualFloatParameterValue(prettyscope::VisualFloatParameterId::TraceGain, 0.1f),
        "0.10") && passed;
    passed = expectEqual(
        "format trace width",
        prettyscope::formatVisualFloatParameterValue(prettyscope::VisualFloatParameterId::TraceWidth, 2.0f),
        "2.0") && passed;
    passed = expectEqual(
        "format persistence",
        prettyscope::formatVisualFloatParameterValue(prettyscope::VisualFloatParameterId::Persistence, 0.98f),
        "0.980") && passed;

    return passed ? 0 : 1;
}
