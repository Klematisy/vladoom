#pragma once
#include "libs.h"
#include "settings.h"

struct Player;

struct Gun {
    int num_of_animation = 0;
    /*
        1 - knife
        2 - pistol
        3 - rifle
        4 - minigun
    */
private:
    Texture *gun_tex;
    ProgramShader *gun_ps;

    void update(Player &p,
                GLFWwindow *window);
    void draw(std::chrono::duration<float> &old_duration_gun,
              std::chrono::duration<float> duration,
              Player &p,
              GLFWwindow *window);
public:
    Gun();
    void processing(std::chrono::duration<float> &old_duration_gun,
                    std::chrono::duration<float> duration,
                    Player &p,
                    GLFWwindow* window);
    ~Gun();
};

struct Player : public Entity {
    Gun gun;
    uint typeOfGun = 1;
    int ammo = 100;
    int score = 0;
    uint lives = 4;
};

struct Item : Entity {
    
};

struct Enemy : public Entity {
    glm::vec3 position_check = glm::vec3(1.0f);
    float danage = 0;
private:
    int tex_x  = 0;
    int tex_x2 = 0;
    int tex_y  = 0;
    
    std::chrono::duration<float> old_duration_enemy = std::chrono::high_resolution_clock::now() - std::chrono::high_resolution_clock::now();
    
    Vertical_plane *enemy_shape;
    ProgramShader *ps;
    Texture *enemy_tex;
    
    void draw(std::chrono::duration<float> duration, const Player &player, glm::mat4 &view, glm::mat4 &proj);
    void update(const Collisions &colls, const std::vector<Door*> &doors);
public:
    Enemy(glm::vec3 position, float rotation, int hit_points, String name_of_file);
    void processing(const Collisions &colls, std::chrono::duration<float> duration, const Player &player, glm::mat4 &view, glm::mat4 &proj, const std::vector<Door*> &doors);
    void clear();
};