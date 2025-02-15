#pragma once

#include "libs.h"
#include "settings.h"
#include "game.h"

class S_Door : public Entity {
    Texture      *tex;
    ProgramShader *ps;
    Cube  *door_shape;
    float *coordinate;
    Map         *cols;
    float        *gap;
    float        *max;
    float        *min;
    int          znak;
    int       tex_num;
    
    int doorArr[1] = {0};
    
    enum DOOR_STATES { DOOR_OPENS, DOOR_IS_STANDING };
    
    void update();
    void draw(glm::mat4 view, glm::mat4 proj);
public:
    DOOR_STATES states;
    
    S_Door(float x_gap, float z_gap, float angle_of_moving, int num_of_tex, Collisions &col);
    void processing(glm::mat4 view, glm::mat4 proj);
    void door_cheking(const glm::vec3 &position, const float &rotation);
    void clear();
};