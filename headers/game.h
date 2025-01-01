#pragma once
#include "libs.h"
#include "settings.h"

struct Player;

struct Gun {
    uint typeOfgun;

    Texture *gun_tex;
    ProgramShader *gun_ps;

    /*
        1 - knife
        2 - pistol
        3 - rifle
        4 - minigun
    */
private:
    void update(std::chrono::duration<float> &old_duration_gun, 
                std::chrono::duration<float> duration, 
                Player &p, 
                GLFWwindow *window);
    void draw(Player &p);
public:
    Gun();
    void processing(std::chrono::duration<float> &old_duration_gun, 
                    std::chrono::duration<float> duration, 
                    Player &p,
                    GLFWwindow* window);
    ~Gun();
};

struct Player {
    glm::vec3 position;
    float rotation;
    uint typeOfGun;
    int hitPoints = 100;
    int ammo = 100;
    int score = 0;
    uint lives = 4;
};

struct Enemy {
    glm::vec3 position;
    float rotation = 0.0f;
    uint typeOfGun;
    int hitPoints = 100;
private:
    Vertical_plane *enemy_shape;
    ProgramShader *ps;
    Texture *enemy_tex;
public:
    Enemy(glm::vec3 position);
    void draw(const Player &player, glm::mat4 &view, glm::mat4 &proj);
    ~Enemy();
};