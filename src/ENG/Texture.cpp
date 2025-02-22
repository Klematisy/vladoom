#include <Texture.h>
#include <iostream>

Texture::Texture(const char* fileName, GLenum colorType, GLenum pixelData, GLenum tex) {
    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true);
    bytes = stbi_load(fileName, &widthImg, &heightImg, &numColCh, STBI_rgb_alpha);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, colorType, widthImg, heightImg, 0, colorType, pixelData, bytes);
    stbi_image_free(bytes);
}

void Texture::uniform(const char* fragShadName, ProgramShader& p, uint uInt) {
    p.useProgram();
    glUniform1i(glGetUniformLocation(p.getShaderProgram(), fragShadName), uInt);
}

void Texture::bind(GLenum type) {
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
    glDeleteTextures(1, &texture);
}