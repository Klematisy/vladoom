#pragma once

#include <stb/stb_image.h>
#include <GL/glew.h>
#include <programShader.h>

typedef unsigned int uint;
typedef unsigned char uchar;

class Texture {
    int widthImg, heightImg, numColCh;
    uchar* bytes;
    uint texture;
public:
    Texture(const char* fileName, GLenum colorType, GLenum pixelData, GLenum tex);
    void uniform(const char* name, ProgramShader& p, uint uInt);
    void bind(GLenum type);
    void unbind();
    void deleteTex();
    ~Texture();
};