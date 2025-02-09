#pragma once
#include <stack>
#include "libs.h"
#include "settings.h"
#include <stack>

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
    
    std::chrono::duration<float> old_duration_gun = std::chrono::high_resolution_clock::now() - std::chrono::high_resolution_clock::now();

    void update(Player &p,
                GLFWwindow *window);
    void draw(std::chrono::duration<float> duration,
              Player &p,
              GLFWwindow *window);
public:
    Gun();
    void processing(std::chrono::duration<float> duration,
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

#define RIGHT_TURN 90
#define FULL_TURN  180

struct Enemy : public Entity {
    glm::vec3 position_check = glm::vec3(1.0f);
    float danage = 0;
private:
    int tex_x  = 0;
    int tex_y  = 0;
    uint turn;
    GLFWwindow *window;
    std::vector<Point2> way;
    
    int maneuvering = 1;
    
    enum ATTACK_STATES {MANEUVERING, RUN, SHOOT};
    glm::vec3 flag_of_maneuvering = position;
    
    std::chrono::duration<float> old_duration_enemy = std::chrono::high_resolution_clock::now() - std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> old_duration_atack = std::chrono::high_resolution_clock::now() - std::chrono::high_resolution_clock::now();
    
    ProgramShader  *ps;
    Texture *enemy_tex;
    
    int vision(Collisions &colls, const glm::vec3 &player_position);
    
    int search_player_rec(const Map &map, 
                                int *main_map, 
                                std::vector<Point2> &solution, 
                                std::vector<Point2> &main_array, 
                          const Point2 &p_p, 
                                int depth, 
                                int &min_depth);
    
    float angle_btw_point_and_enemy(const glm::vec3 &point);
    void draw(std::chrono::duration<float> duration, const Player &player, glm::mat4 &view, glm::mat4 &proj);
    void update(Collisions &colls, std::chrono::duration<float> duration, const std::vector<Door*> &doors, const Entity &player);
public:
    enum states {DUTY, SEARCH, ATTACK};
    states state;
    ATTACK_STATES a_states = RUN;
    
    Enemy(GLFWwindow *window, glm::vec3 position, float rotation, int hit_points, String name_of_file, uint turn);
    
    void processing(Collisions &colls, std::chrono::duration<float> duration, const Player &player, glm::mat4 &view, glm::mat4 &proj, const std::vector<Door*> &doors);
    int search_player(const Map &map, const glm::vec3 &player_position);
    void clear();
};