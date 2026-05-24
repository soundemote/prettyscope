#pragma once

#include "visual/scope_renderer.hpp"
#include "visual/signal_buffer.hpp"
#include "visual/signal_source.hpp"
#include "visual/visual_params.hpp"

namespace prettyscope
{
class ScopeEngine
{
public:
    explicit ScopeEngine(int sampleCount);

    ScopeEngine(const ScopeEngine&) = delete;
    ScopeEngine& operator=(const ScopeEngine&) = delete;

    void initialize();
    void shutdown();
    bool initialized() const;
    void advance(SignalSource& source, float dt);
    void render(SignalSource& source, float dt, int width, int height);
    void renderCurrentSignal(int width, int height);
    void setSignal(const SignalBuffer& signal);
    void setSampleCount(int sampleCount);
    int sampleCount() const;

    VisualParams& params();
    const VisualParams& params() const;
    void setParams(const VisualParams& params);
    void requestClear();

    SignalBuffer& signal();
    const SignalBuffer& signal() const;

private:
    VisualParams params_;
    SignalBuffer signal_;
    ScopeRenderer renderer_;
    bool initialized_ = false;
};
}
