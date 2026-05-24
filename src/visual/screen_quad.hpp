#pragma once

namespace prettyscope
{
class ScreenQuad
{
public:
    ScreenQuad() = default;
    ~ScreenQuad();

    ScreenQuad(const ScreenQuad&) = delete;
    ScreenQuad& operator=(const ScreenQuad&) = delete;

    void initialize();
    void bind() const;
    void draw() const;
    void destroy();

private:
    unsigned int vertexArray_ = 0;
    unsigned int vertexBuffer_ = 0;
};
}
