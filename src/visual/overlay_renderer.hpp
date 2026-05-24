#pragma once

#include "visual/visual_params.hpp"

#include <vector>

namespace prettyscope
{
class OverlayRenderer
{
public:
    OverlayRenderer() = default;
    ~OverlayRenderer();

    OverlayRenderer(const OverlayRenderer&) = delete;
    OverlayRenderer& operator=(const OverlayRenderer&) = delete;

    void initialize();
    void drawGrid(const VisualParams& params, int width, int height);
    void drawFps(const VisualParams& params, int width, int height);
    void destroy();

private:
    void drawOverlayVertices(float r, float g, float b, float a);
    void appendGlyph(char glyph, float x, float y, float scale, int width, int height);
    void appendSegmentRect(int segment, float x, float y, float scale, int width, int height);
    void appendRect(float x, float y, float w, float h, int width, int height);

    unsigned int program_ = 0;
    unsigned int vertexArray_ = 0;
    unsigned int vertexBuffer_ = 0;
    std::vector<float> vertices_;
};
}
