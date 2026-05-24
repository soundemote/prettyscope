#include "visual/scope_renderer.hpp"

#include <glad/glad.h>

namespace prettyscope
{
void ScopeRenderer::initialize()
{
    screenQuad_.initialize();
    beamRenderer_.initialize();
    persistenceBuffer_.initialize(&screenQuad_);
    overlayRenderer_.initialize();

    glEnable(GL_BLEND);
}

void ScopeRenderer::render(const SignalBuffer& signal, const VisualParams& params, int width, int height)
{
    if (width < 1 || height < 1)
    {
        return;
    }

    const int vertexCount = beamRenderer_.uploadSegments(signal, params, width, height);

    if (params.persistenceEnabled)
    {
        persistenceBuffer_.beginPersistentFrame(params, width, height);
        drawTrace(vertexCount, params, width, height);
        persistenceBuffer_.endPersistentFrame(width, height);
    }
    else
    {
        persistenceBuffer_.beginImmediateFrame(params, width, height);
        drawTrace(vertexCount, params, width, height);
    }

    overlayRenderer_.drawGrid(params, width, height);
    overlayRenderer_.drawFps(params, width, height);
}

void ScopeRenderer::drawTrace(int vertexCount, const VisualParams& params, int width, int height)
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    beamRenderer_.draw(vertexCount, params.glowColor, params.glowWidth, params.glowStrength, width, height);
    beamRenderer_.draw(vertexCount, params.traceColor, params.traceWidth, 1.15f, width, height);
}
}
