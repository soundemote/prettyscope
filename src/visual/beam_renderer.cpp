#include "visual/beam_renderer.hpp"

#include "visual/gl_utils.hpp"
#include "visual/shaders.hpp"

#include <glad/glad.h>

#include <algorithm>
#include <cstddef>
#include <stdexcept>

namespace prettyscope
{
namespace
{
unsigned int createBeamProgram()
{
    const unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, shaders::kBeamVertex);
    const unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, shaders::kBeamFragment);
    const unsigned int program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glBindAttribLocation(program, 0, "segmentStart");
    glBindAttribLocation(program, 1, "segmentEnd");
    glBindAttribLocation(program, 2, "cornerIndex");
    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    int success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        char log[1024] = {};
        glGetProgramInfoLog(program, sizeof(log), nullptr, log);
        glDeleteProgram(program);
        throw std::runtime_error(std::string("OpenGL shader link failed: ") + log);
    }

    return program;
}

void setColorUniform(unsigned int program, const RgbColor& color)
{
    glUniform3f(glGetUniformLocation(program, "beamColor"), color.r, color.g, color.b);
}
}

BeamRenderer::~BeamRenderer()
{
    destroy();
}

void BeamRenderer::initialize()
{
    program_ = createBeamProgram();

    glGenVertexArrays(1, &vertexArray_);
    glBindVertexArray(vertexArray_);

    glGenBuffers(1, &vertexBuffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(BeamVertex), reinterpret_cast<void*>(offsetof(BeamVertex, startX)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(BeamVertex), reinterpret_cast<void*>(offsetof(BeamVertex, endX)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(BeamVertex), reinterpret_cast<void*>(offsetof(BeamVertex, corner)));

    glBindVertexArray(0);
}

int BeamRenderer::uploadSegments(const SignalBuffer& signal, const VisualParams& params, int width, int height)
{
    ensureVertexCapacity(signal.size() - 1);

    int vertexIndex = 0;
    constexpr float corners[6] = {0.0f, 1.0f, 2.0f, 2.0f, 1.0f, 3.0f};

    for (int i = 0; i < signal.size() - 1; ++i)
    {
        const ScopePoint start = mapSample(signal, params, i, width, height);
        const ScopePoint end = mapSample(signal, params, i + 1, width, height);

        for (float corner : corners)
        {
            vertices_[static_cast<size_t>(vertexIndex++)] = {start.x, start.y, end.x, end.y, corner};
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
    glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<size_t>(vertexIndex) * sizeof(BeamVertex), vertices_.data());
    return vertexIndex;
}

void BeamRenderer::draw(int vertexCount, const RgbColor& color, float size, float intensity, int width, int height)
{
    glUseProgram(program_);
    glBindVertexArray(vertexArray_);
    setColorUniform(program_, color);
    glUniform1f(glGetUniformLocation(program_, "beamSize"), size);
    glUniform1f(glGetUniformLocation(program_, "beamIntensity"), intensity);
    glUniform2f(glGetUniformLocation(program_, "viewportSize"), static_cast<float>(width), static_cast<float>(height));
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
    glUseProgram(0);
}

void BeamRenderer::ensureVertexCapacity(int segmentCount)
{
    const int requiredVertexCount = segmentCount * 6;
    if (requiredVertexCount <= vertexCapacity_)
    {
        return;
    }

    vertexCapacity_ = requiredVertexCount;
    vertices_.resize(static_cast<size_t>(requiredVertexCount));
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(BeamVertex), nullptr, GL_DYNAMIC_DRAW);
}

BeamRenderer::ScopePoint BeamRenderer::mapSample(const SignalBuffer& signal, const VisualParams& params, int index, int width, int height) const
{
    if (params.traceMode == TraceMode::Xy)
    {
        const float aspect = width > height
            ? static_cast<float>(height) / static_cast<float>(width)
            : 1.0f;
        const float verticalAspect = height > width
            ? static_cast<float>(width) / static_cast<float>(height)
            : 1.0f;

        return {
            signal[index] * params.traceGain * 0.82f * aspect,
            signal.right(index) * params.traceGain * 0.82f * verticalAspect};
    }

    return {
        static_cast<float>(index) / static_cast<float>(signal.size() - 1) * 1.84f - 0.92f,
        signal[index] * params.traceGain};
}

void BeamRenderer::destroy()
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
