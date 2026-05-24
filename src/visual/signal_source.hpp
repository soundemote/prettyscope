#pragma once

#include "visual/signal_buffer.hpp"
#include "visual/visual_params.hpp"

namespace prettyscope
{
enum class SignalLayout
{
    Mono,
    Stereo,
};

struct SignalSourceInfo
{
    const char* name = "";
    SignalLayout layout = SignalLayout::Stereo;
    TraceMode suggestedTraceMode = TraceMode::Xy;
};

class SignalSource
{
public:
    virtual ~SignalSource() = default;

    virtual SignalSourceInfo info() const = 0;
    virtual void advance(SignalBuffer& signal, float dt) = 0;
};
}
