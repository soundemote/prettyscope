#include "visual/test_signal.hpp"

#include <cmath>

namespace prettyscope
{
namespace
{
constexpr float kPi = 3.14159265358979323846f;
}

void TestSignalGenerator::advance(SignalBuffer& signal, float dt)
{
    phase_ += dt;

    for (int i = 0; i < signal.size(); ++i)
    {
        const float x = static_cast<float>(i) / static_cast<float>(signal.size() - 1);
        switch (mode_)
        {
        case Mode::Lissajousish:
        {
            const float fold = std::sin((x * 3.0f + phase_ * 0.33f) * 2.0f * kPi);
            const float weave = std::sin((x * 13.0f - phase_ * 0.72f) * 2.0f * kPi);
            signal[i] = 0.48f * std::sin((x * 5.0f + fold * 0.22f + phase_ * 0.4f) * 2.0f * kPi) + 0.18f * weave;
            signal.right(i) = 0.48f * std::sin((x * 4.0f + fold * 0.18f - phase_ * 0.31f) * 2.0f * kPi) - 0.15f * weave;
            break;
        }
        case Mode::BassPulse:
        {
            const float pulse = 0.5f + 0.5f * std::sin(phase_ * 3.2f);
            const float carrier = std::sin((x * 4.0f + phase_ * 0.28f) * 2.0f * kPi);
            const float quadrature = std::sin((x * 4.0f + phase_ * 0.28f) * 2.0f * kPi + kPi * 0.5f);
            const float edge = std::sin((x * 19.0f - phase_ * 1.1f) * 2.0f * kPi);
            signal[i] = (0.28f + pulse * 0.46f) * carrier + 0.06f * edge;
            signal.right(i) = (0.28f + pulse * 0.46f) * quadrature - 0.06f * edge;
            break;
        }
        case Mode::Musical:
        default:
        {
            const float slowSweep = std::sin((x * 2.0f + phase_ * 0.37f) * kPi);
            const float carrier = std::sin((x * 7.0f + phase_ * 0.85f) * 2.0f * kPi);
            const float stereoCarrier = std::sin((x * 6.0f - phase_ * 0.68f) * 2.0f * kPi);
            const float shimmer = std::sin((x * 31.0f - phase_ * 1.7f) * 2.0f * kPi);
            signal[i] = 0.56f * carrier + 0.26f * slowSweep + 0.08f * shimmer;
            signal.right(i) = 0.52f * stereoCarrier - 0.20f * slowSweep + 0.10f * shimmer;
            break;
        }
        }
    }
}

SignalSourceInfo TestSignalGenerator::info() const
{
    return {modeName(), SignalLayout::Stereo, TraceMode::Xy};
}

void TestSignalGenerator::nextMode()
{
    switch (mode_)
    {
    case Mode::Musical:
        mode_ = Mode::Lissajousish;
        break;
    case Mode::Lissajousish:
        mode_ = Mode::BassPulse;
        break;
    case Mode::BassPulse:
        mode_ = Mode::Musical;
        break;
    }
}

void TestSignalGenerator::setMode(Mode mode)
{
    mode_ = mode;
}

TestSignalGenerator::Mode TestSignalGenerator::mode() const
{
    return mode_;
}

const char* TestSignalGenerator::modeName() const
{
    switch (mode_)
    {
    case Mode::Lissajousish:
        return "fold";
    case Mode::BassPulse:
        return "bass";
    case Mode::Musical:
    default:
        return "musical";
    }
}
}
