#pragma once

#include "visual/signal_source.hpp"

namespace prettyscope
{
class TestSignalGenerator : public SignalSource
{
public:
    enum class Mode
    {
        Musical,
        Lissajousish,
        BassPulse,
    };

    SignalSourceInfo info() const override;
    void advance(SignalBuffer& signal, float dt) override;
    void nextMode();
    void setMode(Mode mode);
    Mode mode() const;
    const char* modeName() const;

private:
    float phase_ = 0.0f;
    Mode mode_ = Mode::Lissajousish;
};
}
