#pragma once

#include <chrono>
#include <thread>
using namespace std::literals::chrono_literals;

#include "VPlane.h"
#include "game.h"

class Enemy;

class Door {
    glm::vec3 pos;
    Cube *door_shape;
    Vertical_plane *plane1;
    Vertical_plane *plane2;
    ProgramShader *ps_door;
    ProgramShader *ps_plane;
    Map *cols;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    int tex_num = 99;
    int *doorArr = new int[1] {tex_num};
    
    enum DOOR_STATES { DOOR_OPENS, DOOR_CLOSES, DOOR_IS_STANDING };
public:
    DOOR_STATES states;
    float *coordinate;
    Door(const  float &xGap, const float &zGap, float rotation, Collisions& col, Texture &tex);
    
    void clear();
    void processing(const glm::mat4 &view, const glm::mat4 &proj, GLFWwindow* window, const glm::vec3 &player_position, std::vector<Enemy> *enemies);
    void update(GLFWwindow *window, const glm::vec3 &player_position, std::vector<Enemy> *enemies);
    void door_cheking(const glm::vec3 &position, const float &rotation);
    void draw(const glm::mat4 &view, const glm::mat4 &proj);
};