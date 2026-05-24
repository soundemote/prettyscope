#pragma once

#include "visual/beam_renderer.hpp"
#include "visual/overlay_renderer.hpp"
#include "visual/persistence_buffer.hpp"
#include "visual/screen_quad.hpp"
#include "visual/signal_buffer.hpp"
#include "visual/visual_params.hpp"

namespace prettyscope
{
class ScopeRenderer
{
public:
    ScopeRenderer() = default;
    ~ScopeRenderer() = default;

    ScopeRenderer(const ScopeRenderer&) = delete;
    ScopeRenderer& operator=(const ScopeRenderer&) = delete;

    void initialize();
    void render(const SignalBuffer& signal, const VisualParams& params, int width, int height);

private:
    void drawTrace(int vertexCount, const VisualParams& params, int width, int height);

    ScreenQuad screenQuad_;
    BeamRenderer beamRenderer_;
    PersistenceBuffer persistenceBuffer_;
    OverlayRenderer overlayRenderer_;
};
}
