#include "game.h"

const static String shaderDir = "Resource files/Shaders/";
String bindShader(std::string dir);

Gun::Gun() {
    String vertexShaderSrc   = bindShader(shaderDir + "map1/map.vert");
    String fragmentShaderSrc = bindShader(shaderDir + "map1/map.frag");

    gun_ps  = new ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    gun_tex = new Texture("Resource files/images/guns1.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
}

void Gun::draw(int num_of_animation, int typeOfgun) {
    gun_tex->bind(GL_TEXTURE0);
    gun_ps->useProgram();
    Rect r = { num_of_animation / 5.0f,
              (4.0f - typeOfgun) / 4,
              (num_of_animation + 1) / 5.0f,
              (4.0f - typeOfgun + 1.0f) / 4};

    Image::draw_once(0.475f, 0.0f, 1.0f, 1.5f, &r);
}

Gun::~Gun() {
    delete gun_tex;
    delete gun_ps;
}
