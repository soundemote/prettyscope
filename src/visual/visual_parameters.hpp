#pragma once

#include "visual/visual_params.hpp"

#include <cstddef>

namespace prettyscope
{
enum class VisualFloatParameterId
{
    TraceGain,
    GlowStrength,
    TraceWidth,
    GlowWidth,
    Persistence,
    FastDecay,
    Afterglow,
    GridIntensity,
};

struct VisualFloatParameter
{
    VisualFloatParameterId id;
    const char* key;
    const char* label;
    float minimum;
    float maximum;
    float defaultValue;
};

const VisualFloatParameter* visualFloatParameters(size_t& count);
const VisualFloatParameter* findVisualFloatParameter(VisualFloatParameterId id);
float getVisualFloatParameter(const VisualParams& params, VisualFloatParameterId id);
bool setVisualFloatParameter(VisualParams& params, VisualFloatParameterId id, float value);
float normalizeVisualFloatParameter(const VisualFloatParameter& parameter, float value);
float denormalizeVisualFloatParameter(const VisualFloatParameter& parameter, float normalizedValue);
float getNormalizedVisualFloatParameter(const VisualParams& params, VisualFloatParameterId id);
bool setNormalizedVisualFloatParameter(VisualParams& params, VisualFloatParameterId id, float normalizedValue);
}
