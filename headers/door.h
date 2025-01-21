#pragma once

#include <chrono>
#include <thread>
using namespace std::literals::chrono_literals;

#include "VPlane.h"

class Door {    
    glm::vec3 pos;
    Cube *door_shape;
    Vertical_plane *plane1;
    Vertical_plane *plane2;
    ProgramShader *ps_door;
    ProgramShader *ps_plane;
    Map *cols;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    int *doorArr = new int[1] {6};
    
    enum DOOR_STATES { DOOR_OPENS, DOOR_CLOSES, DOOR_IS_STANDING };
public:
    DOOR_STATES states;
    float *coordinate;
    Door(const  float &xGap, const float &zGap, float rotation, Collisions& col, Texture &tex);
    ~Door();
    void clear();
    void draw(glm::vec3 &position, glm::mat4 &view, glm::mat4 &proj, GLFWwindow* window, float rotation);
};