#include "visual/screen_quad.hpp"

#include <glad/glad.h>

namespace prettyscope
{
ScreenQuad::~ScreenQuad()
{
    destroy();
}

void ScreenQuad::initialize()
{
    constexpr float screenVertices[] = {
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
    };

    glGenVertexArrays(1, &vertexArray_);
    glBindVertexArray(vertexArray_);

    glGenBuffers(1, &vertexBuffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(screenVertices), screenVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, reinterpret_cast<void*>(sizeof(float) * 2));

    glBindVertexArray(0);
}

void ScreenQuad::bind() const
{
    glBindVertexArray(vertexArray_);
}

void ScreenQuad::draw() const
{
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void ScreenQuad::destroy()
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
}
}
