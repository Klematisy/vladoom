#pragma once

#include <GL/glew.h>

typedef unsigned int uint;

class ProgramShader {
    uint createShader(const char* src, const uint type);
    uint createProgram(const char* vertexShaderSrc, const char* fragmentShaderSrc);
public:
    uint shaderProgram;
    ProgramShader(const char* vs, const char* fs);
    ProgramShader();
    void useProgram();
    void deleteShader();
    uint getShaderProgram();
};