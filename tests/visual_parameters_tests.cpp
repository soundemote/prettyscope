#include "visual/visual_parameters.hpp"

#include <iostream>
#include <set>
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

bool expectEqual(const char* name, std::uint32_t actual, std::uint32_t expected)
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

bool rememberDescriptorId(
    const char* name,
    const char* stableId,
    prettyscope::VisualParameterStableId numericId,
    std::set<std::string>& stableIds,
    std::set<std::uint32_t>& numericIds)
{
    bool passed = true;
    passed = expectTrue(name, stableId != nullptr && stableId[0] != '\0') && passed;
    passed = expectTrue(name, numericId.value != 0) && passed;

    if (stableId != nullptr)
    {
        passed = expectTrue(name, stableIds.insert(stableId).second) && passed;
    }

    passed = expectTrue(name, numericIds.insert(numericId.value).second) && passed;
    return passed;
}
}

int main()
{
    size_t count = 0;
    const prettyscope::VisualFloatParameter* parameters = prettyscope::visualFloatParameters(count);

    bool passed = true;
    passed = expectTrue("parameters exist", parameters != nullptr) && passed;
    passed = expectTrue("parameter count", count == 8) && passed;

    std::set<std::string> stableIds;
    std::set<std::uint32_t> numericIds;
    for (size_t i = 0; i < count; ++i)
    {
        passed = rememberDescriptorId(
            "unique float descriptor id",
            parameters[i].stableId,
            parameters[i].numericId,
            stableIds,
            numericIds) && passed;
    }

    const prettyscope::VisualFloatParameter* traceGain =
        prettyscope::findVisualFloatParameter(prettyscope::VisualFloatParameterId::TraceGain);
    passed = expectTrue("find trace gain", traceGain != nullptr) && passed;
    if (traceGain != nullptr)
    {
        passed = expectEqual("trace gain default", traceGain->defaultValue, 0.10f) && passed;
        passed = expectEqual("trace gain midpoint", traceGain->midpoint, 1.0f) && passed;
        passed = expectEqual("trace gain stable string", std::string(traceGain->stableId), "signal.gain") && passed;
        passed = expectEqual("trace gain stable numeric", traceGain->numericId.value, 0x01010001u) && passed;
        passed = expectTrue("trace gain automatable", traceGain->automatable) && passed;
        passed = expectTrue("trace gain visible", traceGain->visible) && passed;
        passed = expectTrue("trace gain category", traceGain->category == prettyscope::VisualParameterCategory::Signal) && passed;
        passed = expectTrue("trace gain role", traceGain->role == prettyscope::VisualParameterRole::Visual) && passed;
        passed = expectTrue("trace gain precision", traceGain->precision == 2) && passed;
        passed = expectEqual("trace gain step", traceGain->step, 0.08f) && passed;
        passed = expectEqual("trace gain fine step", traceGain->fineStep, 0.01f) && passed;
    }
    passed = expectTrue(
        "find trace gain by stable id",
        prettyscope::findVisualFloatParameterByStableId("signal.gain") == traceGain) && passed;
    passed = expectTrue(
        "find trace gain by numeric id",
        prettyscope::findVisualFloatParameterByNumericId({0x01010001u}) == traceGain) && passed;
    passed = expectTrue(
        "missing float stable id",
        prettyscope::findVisualFloatParameterByStableId("missing.parameter") == nullptr) && passed;
    passed = expectTrue(
        "null float stable id",
        prettyscope::findVisualFloatParameterByStableId(nullptr) == nullptr) && passed;

    prettyscope::VisualParams params;
    passed = expectTrue(
        "set trace gain",
        prettyscope::setVisualFloatParameter(params, prettyscope::VisualFloatParameterId::TraceGain, 99.0f)) && passed;
    passed = expectEqual(
        "trace gain clamps",
        prettyscope::getVisualFloatParameter(params, prettyscope::VisualFloatParameterId::TraceGain),
        4.0f) && passed;
    passed = expectTrue(
        "offset trace gain",
        prettyscope::offsetVisualFloatParameter(params, prettyscope::VisualFloatParameterId::TraceGain, -0.5f)) && passed;
    passed = expectEqual(
        "offset trace gain value",
        prettyscope::getVisualFloatParameter(params, prettyscope::VisualFloatParameterId::TraceGain),
        3.5f) && passed;

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

    size_t boolCount = 0;
    const prettyscope::VisualBoolParameter* bools = prettyscope::visualBoolParameters(boolCount);
    passed = expectTrue("bool parameters exist", bools != nullptr) && passed;
    passed = expectTrue("bool parameter count", boolCount == 3) && passed;
    for (size_t i = 0; i < boolCount; ++i)
    {
        passed = rememberDescriptorId(
            "unique bool descriptor id",
            bools[i].stableId,
            bools[i].numericId,
            stableIds,
            numericIds) && passed;
    }
    const prettyscope::VisualBoolParameter* fps =
        prettyscope::findVisualBoolParameter(prettyscope::VisualBoolParameterId::ShowFps);
    passed = expectTrue("find fps bool", fps != nullptr) && passed;
    if (fps != nullptr)
    {
        passed = expectEqual("fps stable string", std::string(fps->stableId), "overlay.fps_enabled") && passed;
        passed = expectEqual("fps stable numeric", fps->numericId.value, 0x01020002u) && passed;
        passed = expectTrue("fps not automatable", !fps->automatable) && passed;
        passed = expectTrue("fps debug role", fps->role == prettyscope::VisualParameterRole::Debug) && passed;
    }
    passed = expectTrue(
        "find fps by stable id",
        prettyscope::findVisualBoolParameterByStableId("overlay.fps_enabled") == fps) && passed;
    passed = expectTrue(
        "find fps by numeric id",
        prettyscope::findVisualBoolParameterByNumericId({0x01020002u}) == fps) && passed;
    passed = expectTrue(
        "set show grid",
        prettyscope::setVisualBoolParameter(params, prettyscope::VisualBoolParameterId::ShowGrid, true)) && passed;
    passed = expectTrue(
        "get show grid",
        prettyscope::getVisualBoolParameter(params, prettyscope::VisualBoolParameterId::ShowGrid)) && passed;
    passed = expectEqual(
        "get normalized show grid",
        prettyscope::getNormalizedVisualBoolParameter(params, prettyscope::VisualBoolParameterId::ShowGrid),
        1.0f) && passed;
    passed = expectTrue(
        "set normalized show grid",
        prettyscope::setNormalizedVisualBoolParameter(params, prettyscope::VisualBoolParameterId::ShowGrid, 0.25f)) && passed;
    passed = expectTrue(
        "normalized show grid value",
        !prettyscope::getVisualBoolParameter(params, prettyscope::VisualBoolParameterId::ShowGrid)) && passed;

    size_t choiceCount = 0;
    const prettyscope::VisualChoiceParameter* choices = prettyscope::visualChoiceParameters(choiceCount);
    passed = expectTrue("choice parameters exist", choices != nullptr) && passed;
    passed = expectTrue("choice parameter count", choiceCount == 2) && passed;
    for (size_t i = 0; i < choiceCount; ++i)
    {
        passed = rememberDescriptorId(
            "unique choice descriptor id",
            choices[i].stableId,
            choices[i].numericId,
            stableIds,
            numericIds) && passed;
    }
    const prettyscope::VisualChoiceParameter* traceMode =
        prettyscope::findVisualChoiceParameter(prettyscope::VisualChoiceParameterId::TraceMode);
    passed = expectTrue("find trace mode", traceMode != nullptr) && passed;
    if (traceMode != nullptr)
    {
        passed = expectEqual("trace mode stable string", std::string(traceMode->stableId), "scope.trace_mode") && passed;
        passed = expectEqual("trace mode stable numeric", traceMode->numericId.value, 0x01030001u) && passed;
        passed = expectTrue("trace mode options", traceMode->optionCount == 2) && passed;
        passed = expectEqual(
            "normalize trace mode first option",
            prettyscope::normalizeVisualChoiceParameter(*traceMode, static_cast<int>(prettyscope::TraceMode::Time)),
            0.0f) && passed;
        passed = expectEqual(
            "normalize trace mode last option",
            prettyscope::normalizeVisualChoiceParameter(*traceMode, static_cast<int>(prettyscope::TraceMode::Xy)),
            1.0f) && passed;
        passed = expectTrue(
            "denormalize trace mode first option",
            prettyscope::denormalizeVisualChoiceParameter(*traceMode, 0.0f) ==
                static_cast<int>(prettyscope::TraceMode::Time)) && passed;
        passed = expectTrue(
            "denormalize trace mode last option",
            prettyscope::denormalizeVisualChoiceParameter(*traceMode, 1.0f) ==
                static_cast<int>(prettyscope::TraceMode::Xy)) && passed;
    }
    passed = expectTrue(
        "find trace mode by stable id",
        prettyscope::findVisualChoiceParameterByStableId("scope.trace_mode") == traceMode) && passed;
    passed = expectTrue(
        "find trace mode by numeric id",
        prettyscope::findVisualChoiceParameterByNumericId({0x01030001u}) == traceMode) && passed;

    const int clearRevision = params.clearRevision;
    passed = expectTrue(
        "set trace mode choice",
        prettyscope::setVisualChoiceParameter(
            params,
            prettyscope::VisualChoiceParameterId::TraceMode,
            static_cast<int>(prettyscope::TraceMode::Time))) && passed;
    passed = expectTrue("trace mode clear", params.clearRevision == clearRevision + 1) && passed;
    passed = expectEqual(
        "get normalized trace mode",
        prettyscope::getNormalizedVisualChoiceParameter(params, prettyscope::VisualChoiceParameterId::TraceMode),
        0.0f) && passed;
    passed = expectTrue(
        "set normalized trace mode choice",
        prettyscope::setNormalizedVisualChoiceParameter(
            params,
            prettyscope::VisualChoiceParameterId::TraceMode,
            1.0f)) && passed;
    passed = expectTrue(
        "normalized trace mode value",
        params.traceMode == prettyscope::TraceMode::Xy) && passed;
    passed = expectTrue("normalized trace mode clear", params.clearRevision == clearRevision + 2) && passed;
    passed = expectTrue(
        "invalid choice rejected",
        !prettyscope::setVisualChoiceParameter(params, prettyscope::VisualChoiceParameterId::TraceMode, 99)) && passed;

    return passed ? 0 : 1;
}
