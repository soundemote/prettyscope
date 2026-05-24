#pragma once

#include "visual/visual_params.hpp"

#include <cstddef>
#include <cstdint>
#include <string>

namespace prettyscope
{
inline constexpr std::uint32_t kVisualParameterStateVersion = 1;

struct VisualParameterStableId
{
    std::uint32_t value = 0;
};

enum class VisualParameterCategory
{
    Beam,
    Phosphor,
    Overlay,
    Palette,
    Signal,
    Debug,
};

enum class VisualParameterRole
{
    Visual,
    Debug,
    Performance,
    State,
    Internal,
};

enum class VisualParameterDisplayMode
{
    Scalar,
    Percent,
};

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

enum class VisualBoolParameterId
{
    PersistenceEnabled,
    ShowFps,
    ShowGrid,
};

enum class VisualChoiceParameterId
{
    TraceMode,
    DecayStyle,
};

struct VisualFloatParameter
{
    VisualFloatParameterId id;
    const char* stableId;
    VisualParameterStableId numericId;
    const char* displayName;
    const char* shortName;
    const char* unit;
    const char* description;
    VisualParameterCategory category;
    VisualParameterRole role;
    VisualParameterDisplayMode displayMode;
    bool automatable;
    bool visible;
    float minimum;
    float midpoint;
    float maximum;
    float defaultValue;
    float step;
    float fineStep;
    int precision;
};

struct VisualBoolParameter
{
    VisualBoolParameterId id;
    const char* stableId;
    VisualParameterStableId numericId;
    const char* displayName;
    const char* shortName;
    const char* description;
    VisualParameterCategory category;
    VisualParameterRole role;
    bool automatable;
    bool visible;
    bool defaultValue;
};

struct VisualChoiceOption
{
    int value;
    const char* key;
    const char* label;
};

struct VisualChoiceParameter
{
    VisualChoiceParameterId id;
    const char* stableId;
    VisualParameterStableId numericId;
    const char* displayName;
    const char* shortName;
    const char* description;
    VisualParameterCategory category;
    VisualParameterRole role;
    bool automatable;
    bool visible;
    const VisualChoiceOption* options;
    size_t optionCount;
    int defaultValue;
};

const VisualFloatParameter* visualFloatParameters(size_t& count);
const VisualFloatParameter* findVisualFloatParameter(VisualFloatParameterId id);
const VisualFloatParameter* findVisualFloatParameterByStableId(const char* stableId);
const VisualFloatParameter* findVisualFloatParameterByNumericId(VisualParameterStableId numericId);
float getVisualFloatParameter(const VisualParams& params, VisualFloatParameterId id);
bool setVisualFloatParameter(VisualParams& params, VisualFloatParameterId id, float value);
bool offsetVisualFloatParameter(VisualParams& params, VisualFloatParameterId id, float delta);
float normalizeVisualFloatParameter(const VisualFloatParameter& parameter, float value);
float denormalizeVisualFloatParameter(const VisualFloatParameter& parameter, float normalizedValue);
float getNormalizedVisualFloatParameter(const VisualParams& params, VisualFloatParameterId id);
bool setNormalizedVisualFloatParameter(VisualParams& params, VisualFloatParameterId id, float normalizedValue);
std::string formatVisualFloatParameterValue(VisualFloatParameterId id, float value);

const VisualBoolParameter* visualBoolParameters(size_t& count);
const VisualBoolParameter* findVisualBoolParameter(VisualBoolParameterId id);
const VisualBoolParameter* findVisualBoolParameterByStableId(const char* stableId);
const VisualBoolParameter* findVisualBoolParameterByNumericId(VisualParameterStableId numericId);
bool getVisualBoolParameter(const VisualParams& params, VisualBoolParameterId id);
bool setVisualBoolParameter(VisualParams& params, VisualBoolParameterId id, bool value);
float getNormalizedVisualBoolParameter(const VisualParams& params, VisualBoolParameterId id);
bool setNormalizedVisualBoolParameter(VisualParams& params, VisualBoolParameterId id, float normalizedValue);

const VisualChoiceParameter* visualChoiceParameters(size_t& count);
const VisualChoiceParameter* findVisualChoiceParameter(VisualChoiceParameterId id);
const VisualChoiceParameter* findVisualChoiceParameterByStableId(const char* stableId);
const VisualChoiceParameter* findVisualChoiceParameterByNumericId(VisualParameterStableId numericId);
int getVisualChoiceParameter(const VisualParams& params, VisualChoiceParameterId id);
bool setVisualChoiceParameter(VisualParams& params, VisualChoiceParameterId id, int value);
float normalizeVisualChoiceParameter(const VisualChoiceParameter& parameter, int value);
int denormalizeVisualChoiceParameter(const VisualChoiceParameter& parameter, float normalizedValue);
float getNormalizedVisualChoiceParameter(const VisualParams& params, VisualChoiceParameterId id);
bool setNormalizedVisualChoiceParameter(VisualParams& params, VisualChoiceParameterId id, float normalizedValue);
}
