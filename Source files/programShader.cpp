#include <programShader.h>
#include <iostream>

ProgramShader::ProgramShader(const char* vs, const char* fs) {
    shaderProgram = createProgram(vs, fs);
}

uint ProgramShader::createShader(const char* src, const uint type) {
    uint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    /*
        Errors handler
    */
    int result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(shader, length, &length, message);
        std::cout << "Failed to compile shader!" << std::endl;
        std::cout << message << std::endl;
        return 0;
    }

    return shader;
}

uint ProgramShader::createProgram(const char* vertexShaderSrc, const char* fragmentShaderSrc) {
    uint vs = createShader(vertexShaderSrc, GL_VERTEX_SHADER);
    std::cout << "fkljds\n";
    uint fs = createShader(fragmentShaderSrc, GL_FRAGMENT_SHADER);

    uint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vs);
    glAttachShader(shaderProgram, fs);
    glLinkProgram(shaderProgram);

    glDeleteShader(vs);
    glDeleteShader(fs);
    
    return shaderProgram;
}

uint ProgramShader::getShaderProgram() {
    return shaderProgram;
}

void ProgramShader::useProgram() {
    glUseProgram(shaderProgram);
}

ProgramShader::~ProgramShader() {
    glDeleteProgram(shaderProgram);
}