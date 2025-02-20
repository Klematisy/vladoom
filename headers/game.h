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
public:
    Gun gun;
    uint typeOfGun = 1;
    int ammo = 100;
    int score = 0;
    uint lives = 4;
    int invetory[4] = {
        1, 2, 0, 0
    };
};

enum TYPE_0F_ITEM {
    HEALTH,
    GUN,
    SCORE,
    KEY
};

class Item : Entity {
    int tex_x;
    int tex_y;
    int tex_num;
    
    float changeble = 100;
    float temp;
    TYPE_0F_ITEM type;
    
    ProgramShader *ps;
    Texture      *tex;
    
    void draw(const Player &player, glm::mat4 &view, glm::mat4 &proj);
    void update(Player &player);
public:
    Item(float xGap, float zGap, int tex_num, float changeble,  Player &player, TYPE_0F_ITEM type);
    void processing(Player &player, glm::mat4 &view, glm::mat4 &proj);
};

enum AVAILABILITY {
    IMAGINARY,
    TANGIBLE
};

struct Furniture : public Entity {
private:
    int num_of_tex;
    int x_count_of_objs, y_count_of_objs;
    int map[1] = {1};
    
    ProgramShader *ps;
    Texture      *tex;
public:
    Furniture(
            float xGap, float zGap, 
            int num_of_tex, 
            float x_count_of_objs, float y_count_of_objs,
            Collisions &col, 
            AVAILABILITY av, TYPE_OF_COLLISION toc,
            Texture *tex);
    void draw(const Player &player, glm::mat4 &view, glm::mat4 &proj);
    void clear();
};

#define RIGHT_TURN 90
#define FULL_TURN  180

struct Enemy : public Entity {
    glm::vec3 position_check = glm::vec3(1.0f);
    float danage = 0;
protected:
    struct Utills_for_maneuvering {
        enum maneuvering_corners { RIGHT, LEFT};
        maneuvering_corners maneuvering;
        
        glm::vec3 pos_for_angle;     //angle_btw_player_enemy
        Line line_for_maneuvering;
        float rotation_for_maneuvering;
        bool line_calculator_turner = true;
        glm::vec3 flag_of_maneuvering = glm::vec3(1.5f, 0.0f, 1.5f);
        glm::vec2 movement = glm::vec2(0.0f, 0.0f);
        glm::vec2 flag_of_run = glm::vec2(0.0f, 0.0f);
        int move_counter = 0;
    };
    
    Utills_for_maneuvering ufm;
    
    int tex_x  = 0;
    int tex_y  = 0;
    uint turn;
    int random_number = 0;
    GLFWwindow *window;
    std::vector<Point2> way;
    
    enum ATTACK_STATES {MANEUVERING, RUN, SHOOT};
    bool death_fact = true;
    float duration_for_shooting = 0.2f;
    bool shot = false;
    
    std::chrono::duration<float> old_duration_enemy = std::chrono::high_resolution_clock::now() - std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> old_duration_atack = std::chrono::high_resolution_clock::now() - std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> old_duration_shoot = std::chrono::high_resolution_clock::now() - std::chrono::high_resolution_clock::now();
    
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
    virtual void update(Collisions &colls, std::chrono::duration<float> duration, const std::vector<Door*> &doors, Entity &player);
    virtual void draw(std::chrono::duration<float> duration, const Player &player, glm::mat4 &view, glm::mat4 &proj);
public:
    enum states {DUTY, SEARCH, ATTACK};
    states state;
    ATTACK_STATES a_states = RUN;
    
    Enemy(glm::vec3 position, float rotation, int hit_points, int danage, String name_of_file, uint turn);
    int search_player(const Map &map, const glm::vec3 &player_position);
    void clear();
    
    virtual void processing(Collisions &colls, std::chrono::duration<float> duration, Player &player, glm::mat4 &view, glm::mat4 &proj, const std::vector<Door*> &doors);
};

struct E_Dog : public Enemy {
    E_Dog(glm::vec3 position, float rotation, int hit_points, int danage, String name_of_file);
    ATTACK_STATES a_states = MANEUVERING;
    
    void update(Collisions &colls, std::chrono::duration<float> duration, const std::vector<Door*> &doors, Entity &player) override;
    void draw(std::chrono::duration<float> duration, const Player &player, glm::mat4 &view, glm::mat4 &proj) override;
    void processing(Collisions &colls, std::chrono::duration<float> duration, Player &player, glm::mat4 &view, glm::mat4 &proj, const std::vector<Door*> &doors) override;
};