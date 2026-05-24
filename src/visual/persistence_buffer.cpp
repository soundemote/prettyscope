#include "visual/persistence_buffer.hpp"

#include "visual/gl_utils.hpp"
#include "visual/shaders.hpp"

#include <glad/glad.h>

#include <stdexcept>

namespace prettyscope
{
PersistenceBuffer::~PersistenceBuffer()
{
    destroy();
}

void PersistenceBuffer::initialize(ScreenQuad* screenQuad)
{
    screenQuad_ = screenQuad;
    screenProgram_ = createProgram(shaders::kScreenVertex, shaders::kTextureFragment);
    decayProgram_ = createProgram(shaders::kScreenVertex, shaders::kDecayFragment);
}

void PersistenceBuffer::beginPersistentFrame(const VisualParams& params, int width, int height)
{
    ensureTargets(width, height);

    if (lastClearRevision_ != params.clearRevision)
    {
        clearTargets(params, width, height);
        lastClearRevision_ = params.clearRevision;
    }

    decay(params, width, height);

    glBindFramebuffer(GL_FRAMEBUFFER, framebuffers_[activeTarget_]);
    glViewport(0, 0, width, height);
}

void PersistenceBuffer::endPersistentFrame(int width, int height)
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, width, height);
    present(textures_[activeTarget_]);
}

void PersistenceBuffer::beginImmediateFrame(const VisualParams& params, int width, int height)
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, width, height);
    glClearColor(
        params.backgroundColor.r,
        params.backgroundColor.g,
        params.backgroundColor.b,
        1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void PersistenceBuffer::ensureTargets(int width, int height)
{
    if (framebuffers_[0] != 0 && width_ == width && height_ == height)
    {
        return;
    }

    for (int i = 0; i < 2; ++i)
    {
        if (framebuffers_[i] != 0)
        {
            glDeleteFramebuffers(1, &framebuffers_[i]);
            framebuffers_[i] = 0;
        }

        if (textures_[i] != 0)
        {
            glDeleteTextures(1, &textures_[i]);
            textures_[i] = 0;
        }
    }

    createTarget(0, width, height);
    createTarget(1, width, height);
    width_ = width;
    height_ = height;
    activeTarget_ = 0;

    clearTargets(VisualParams{}, width, height);
    lastClearRevision_ = -1;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PersistenceBuffer::createTarget(int index, int width, int height)
{
    glGenTextures(1, &textures_[index]);
    glBindTexture(GL_TEXTURE_2D, textures_[index]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glGenFramebuffers(1, &framebuffers_[index]);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffers_[index]);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textures_[index], 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        throw std::runtime_error("Could not create persistence framebuffer");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PersistenceBuffer::clearTargets(const VisualParams& params, int width, int height)
{
    for (unsigned int framebuffer : framebuffers_)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glViewport(0, 0, width, height);
        glClearColor(
            params.backgroundColor.r,
            params.backgroundColor.g,
            params.backgroundColor.b,
            1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}

void PersistenceBuffer::decay(const VisualParams& params, int width, int height)
{
    const int source = activeTarget_;
    const int destination = 1 - activeTarget_;

    glBindFramebuffer(GL_FRAMEBUFFER, framebuffers_[destination]);
    glViewport(0, 0, width, height);
    glUseProgram(decayProgram_);
    screenQuad_->bind();
    glDisable(GL_BLEND);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures_[source]);
    glUniform1i(glGetUniformLocation(decayProgram_, "image"), 0);
    glUniform3f(
        glGetUniformLocation(decayProgram_, "backgroundColor"),
        params.backgroundColor.r,
        params.backgroundColor.g,
        params.backgroundColor.b);
    glUniform1f(glGetUniformLocation(decayProgram_, "persistence"), params.persistence);
    glUniform1f(glGetUniformLocation(decayProgram_, "fastDecay"), params.fastDecay);
    glUniform1f(glGetUniformLocation(decayProgram_, "afterglow"), params.afterglow);
    glUniform1i(
        glGetUniformLocation(decayProgram_, "decayStyle"),
        params.decayStyle == DecayStyle::Phosphor ? 1 : 0);
    screenQuad_->draw();
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glEnable(GL_BLEND);
    glUseProgram(0);

    activeTarget_ = destination;
}

void PersistenceBuffer::present(unsigned int texture)
{
    glUseProgram(screenProgram_);
    screenQuad_->bind();
    glDisable(GL_BLEND);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(screenProgram_, "image"), 0);
    screenQuad_->draw();
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glEnable(GL_BLEND);
    glUseProgram(0);
}

void PersistenceBuffer::destroy()
{
    for (int i = 0; i < 2; ++i)
    {
        if (framebuffers_[i] != 0)
        {
            glDeleteFramebuffers(1, &framebuffers_[i]);
            framebuffers_[i] = 0;
        }

        if (textures_[i] != 0)
        {
            glDeleteTextures(1, &textures_[i]);
            textures_[i] = 0;
        }
    }

    if (screenProgram_ != 0)
    {
        glDeleteProgram(screenProgram_);
        screenProgram_ = 0;
    }

    if (decayProgram_ != 0)
    {
        glDeleteProgram(decayProgram_);
        decayProgram_ = 0;
    }
}
}
