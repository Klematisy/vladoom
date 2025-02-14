#pragma once

#include "image.h"
#include "programShader.h"
#include "texture.h"
#include "game.h"

class Player;

class Hud {
    Image *img;

    ProgramShader *hud_shader;
    ProgramShader *face_shader;
    ProgramShader *nums_shader;
    ProgramShader *guns_shader;

    Texture *hud_texture;
    Texture *nums_texture;
    Texture *face_texture;
    Texture *guns_texture;
public:
    Hud(); 
    void draw(const Player &player, int k);
    ~Hud();
};