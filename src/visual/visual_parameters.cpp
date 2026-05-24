#include "visual/visual_parameters.hpp"

#include "visual/visual_param_limits.hpp"

#include <cstdio>

namespace prettyscope
{
namespace
{
constexpr VisualParams kDefaults;

constexpr VisualFloatParameter kFloatParameters[] = {
    {
        VisualFloatParameterId::TraceGain,
        "signal.gain",
        {0x01010001u},
        "Signal Gain",
        "Gain",
        "",
        "Scales incoming signal amplitude before trace mapping.",
        VisualParameterCategory::Signal,
        VisualParameterRole::Visual,
        VisualParameterDisplayMode::Scalar,
        true,
        true,
        kMinTraceGain,
        1.0f,
        kMaxTraceGain,
        kDefaults.traceGain,
        0.08f,
        0.01f,
        2,
    },
    {
        VisualFloatParameterId::GlowStrength,
        "beam.glow_intensity",
        {0x01010002u},
        "Glow Intensity",
        "Glow",
        "",
        "Controls the additive wide-beam glow pass intensity.",
        VisualParameterCategory::Beam,
        VisualParameterRole::Visual,
        VisualParameterDisplayMode::Scalar,
        true,
        true,
        kMinGlowStrength,
        0.5f,
        kMaxGlowStrength,
        kDefaults.glowStrength,
        0.06f,
        0.01f,
        2,
    },
    {
        VisualFloatParameterId::TraceWidth,
        "beam.thickness",
        {0x01010003u},
        "Beam Thickness",
        "Trace",
        "px",
        "Controls the narrow bright beam width in pixels.",
        VisualParameterCategory::Beam,
        VisualParameterRole::Visual,
        VisualParameterDisplayMode::Scalar,
        true,
        true,
        kMinTraceWidth,
        4.0f,
        kMaxTraceWidth,
        kDefaults.traceWidth,
        0.5f,
        0.1f,
        1,
    },
    {
        VisualFloatParameterId::GlowWidth,
        "beam.glow_width",
        {0x01010004u},
        "Glow Width",
        "Bloom",
        "px",
        "Controls the wide glow beam width in pixels.",
        VisualParameterCategory::Beam,
        VisualParameterRole::Visual,
        VisualParameterDisplayMode::Scalar,
        true,
        true,
        kMinTraceWidth,
        8.0f,
        kMaxGlowWidth,
        kDefaults.glowWidth,
        1.0f,
        0.25f,
        1,
    },
    {
        VisualFloatParameterId::Persistence,
        "phosphor.persistence",
        {0x01010005u},
        "Phosphor Persistence",
        "Decay",
        "",
        "Base per-frame retention for the persistence buffer.",
        VisualParameterCategory::Phosphor,
        VisualParameterRole::Visual,
        VisualParameterDisplayMode::Scalar,
        true,
        true,
        kMinPersistence,
        0.9f,
        kMaxPersistence,
        kDefaults.persistence,
        0.03f,
        0.005f,
        3,
    },
    {
        VisualFloatParameterId::FastDecay,
        "phosphor.fast_decay",
        {0x01010006u},
        "Fast Decay",
        "Fast",
        "",
        "Controls how aggressively bright phosphor energy drains.",
        VisualParameterCategory::Phosphor,
        VisualParameterRole::Visual,
        VisualParameterDisplayMode::Scalar,
        true,
        true,
        kMinDecayAmount,
        0.5f,
        kMaxDecayAmount,
        kDefaults.fastDecay,
        0.05f,
        0.01f,
        2,
    },
    {
        VisualFloatParameterId::Afterglow,
        "phosphor.afterglow",
        {0x01010007u},
        "Phosphor Afterglow",
        "Tail",
        "",
        "Controls how long dim phosphor energy lingers.",
        VisualParameterCategory::Phosphor,
        VisualParameterRole::Visual,
        VisualParameterDisplayMode::Scalar,
        true,
        true,
        kMinDecayAmount,
        0.5f,
        kMaxDecayAmount,
        kDefaults.afterglow,
        0.05f,
        0.01f,
        2,
    },
    {
        VisualFloatParameterId::GridIntensity,
        "overlay.grid_intensity",
        {0x01010008u},
        "Grid Intensity",
        "Grid",
        "",
        "Controls overlay grid opacity.",
        VisualParameterCategory::Overlay,
        VisualParameterRole::Visual,
        VisualParameterDisplayMode::Scalar,
        true,
        true,
        0.0f,
        0.5f,
        1.0f,
        kDefaults.gridIntensity,
        0.05f,
        0.01f,
        2,
    },
};

constexpr VisualBoolParameter kBoolParameters[] = {
    {
        VisualBoolParameterId::PersistenceEnabled,
        "phosphor.enabled",
        {0x01020001u},
        "Persistence",
        "Persist",
        "Enables framebuffer persistence and phosphor decay.",
        VisualParameterCategory::Phosphor,
        VisualParameterRole::Visual,
        true,
        true,
        kDefaults.persistenceEnabled,
    },
    {
        VisualBoolParameterId::ShowFps,
        "overlay.fps_enabled",
        {0x01020002u},
        "FPS Overlay",
        "FPS",
        "Shows the debug FPS readout.",
        VisualParameterCategory::Overlay,
        VisualParameterRole::Debug,
        false,
        true,
        kDefaults.showFps,
    },
    {
        VisualBoolParameterId::ShowGrid,
        "overlay.grid_enabled",
        {0x01020003u},
        "Grid Overlay",
        "Grid",
        "Shows the scope grid overlay.",
        VisualParameterCategory::Overlay,
        VisualParameterRole::Visual,
        true,
        true,
        kDefaults.showGrid,
    },
};

constexpr VisualChoiceOption kTraceModeOptions[] = {
    {static_cast<int>(TraceMode::Time), "time", "1D"},
    {static_cast<int>(TraceMode::Xy), "xy", "XY"},
};

constexpr VisualChoiceOption kDecayStyleOptions[] = {
    {static_cast<int>(DecayStyle::Classic), "classic", "Classic"},
    {static_cast<int>(DecayStyle::Phosphor), "phosphor", "Phosphor"},
};

constexpr VisualChoiceParameter kChoiceParameters[] = {
    {
        VisualChoiceParameterId::TraceMode,
        "scope.trace_mode",
        {0x01030001u},
        "Trace Mode",
        "Mode",
        "Selects 1D waveform or XY vectorscope mapping.",
        VisualParameterCategory::Signal,
        VisualParameterRole::Visual,
        true,
        true,
        kTraceModeOptions,
        sizeof(kTraceModeOptions) / sizeof(kTraceModeOptions[0]),
        static_cast<int>(kDefaults.traceMode),
    },
    {
        VisualChoiceParameterId::DecayStyle,
        "phosphor.decay_style",
        {0x01030002u},
        "Decay Style",
        "Decay",
        "Selects classic linear decay or phosphor-style decay.",
        VisualParameterCategory::Phosphor,
        VisualParameterRole::Visual,
        true,
        true,
        kDecayStyleOptions,
        sizeof(kDecayStyleOptions) / sizeof(kDecayStyleOptions[0]),
        static_cast<int>(kDefaults.decayStyle),
    },
};

bool choiceContainsValue(const VisualChoiceParameter& parameter, int value)
{
    for (size_t i = 0; i < parameter.optionCount; ++i)
    {
        if (parameter.options[i].value == value)
        {
            return true;
        }
    }

    return false;
}
}

const VisualFloatParameter* visualFloatParameters(size_t& count)
{
    count = sizeof(kFloatParameters) / sizeof(kFloatParameters[0]);
    return kFloatParameters;
}

const VisualFloatParameter* findVisualFloatParameter(VisualFloatParameterId id)
{
    size_t count = 0;
    const VisualFloatParameter* parameters = visualFloatParameters(count);
    for (size_t i = 0; i < count; ++i)
    {
        if (parameters[i].id == id)
        {
            return &parameters[i];
        }
    }

    return nullptr;
}

float getVisualFloatParameter(const VisualParams& params, VisualFloatParameterId id)
{
    switch (id)
    {
    case VisualFloatParameterId::TraceGain: return params.traceGain;
    case VisualFloatParameterId::GlowStrength: return params.glowStrength;
    case VisualFloatParameterId::TraceWidth: return params.traceWidth;
    case VisualFloatParameterId::GlowWidth: return params.glowWidth;
    case VisualFloatParameterId::Persistence: return params.persistence;
    case VisualFloatParameterId::FastDecay: return params.fastDecay;
    case VisualFloatParameterId::Afterglow: return params.afterglow;
    case VisualFloatParameterId::GridIntensity: return params.gridIntensity;
    }

    return 0.0f;
}

bool setVisualFloatParameter(VisualParams& params, VisualFloatParameterId id, float value)
{
    switch (id)
    {
    case VisualFloatParameterId::TraceGain: params.traceGain = value; break;
    case VisualFloatParameterId::GlowStrength: params.glowStrength = value; break;
    case VisualFloatParameterId::TraceWidth: params.traceWidth = value; break;
    case VisualFloatParameterId::GlowWidth: params.glowWidth = value; break;
    case VisualFloatParameterId::Persistence: params.persistence = value; break;
    case VisualFloatParameterId::FastDecay: params.fastDecay = value; break;
    case VisualFloatParameterId::Afterglow: params.afterglow = value; break;
    case VisualFloatParameterId::GridIntensity: params.gridIntensity = value; break;
    default: return false;
    }

    clampVisualParams(params);
    return true;
}

bool offsetVisualFloatParameter(VisualParams& params, VisualFloatParameterId id, float delta)
{
    return setVisualFloatParameter(params, id, getVisualFloatParameter(params, id) + delta);
}

float normalizeVisualFloatParameter(const VisualFloatParameter& parameter, float value)
{
    if (parameter.maximum <= parameter.minimum)
    {
        return 0.0f;
    }

    const float clamped = clampValue(value, parameter.minimum, parameter.maximum);
    return (clamped - parameter.minimum) / (parameter.maximum - parameter.minimum);
}

float denormalizeVisualFloatParameter(const VisualFloatParameter& parameter, float normalizedValue)
{
    const float clamped = clampValue(normalizedValue, 0.0f, 1.0f);
    return parameter.minimum + clamped * (parameter.maximum - parameter.minimum);
}

float getNormalizedVisualFloatParameter(const VisualParams& params, VisualFloatParameterId id)
{
    const VisualFloatParameter* parameter = findVisualFloatParameter(id);
    if (parameter == nullptr)
    {
        return 0.0f;
    }

    return normalizeVisualFloatParameter(*parameter, getVisualFloatParameter(params, id));
}

bool setNormalizedVisualFloatParameter(VisualParams& params, VisualFloatParameterId id, float normalizedValue)
{
    const VisualFloatParameter* parameter = findVisualFloatParameter(id);
    if (parameter == nullptr)
    {
        return false;
    }

    return setVisualFloatParameter(params, id, denormalizeVisualFloatParameter(*parameter, normalizedValue));
}

std::string formatVisualFloatParameterValue(VisualFloatParameterId id, float value)
{
    char text[32] = {};
    const VisualFloatParameter* parameter = findVisualFloatParameter(id);
    if (parameter == nullptr)
    {
        return {};
    }

    std::snprintf(text, sizeof(text), "%.*f", parameter->precision, value);
    return text;
}

const VisualBoolParameter* visualBoolParameters(size_t& count)
{
    count = sizeof(kBoolParameters) / sizeof(kBoolParameters[0]);
    return kBoolParameters;
}

const VisualBoolParameter* findVisualBoolParameter(VisualBoolParameterId id)
{
    size_t count = 0;
    const VisualBoolParameter* parameters = visualBoolParameters(count);
    for (size_t i = 0; i < count; ++i)
    {
        if (parameters[i].id == id)
        {
            return &parameters[i];
        }
    }

    return nullptr;
}

bool getVisualBoolParameter(const VisualParams& params, VisualBoolParameterId id)
{
    switch (id)
    {
    case VisualBoolParameterId::PersistenceEnabled: return params.persistenceEnabled;
    case VisualBoolParameterId::ShowFps: return params.showFps;
    case VisualBoolParameterId::ShowGrid: return params.showGrid;
    }

    return false;
}

bool setVisualBoolParameter(VisualParams& params, VisualBoolParameterId id, bool value)
{
    switch (id)
    {
    case VisualBoolParameterId::PersistenceEnabled: params.persistenceEnabled = value; return true;
    case VisualBoolParameterId::ShowFps: params.showFps = value; return true;
    case VisualBoolParameterId::ShowGrid: params.showGrid = value; return true;
    }

    return false;
}

const VisualChoiceParameter* visualChoiceParameters(size_t& count)
{
    count = sizeof(kChoiceParameters) / sizeof(kChoiceParameters[0]);
    return kChoiceParameters;
}

const VisualChoiceParameter* findVisualChoiceParameter(VisualChoiceParameterId id)
{
    size_t count = 0;
    const VisualChoiceParameter* parameters = visualChoiceParameters(count);
    for (size_t i = 0; i < count; ++i)
    {
        if (parameters[i].id == id)
        {
            return &parameters[i];
        }
    }

    return nullptr;
}

int getVisualChoiceParameter(const VisualParams& params, VisualChoiceParameterId id)
{
    switch (id)
    {
    case VisualChoiceParameterId::TraceMode: return static_cast<int>(params.traceMode);
    case VisualChoiceParameterId::DecayStyle: return static_cast<int>(params.decayStyle);
    }

    return 0;
}

bool setVisualChoiceParameter(VisualParams& params, VisualChoiceParameterId id, int value)
{
    const VisualChoiceParameter* parameter = findVisualChoiceParameter(id);
    if (parameter == nullptr || !choiceContainsValue(*parameter, value))
    {
        return false;
    }

    switch (id)
    {
    case VisualChoiceParameterId::TraceMode:
        params.traceMode = static_cast<TraceMode>(value);
        ++params.clearRevision;
        return true;
    case VisualChoiceParameterId::DecayStyle:
        params.decayStyle = static_cast<DecayStyle>(value);
        ++params.clearRevision;
        return true;
    }

    return false;
}
}
