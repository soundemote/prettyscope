#pragma once

#include "visual/signal_buffer.hpp"
#include "visual/visual_params.hpp"

#include <vector>

namespace prettyscope
{
class BeamRenderer
{
public:
    BeamRenderer() = default;
    ~BeamRenderer();

    BeamRenderer(const BeamRenderer&) = delete;
    BeamRenderer& operator=(const BeamRenderer&) = delete;

    void initialize();
    int uploadSegments(const SignalBuffer& signal, const VisualParams& params, int width, int height);
    void draw(int vertexCount, const RgbColor& color, float size, float intensity, int width, int height);
    void destroy();

private:
    struct BeamVertex
    {
        float startX = 0.0f;
        float startY = 0.0f;
        float endX = 0.0f;
        float endY = 0.0f;
        float corner = 0.0f;
    };

    struct ScopePoint
    {
        float x = 0.0f;
        float y = 0.0f;
    };

    void ensureVertexCapacity(int segmentCount);
    ScopePoint mapSample(const SignalBuffer& signal, const VisualParams& params, int index, int width, int height) const;

    unsigned int program_ = 0;
    unsigned int vertexArray_ = 0;
    unsigned int vertexBuffer_ = 0;
    int vertexCapacity_ = 0;
    std::vector<BeamVertex> vertices_;
};
}
