#pragma once

#include "visual/visual_params.hpp"

#include <algorithm>

namespace prettyscope
{
constexpr float kMinTraceGain = 0.10f;
constexpr float kMaxTraceGain = 4.00f;
constexpr float kMinGlowStrength = 0.0f;
constexpr float kMaxGlowStrength = 1.0f;
constexpr float kMinTraceWidth = 1.0f;
constexpr float kMaxTraceWidth = 12.0f;
constexpr float kMaxGlowWidth = 24.0f;
constexpr float kMinPersistence = 0.0f;
constexpr float kMaxPersistence = 0.98f;
constexpr float kMinDecayAmount = 0.0f;
constexpr float kMaxDecayAmount = 1.0f;

inline float clampValue(float value, float minValue, float maxValue)
{
    return std::max(minValue, std::min(maxValue, value));
}

inline RgbColor clampColor(RgbColor color)
{
    return {
        clampValue(color.r, 0.0f, 1.0f),
        clampValue(color.g, 0.0f, 1.0f),
        clampValue(color.b, 0.0f, 1.0f)};
}

inline void clampVisualParams(VisualParams& params)
{
    params.backgroundColor = clampColor(params.backgroundColor);
    params.traceColor = clampColor(params.traceColor);
    params.glowColor = clampColor(params.glowColor);
    params.traceGain = clampValue(params.traceGain, kMinTraceGain, kMaxTraceGain);
    params.glowStrength = clampValue(params.glowStrength, kMinGlowStrength, kMaxGlowStrength);
    params.traceWidth = clampValue(params.traceWidth, kMinTraceWidth, kMaxTraceWidth);
    params.glowWidth = clampValue(params.glowWidth, params.traceWidth, kMaxGlowWidth);
    params.persistence = clampValue(params.persistence, kMinPersistence, kMaxPersistence);
    params.fastDecay = clampValue(params.fastDecay, kMinDecayAmount, kMaxDecayAmount);
    params.afterglow = clampValue(params.afterglow, kMinDecayAmount, kMaxDecayAmount);
    params.gridIntensity = clampValue(params.gridIntensity, 0.0f, 1.0f);
}
}
