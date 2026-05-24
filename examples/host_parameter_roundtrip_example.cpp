#include "prettyscope.hpp"

#include <cmath>
#include <iostream>
#include <string>

namespace
{
bool nearlyEqual(float left, float right)
{
    return std::fabs(left - right) <= 0.0001f;
}

bool expectTrue(const char* name, bool value)
{
    if (value)
    {
        return true;
    }

    std::cerr << name << " failed\n";
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

bool expectNear(const char* name, float actual, float expected)
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
    prettyscope::VisualParams params;
    bool passed = true;

    const prettyscope::VisualFloatParameter* gain =
        prettyscope::findVisualFloatParameterByStableId("signal.gain");
    passed = expectTrue("find gain descriptor", gain != nullptr) && passed;
    if (gain != nullptr)
    {
        passed = expectEqual("gain stable id", gain->stableId, "signal.gain") && passed;
        passed = expectTrue(
            "gain numeric lookup",
            prettyscope::findVisualFloatParameterByNumericId(gain->numericId) == gain) && passed;

        const float hostValue = 0.25f;
        passed = expectTrue(
            "host writes normalized gain",
            prettyscope::setNormalizedVisualFloatParameter(params, gain->id, hostValue)) && passed;
        const float rawGain = prettyscope::getVisualFloatParameter(params, gain->id);
        passed = expectNear("gain raw roundtrip", rawGain, prettyscope::denormalizeVisualFloatParameter(*gain, hostValue)) && passed;
        passed = expectNear(
            "gain normalized roundtrip",
            prettyscope::getNormalizedVisualFloatParameter(params, gain->id),
            hostValue) && passed;
    }

    const prettyscope::VisualBoolParameter* grid =
        prettyscope::findVisualBoolParameterByStableId("overlay.grid_enabled");
    passed = expectTrue("find grid descriptor", grid != nullptr) && passed;
    if (grid != nullptr)
    {
        passed = expectEqual("grid stable id", grid->stableId, "overlay.grid_enabled") && passed;
        passed = expectTrue(
            "grid numeric lookup",
            prettyscope::findVisualBoolParameterByNumericId(grid->numericId) == grid) && passed;

        passed = expectTrue(
            "host writes normalized grid",
            prettyscope::setNormalizedVisualBoolParameter(params, grid->id, 0.75f)) && passed;
        passed = expectTrue("grid raw roundtrip", prettyscope::getVisualBoolParameter(params, grid->id)) && passed;
        passed = expectNear(
            "grid normalized roundtrip",
            prettyscope::getNormalizedVisualBoolParameter(params, grid->id),
            1.0f) && passed;
    }

    const prettyscope::VisualChoiceParameter* traceMode =
        prettyscope::findVisualChoiceParameterByStableId("scope.trace_mode");
    passed = expectTrue("find trace mode descriptor", traceMode != nullptr) && passed;
    if (traceMode != nullptr)
    {
        passed = expectEqual("trace mode stable id", traceMode->stableId, "scope.trace_mode") && passed;
        passed = expectTrue(
            "trace mode numeric lookup",
            prettyscope::findVisualChoiceParameterByNumericId(traceMode->numericId) == traceMode) && passed;

        const int clearRevision = params.clearRevision;
        passed = expectTrue(
            "host writes normalized trace mode",
            prettyscope::setNormalizedVisualChoiceParameter(params, traceMode->id, 0.0f)) && passed;
        passed = expectTrue(
            "trace mode raw roundtrip",
            prettyscope::getVisualChoiceParameter(params, traceMode->id) ==
                static_cast<int>(prettyscope::TraceMode::Time)) && passed;
        passed = expectNear(
            "trace mode normalized roundtrip",
            prettyscope::getNormalizedVisualChoiceParameter(params, traceMode->id),
            0.0f) && passed;
        passed = expectTrue("trace mode clear revision", params.clearRevision == clearRevision + 1) && passed;
    }

    std::cout << "host parameter roundtrip " << (passed ? "passed" : "failed") << '\n';
    return passed ? 0 : 1;
}
