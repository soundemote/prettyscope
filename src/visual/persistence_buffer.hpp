#pragma once

#include "visual/screen_quad.hpp"
#include "visual/visual_params.hpp"

namespace prettyscope
{
class PersistenceBuffer
{
public:
    PersistenceBuffer() = default;
    ~PersistenceBuffer();

    PersistenceBuffer(const PersistenceBuffer&) = delete;
    PersistenceBuffer& operator=(const PersistenceBuffer&) = delete;

    void initialize(ScreenQuad* screenQuad);
    void beginPersistentFrame(const VisualParams& params, int width, int height);
    void endPersistentFrame(int width, int height);
    void beginImmediateFrame(const VisualParams& params, int width, int height);
    void destroy();

private:
    void ensureTargets(int width, int height);
    void createTarget(int index, int width, int height);
    void clearTargets(const VisualParams& params, int width, int height);
    void decay(const VisualParams& params, int width, int height);
    void present(unsigned int texture);

    ScreenQuad* screenQuad_ = nullptr;
    unsigned int screenProgram_ = 0;
    unsigned int decayProgram_ = 0;
    unsigned int framebuffers_[2] = {};
    unsigned int textures_[2] = {};
    int width_ = 0;
    int height_ = 0;
    int activeTarget_ = 0;
    int lastClearRevision_ = -1;
};
}
