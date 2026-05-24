#include "visual/overlay_renderer.hpp"

#include "visual/gl_utils.hpp"
#include "visual/shaders.hpp"

#include <glad/glad.h>

#include <algorithm>
#include <cstdio>
#include <string>

namespace prettyscope
{
OverlayRenderer::~OverlayRenderer()
{
    destroy();
}

void OverlayRenderer::initialize()
{
    program_ = createProgram(shaders::kSolidVertex, shaders::kSolidFragment);

    glGenVertexArrays(1, &vertexArray_);
    glBindVertexArray(vertexArray_);

    glGenBuffers(1, &vertexBuffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 1024, nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);

    glBindVertexArray(0);
}

void OverlayRenderer::drawGrid(const VisualParams& params, int width, int height)
{
    if (!params.showGrid)
    {
        return;
    }

    vertices_.clear();

    const float line = 1.0f;

    if (params.traceMode == TraceMode::Xy)
    {
        constexpr int divisions = 8;
        const float side = static_cast<float>(std::min(width, height));
        const float left = (static_cast<float>(width) - side) * 0.5f;
        const float top = (static_cast<float>(height) - side) * 0.5f;

        for (int i = 0; i <= divisions; ++i)
        {
            const float offset = static_cast<float>(i) / static_cast<float>(divisions) * side;
            const float thickness = i == divisions / 2 ? 2.0f : line;
            appendRect(left + offset - thickness * 0.5f, top, thickness, side, width, height);
            appendRect(left, top + offset - thickness * 0.5f, side, thickness, width, height);
        }
    }
    else
    {
        constexpr int divisionsX = 10;
        constexpr int divisionsY = 8;

        for (int i = 0; i <= divisionsX; ++i)
        {
            const float x = static_cast<float>(i) / static_cast<float>(divisionsX) * static_cast<float>(width);
            const float thickness = i == divisionsX / 2 ? 2.0f : line;
            appendRect(x - thickness * 0.5f, 0.0f, thickness, static_cast<float>(height), width, height);
        }

        for (int i = 0; i <= divisionsY; ++i)
        {
            const float y = static_cast<float>(i) / static_cast<float>(divisionsY) * static_cast<float>(height);
            const float thickness = i == divisionsY / 2 ? 2.0f : line;
            appendRect(0.0f, y - thickness * 0.5f, static_cast<float>(width), thickness, width, height);
        }
    }

    const float alpha = std::max(0.0f, std::min(1.0f, params.gridIntensity));
    drawOverlayVertices(0.45f, 0.95f, 0.72f, alpha);
}

void OverlayRenderer::drawFps(const VisualParams& params, int width, int height)
{
    if (!params.showFps)
    {
        return;
    }

    char text[8] = {};
    const int fps = std::max(0, std::min(999, static_cast<int>(params.fps + 0.5f)));
    std::snprintf(text, sizeof(text), "FPS %03d", fps);

    vertices_.clear();

    const float scale = 1.2f;
    const float glyphWidth = 12.0f * scale;
    const float spacing = 4.0f * scale;
    const int glyphCount = static_cast<int>(std::string(text).size());
    const float totalWidth = static_cast<float>(glyphCount) * glyphWidth + static_cast<float>(glyphCount - 1) * spacing;
    const float y = 16.0f;
    float x = static_cast<float>(width) - totalWidth - 18.0f;

    for (char glyph : std::string(text))
    {
        appendGlyph(glyph, x, y, scale, width, height);
        x += glyphWidth + spacing;
    }

    drawOverlayVertices(0.82f, 1.0f, 0.88f, 0.78f);
}

void OverlayRenderer::drawOverlayVertices(float r, float g, float b, float a)
{
    if (vertices_.empty())
    {
        return;
    }

    glUseProgram(program_);
    glBindVertexArray(vertexArray_);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(float), vertices_.data(), GL_DYNAMIC_DRAW);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUniform4f(glGetUniformLocation(program_, "fillColor"), r, g, b, a);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(vertices_.size() / 2));
    glBindVertexArray(0);
    glUseProgram(0);
}

void OverlayRenderer::appendGlyph(char glyph, float x, float y, float scale, int width, int height)
{
    unsigned char mask = 0;

    switch (glyph)
    {
    case '0': mask = 0b0111111; break;
    case '1': mask = 0b0000110; break;
    case '2': mask = 0b1011011; break;
    case '3': mask = 0b1001111; break;
    case '4': mask = 0b1100110; break;
    case '5': mask = 0b1101101; break;
    case '6': mask = 0b1111101; break;
    case '7': mask = 0b0000111; break;
    case '8': mask = 0b1111111; break;
    case '9': mask = 0b1101111; break;
    case 'F': mask = 0b1110001; break;
    case 'P': mask = 0b1110011; break;
    case 'S': mask = 0b1101101; break;
    default: break;
    }

    for (int segment = 0; segment < 7; ++segment)
    {
        if ((mask & (1 << segment)) != 0)
        {
            appendSegmentRect(segment, x, y, scale, width, height);
        }
    }
}

void OverlayRenderer::appendSegmentRect(int segment, float x, float y, float scale, int width, int height)
{
    const float t = 2.5f * scale;
    const float w = 12.0f * scale;
    const float h = 20.0f * scale;

    switch (segment)
    {
    case 0: appendRect(x + t, y, w - t * 2.0f, t, width, height); break;
    case 1: appendRect(x + w - t, y + t, t, h * 0.5f - t, width, height); break;
    case 2: appendRect(x + w - t, y + h * 0.5f, t, h * 0.5f - t, width, height); break;
    case 3: appendRect(x + t, y + h - t, w - t * 2.0f, t, width, height); break;
    case 4: appendRect(x, y + h * 0.5f, t, h * 0.5f - t, width, height); break;
    case 5: appendRect(x, y + t, t, h * 0.5f - t, width, height); break;
    case 6: appendRect(x + t, y + h * 0.5f - t * 0.5f, w - t * 2.0f, t, width, height); break;
    default: break;
    }
}

void OverlayRenderer::appendRect(float x, float y, float w, float h, int width, int height)
{
    const float x0 = x / static_cast<float>(width) * 2.0f - 1.0f;
    const float x1 = (x + w) / static_cast<float>(width) * 2.0f - 1.0f;
    const float y0 = 1.0f - y / static_cast<float>(height) * 2.0f;
    const float y1 = 1.0f - (y + h) / static_cast<float>(height) * 2.0f;

    const float rect[] = {
        x0, y1,
        x1, y1,
        x0, y0,
        x0, y0,
        x1, y1,
        x1, y0,
    };

    vertices_.insert(vertices_.end(), std::begin(rect), std::end(rect));
}

void OverlayRenderer::destroy()
{
    if (vertexBuffer_ != 0)
    {
        glDeleteBuffers(1, &vertexBuffer_);
        vertexBuffer_ = 0;
    }

    if (vertexArray_ != 0)
    {
        glDeleteVertexArrays(1, &vertexArray_);
        vertexArray_ = 0;
    }

    if (program_ != 0)
    {
        glDeleteProgram(program_);
        program_ = 0;
    }
}
}
