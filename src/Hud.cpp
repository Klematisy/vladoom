#include "game.h"
#include "hud.h"

const static String shaderDir = "resource/Shaders/";
String bindShader(std::string dir);

Hud::Hud() {
    String vertexShaderSrc   = bindShader(shaderDir + "map1/map.vert");
    String fragmentShaderSrc = bindShader(shaderDir + "map1/map.frag");

    hud_shader  = new ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    nums_shader = new ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    face_shader = new ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    guns_shader = new ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());

    hud_texture = new Texture("resource/images/hud.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    hud_texture->unbind();
    hud_texture->uniform("tex0", *hud_shader, 0);

    face_texture = new Texture("resource/images/faces.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    face_texture->unbind();
    face_texture->uniform("tex0", *face_shader, 0);

    nums_texture = new Texture("resource/images/nums.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    nums_texture->unbind();
    nums_texture->uniform("tex0", *nums_shader, 0);
    
    guns_texture = new Texture("resource/images/hud_guns2.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    guns_texture->unbind();
    guns_texture->uniform("tex0", *guns_shader, 0);

    img = new Image(GL_STATIC_DRAW, 0.0f, 0.0f, 2.0f, 2.0f, 1.0f);
}

void Hud::draw(const Player &player, int k) {
    hud_texture->bind(GL_TEXTURE0);
    hud_shader->useProgram();

    img->draw(nullptr, 1.0f);

    face_texture->bind(GL_TEXTURE0);
    face_shader->useProgram();
    
    int hit_points = player.hit_points;
    float num_of_tex = (int) 6 - (hit_points / (100 / 6));
    float a = (num_of_tex * 3 >= 12) ? 0.5f : 0.0f;
    num_of_tex *= 3;
    
    if (hit_points == 0.0f) {
        num_of_tex = 22;
    }
    
    if (num_of_tex < 19)
        num_of_tex += k;

    Rect r = {
        (num_of_tex) / 12.0f,
        0.5f - a,
        (num_of_tex + 1) / 12.0f,
        1.0f - a
    };

    Image::draw_once(0.83f, 0.12f, 0.19f, 1.75f, &r, 1.0f);

    nums_texture->bind(GL_TEXTURE0);
    nums_shader->useProgram();

    int score_copy = player.score;
    int health_copy = hit_points;
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
    
    guns_texture->bind(GL_TEXTURE0);
    guns_shader->useProgram();
    int l = player.typeOfGun - 1;
    
    Rect r2 = { (l + 0.0f) / 4,
                0.0f,
                ((l + 1) + 0.0f) / 4,
                1.0f 
    };

    Image::draw_once(1.61f, 0.4f, 0.5f * 0.7f, 1.7f * 0.7f, &r2,  1.0f);
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
