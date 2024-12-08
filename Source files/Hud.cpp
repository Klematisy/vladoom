#include "game.h"
#include "hud.h"

const static String shaderDir = "Resource files/Shaders/";
String bindShader(std::string dir);

Hud::Hud() {
    String vertexShaderSrc   = bindShader(shaderDir + "map1/map.vert");
    String fragmentShaderSrc = bindShader(shaderDir + "map1/map.frag");

    hud_shader  = new ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    nums_shader = new ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    face_shader = new ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());

    hud_texture = new Texture("Resource files/images/hud.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    hud_texture->unbind();
    hud_texture->uniform("tex0", *hud_shader, 0);

    face_texture = new Texture("Resource files/images/faces.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    face_texture->unbind();
    face_texture->uniform("tex0", *face_shader, 0);

    nums_texture = new Texture("Resource files/images/nums.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    nums_texture->unbind();
    nums_texture->uniform("tex0", *nums_shader, 0);

    img = new Image(GL_STATIC_DRAW, 0.0f, 0.0f, 2.0f, 2.0f);
}

void Hud::draw(Player &player, int k) {
    hud_texture->bind(GL_TEXTURE0);
    hud_shader->useProgram();

    img->draw(nullptr);

    if (player.hitPoints <= 0) {
        player.hitPoints = 100.0f;
    }

    face_texture->bind(GL_TEXTURE0);
    face_shader->useProgram();
    float num_of_tex = (int) ((100 - player.hitPoints) / 14);

    float a = (num_of_tex * 3 >= 12) ? 0.5f : 0.0f;
    num_of_tex *= 3;
    if (num_of_tex <= 21)
        num_of_tex += k;

    Rect r = {
        (num_of_tex) / 12.0f,
        0.5f - a,
        (num_of_tex + 1) / 12.0f,
        1.0f - a
    };

    Image::draw_once(0.83f, 0.12f, 0.19f, 1.75f, &r);

    nums_texture->bind(GL_TEXTURE0);
    nums_shader->useProgram();

    int score_copy = player.score;
    int health_copy = player.hitPoints;
    int ammo_copy = player.ammo;

    Symbol::draw(0.1f, 0.45f, 1);

    Symbol::draw(0.30f, 0.45f, score_copy / 10000);
    score_copy %= 10000;
    Symbol::draw(0.35f, 0.45f, score_copy / 1000);
    score_copy %= 1000;
    Symbol::draw(0.40f, 0.45f, score_copy / 100);
    score_copy %= 100;
    Symbol::draw(0.45f, 0.45f, score_copy / 10);
    score_copy %= 10;
    Symbol::draw(0.50f, 0.45f, score_copy / 1);

    Symbol::draw(0.69f, 0.45f, player.lives);

    if (health_copy == 100) {
        Symbol::draw(1.060f, 0.45f, health_copy / 100);
        health_copy %= 100;
    }
    Symbol::draw(1.110f, 0.45f, health_copy / 10);
    health_copy %= 10;
    Symbol::draw(1.160f, 0.45f, health_copy / 1);

    Symbol::draw(1.37f, 0.45f, ammo_copy / 10);
    ammo_copy %= 10;
    Symbol::draw(1.42f, 0.45f, ammo_copy);
}

Hud::~Hud() {
    img->clear();
    delete img;

    hud_shader->deleteShader();
    nums_shader->deleteShader();

    delete hud_shader;
    delete nums_shader;

    delete hud_texture;
    delete nums_texture;
}