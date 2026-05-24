#pragma once

namespace prettyscope
{
unsigned int compileShader(unsigned int type, const char* source);
unsigned int createProgram(const char* vertexSource, const char* fragmentSource);
}
