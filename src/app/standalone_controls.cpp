#include "app/standalone_controls.hpp"

#include "app/preset_store.hpp"

#include "visual/visual_param_limits.hpp"

#include <cstdio>

namespace prettyscope
{
void StandaloneControls::update(Win32GlWindow& window, VisualParams& params, TestSignalGenerator& generator)
{
    const int wheelDelta = window.consumeMouseWheelDelta();
    if (wheelDelta != 0)
    {
        const float wheelSteps = static_cast<float>(wheelDelta) / static_cast<float>(WHEEL_DELTA);
        params.traceGain = clampValue(params.traceGain + wheelSteps * 0.08f, kMinTraceGain, kMaxTraceGain);
    }

    if (pressed(window, '1'))
    {
        params.traceGain = clampValue(params.traceGain - 0.08f, kMinTraceGain, kMaxTraceGain);
    }
    if (pressed(window, '2'))
    {
        params.traceGain = clampValue(params.traceGain + 0.08f, kMinTraceGain, kMaxTraceGain);
    }

    if (pressed(window, '3'))
    {
        params.glowStrength = clampValue(params.glowStrength - 0.06f, kMinGlowStrength, kMaxGlowStrength);
    }
    if (pressed(window, '4'))
    {
        params.glowStrength = clampValue(params.glowStrength + 0.06f, kMinGlowStrength, kMaxGlowStrength);
    }

    if (pressed(window, '5'))
    {
        params.traceWidth = clampValue(params.traceWidth - 0.5f, kMinTraceWidth, kMaxTraceWidth);
    }
    if (pressed(window, '6'))
    {
        params.traceWidth = clampValue(params.traceWidth + 0.5f, kMinTraceWidth, kMaxTraceWidth);
    }

    if (pressed(window, '7'))
    {
        params.glowWidth = clampValue(params.glowWidth - 1.0f, params.traceWidth, kMaxGlowWidth);
    }
    if (pressed(window, '8'))
    {
        params.glowWidth = clampValue(params.glowWidth + 1.0f, params.traceWidth, kMaxGlowWidth);
    }

    if (pressed(window, '9'))
    {
        params.persistence = clampValue(params.persistence - 0.03f, kMinPersistence, kMaxPersistence);
    }
    if (pressed(window, '0'))
    {
        params.persistence = clampValue(params.persistence + 0.03f, kMinPersistence, kMaxPersistence);
    }
    if (pressed(window, VK_OEM_4))
    {
        params.persistence = clampValue(params.persistence - 0.005f, kMinPersistence, kMaxPersistence);
    }
    if (pressed(window, VK_OEM_6))
    {
        params.persistence = clampValue(params.persistence + 0.005f, kMinPersistence, kMaxPersistence);
    }
    if (pressed(window, 'T'))
    {
        params.fastDecay = clampValue(params.fastDecay - 0.05f, kMinDecayAmount, kMaxDecayAmount);
    }
    if (pressed(window, 'Y'))
    {
        params.fastDecay = clampValue(params.fastDecay + 0.05f, kMinDecayAmount, kMaxDecayAmount);
    }
    if (pressed(window, VK_OEM_MINUS))
    {
        params.afterglow = clampValue(params.afterglow - 0.05f, kMinDecayAmount, kMaxDecayAmount);
    }
    if (pressed(window, VK_OEM_PLUS))
    {
        params.afterglow = clampValue(params.afterglow + 0.05f, kMinDecayAmount, kMaxDecayAmount);
    }
    if (pressed(window, 'P'))
    {
        params.persistenceEnabled = !params.persistenceEnabled;
    }
    if (pressed(window, 'D'))
    {
        params.decayStyle = params.decayStyle == DecayStyle::Classic ? DecayStyle::Phosphor : DecayStyle::Classic;
        ++params.clearRevision;
    }
    if (pressed(window, 'F'))
    {
        params.showFps = !params.showFps;
    }
    if (pressed(window, 'G'))
    {
        params.showGrid = !params.showGrid;
    }
    if (pressed(window, 'S'))
    {
        PresetStore::saveDefault(params, generator);
    }
    if (pressed(window, 'L'))
    {
        PresetStore::loadDefault(params, generator);
        clampVisualParams(params);
    }

    if (pressed(window, VK_SPACE))
    {
        generator.nextMode();
        ++params.clearRevision;
    }
    if (pressed(window, 'X'))
    {
        params.traceMode = params.traceMode == TraceMode::Time ? TraceMode::Xy : TraceMode::Time;
        ++params.clearRevision;
    }
    if (pressed(window, 'C'))
    {
        cyclePalette(params);
        ++params.clearRevision;
    }
    if (pressed(window, 'R'))
    {
        const int nextClearRevision = params.clearRevision + 1;
        params = {};
        params.clearRevision = nextClearRevision;
        paletteIndex_ = 0;
    }
}

std::string StandaloneControls::titleText(const VisualParams& params, const TestSignalGenerator& generator) const
{
    char text[512] = {};
    std::snprintf(
        text,
        sizeof(text),
        "Prettyscope | %s | signal %s Space | color C | gain 1/2 %.2f | glow 3/4 %.2f | trace 5/6 %.1f | bloom 7/8 %.1f | decay 9/0 [/] %.3f | fast T/Y %.2f | tail -/= %.2f | %s P | style D %s | F fps | G grid | X mode | S save | L load | R reset",
        params.traceMode == TraceMode::Time ? "1D" : "XY",
        generator.modeName(),
        params.traceGain,
        params.glowStrength,
        params.traceWidth,
        params.glowWidth,
        params.persistence,
        params.fastDecay,
        params.afterglow,
        params.persistenceEnabled ? "on" : "off",
        params.decayStyle == DecayStyle::Classic ? "classic" : "phosphor");
    return text;
}

bool StandaloneControls::pressed(const Win32GlWindow& window, int key)
{
    const bool down = window.isKeyDown(key);
    const bool wasDown = previousKeys_[static_cast<size_t>(key)];
    previousKeys_[static_cast<size_t>(key)] = down;
    return down && !wasDown;
}

void StandaloneControls::cyclePalette(VisualParams& params)
{
    paletteIndex_ = (paletteIndex_ + 1) % 4;

    switch (paletteIndex_)
    {
    case 0:
        params.traceColor = {1.0f, 0.22f, 0.70f};
        params.glowColor = {0.18f, 0.80f, 1.0f};
        params.backgroundColor = {0.018f, 0.012f, 0.026f};
        break;
    case 1:
        params.traceColor = {1.0f, 0.86f, 0.26f};
        params.glowColor = {1.0f, 0.18f, 0.08f};
        params.backgroundColor = {0.018f, 0.010f, 0.006f};
        break;
    case 2:
        params.traceColor = {0.72f, 1.0f, 0.32f};
        params.glowColor = {0.16f, 0.92f, 0.62f};
        params.backgroundColor = {0.008f, 0.016f, 0.012f};
        break;
    default:
        params.traceColor = {0.24f, 0.92f, 0.78f};
        params.glowColor = {0.95f, 0.20f, 0.72f};
        params.backgroundColor = {0.015f, 0.014f, 0.022f};
        break;
    }
}
}
