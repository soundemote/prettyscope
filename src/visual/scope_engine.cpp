#include "visual/scope_engine.hpp"

#include "visual/visual_param_limits.hpp"

namespace prettyscope
{
ScopeEngine::ScopeEngine(int sampleCount)
    : signal_(sampleCount)
{
}

void ScopeEngine::initialize()
{
    renderer_.initialize();
}

void ScopeEngine::shutdown()
{
    renderer_.destroy();
}

void ScopeEngine::advance(SignalSource& source, float dt)
{
    source.advance(signal_, dt);
}

void ScopeEngine::render(SignalSource& source, float dt, int width, int height)
{
    advance(source, dt);
    renderCurrentSignal(width, height);
}

void ScopeEngine::renderCurrentSignal(int width, int height)
{
    renderer_.render(signal_, params_, width, height);
}

void ScopeEngine::setSampleCount(int sampleCount)
{
    signal_.resize(sampleCount);
}

int ScopeEngine::sampleCount() const
{
    return signal_.size();
}

VisualParams& ScopeEngine::params()
{
    return params_;
}

const VisualParams& ScopeEngine::params() const
{
    return params_;
}

void ScopeEngine::setParams(const VisualParams& params)
{
    const int clearRevision = params_.clearRevision;
    params_ = params;
    params_.clearRevision = clearRevision;
    clampVisualParams(params_);
}

void ScopeEngine::requestClear()
{
    ++params_.clearRevision;
}

SignalBuffer& ScopeEngine::signal()
{
    return signal_;
}

const SignalBuffer& ScopeEngine::signal() const
{
    return signal_;
}
}
