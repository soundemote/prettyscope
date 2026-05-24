#include "app/standalone_controls.hpp"

#include "app/preset_store.hpp"

#include "visual/visual_param_limits.hpp"
#include "visual/visual_parameters.hpp"
#include "visual/visual_palettes.hpp"

#include <cstdio>

namespace prettyscope
{
void StandaloneControls::update(Win32GlWindow& window, VisualParams& params, TestSignalGenerator& generator)
{
    const VisualFloatParameter* traceGain = findVisualFloatParameter(VisualFloatParameterId::TraceGain);
    const VisualFloatParameter* glowStrength = findVisualFloatParameter(VisualFloatParameterId::GlowStrength);
    const VisualFloatParameter* traceWidth = findVisualFloatParameter(VisualFloatParameterId::TraceWidth);
    const VisualFloatParameter* glowWidth = findVisualFloatParameter(VisualFloatParameterId::GlowWidth);
    const VisualFloatParameter* persistence = findVisualFloatParameter(VisualFloatParameterId::Persistence);
    const VisualFloatParameter* fastDecay = findVisualFloatParameter(VisualFloatParameterId::FastDecay);
    const VisualFloatParameter* afterglow = findVisualFloatParameter(VisualFloatParameterId::Afterglow);

    const int wheelDelta = window.consumeMouseWheelDelta();
    if (wheelDelta != 0 && traceGain != nullptr)
    {
        const float wheelSteps = static_cast<float>(wheelDelta) / static_cast<float>(WHEEL_DELTA);
        offsetVisualFloatParameter(params, VisualFloatParameterId::TraceGain, wheelSteps * traceGain->step);
    }

    if (pressed(window, '1') && traceGain != nullptr)
    {
        offsetVisualFloatParameter(params, VisualFloatParameterId::TraceGain, -traceGain->step);
    }
    if (pressed(window, '2') && traceGain != nullptr)
    {
        offsetVisualFloatParameter(params, VisualFloatParameterId::TraceGain, traceGain->step);
    }

    if (pressed(window, '3') && glowStrength != nullptr)
    {
        offsetVisualFloatParameter(params, VisualFloatParameterId::GlowStrength, -glowStrength->step);
    }
    if (pressed(window, '4') && glowStrength != nullptr)
    {
        offsetVisualFloatParameter(params, VisualFloatParameterId::GlowStrength, glowStrength->step);
    }

    if (pressed(window, '5') && traceWidth != nullptr)
    {
        offsetVisualFloatParameter(params, VisualFloatParameterId::TraceWidth, -traceWidth->step);
    }
    if (pressed(window, '6') && traceWidth != nullptr)
    {
        offsetVisualFloatParameter(params, VisualFloatParameterId::TraceWidth, traceWidth->step);
    }

    if (pressed(window, '7') && glowWidth != nullptr)
    {
        offsetVisualFloatParameter(params, VisualFloatParameterId::GlowWidth, -glowWidth->step);
    }
    if (pressed(window, '8') && glowWidth != nullptr)
    {
        offsetVisualFloatParameter(params, VisualFloatParameterId::GlowWidth, glowWidth->step);
    }

    if (pressed(window, '9') && persistence != nullptr)
    {
        offsetVisualFloatParameter(params, VisualFloatParameterId::Persistence, -persistence->step);
    }
    if (pressed(window, '0') && persistence != nullptr)
    {
        offsetVisualFloatParameter(params, VisualFloatParameterId::Persistence, persistence->step);
    }
    if (pressed(window, VK_OEM_4) && persistence != nullptr)
    {
        offsetVisualFloatParameter(params, VisualFloatParameterId::Persistence, -persistence->fineStep);
    }
    if (pressed(window, VK_OEM_6) && persistence != nullptr)
    {
        offsetVisualFloatParameter(params, VisualFloatParameterId::Persistence, persistence->fineStep);
    }
    if (pressed(window, 'T') && fastDecay != nullptr)
    {
        offsetVisualFloatParameter(params, VisualFloatParameterId::FastDecay, -fastDecay->step);
    }
    if (pressed(window, 'Y') && fastDecay != nullptr)
    {
        offsetVisualFloatParameter(params, VisualFloatParameterId::FastDecay, fastDecay->step);
    }
    if (pressed(window, VK_OEM_MINUS) && afterglow != nullptr)
    {
        offsetVisualFloatParameter(params, VisualFloatParameterId::Afterglow, -afterglow->step);
    }
    if (pressed(window, VK_OEM_PLUS) && afterglow != nullptr)
    {
        offsetVisualFloatParameter(params, VisualFloatParameterId::Afterglow, afterglow->step);
    }
    if (pressed(window, 'P'))
    {
        setVisualBoolParameter(
            params,
            VisualBoolParameterId::PersistenceEnabled,
            !getVisualBoolParameter(params, VisualBoolParameterId::PersistenceEnabled));
    }
    if (pressed(window, 'D'))
    {
        const DecayStyle nextStyle = params.decayStyle == DecayStyle::Classic ? DecayStyle::Phosphor : DecayStyle::Classic;
        setVisualChoiceParameter(params, VisualChoiceParameterId::DecayStyle, static_cast<int>(nextStyle));
    }
    if (pressed(window, 'F'))
    {
        setVisualBoolParameter(params, VisualBoolParameterId::ShowFps, !getVisualBoolParameter(params, VisualBoolParameterId::ShowFps));
    }
    if (pressed(window, 'G'))
    {
        setVisualBoolParameter(params, VisualBoolParameterId::ShowGrid, !getVisualBoolParameter(params, VisualBoolParameterId::ShowGrid));
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
        const TraceMode nextMode = params.traceMode == TraceMode::Time ? TraceMode::Xy : TraceMode::Time;
        setVisualChoiceParameter(params, VisualChoiceParameterId::TraceMode, static_cast<int>(nextMode));
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
        "Prettyscope | %s | signal %s Space | color C | gain 1/2 %s | glow 3/4 %s | trace 5/6 %s | bloom 7/8 %s | decay 9/0 [/] %s | fast T/Y %s | tail -/= %s | %s P | style D %s | F fps | G grid | X mode | S save | L load | R reset",
        params.traceMode == TraceMode::Time ? "1D" : "XY",
        generator.modeName(),
        formatVisualFloatParameterValue(VisualFloatParameterId::TraceGain, params.traceGain).c_str(),
        formatVisualFloatParameterValue(VisualFloatParameterId::GlowStrength, params.glowStrength).c_str(),
        formatVisualFloatParameterValue(VisualFloatParameterId::TraceWidth, params.traceWidth).c_str(),
        formatVisualFloatParameterValue(VisualFloatParameterId::GlowWidth, params.glowWidth).c_str(),
        formatVisualFloatParameterValue(VisualFloatParameterId::Persistence, params.persistence).c_str(),
        formatVisualFloatParameterValue(VisualFloatParameterId::FastDecay, params.fastDecay).c_str(),
        formatVisualFloatParameterValue(VisualFloatParameterId::Afterglow, params.afterglow).c_str(),
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
    size_t count = 0;
    visualPalettes(count);
    if (count == 0)
    {
        return;
    }

    paletteIndex_ = (paletteIndex_ + 1) % count;
    applyVisualPalette(params, paletteIndex_);
}
}
