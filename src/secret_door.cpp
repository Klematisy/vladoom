#include "secret_door.h"

String bindShader(std::string dir);
const static String shaderDir = "resource/Shaders/";

S_Door::S_Door(float x_gap, float z_gap, float angle_of_moving, int num_of_tex, Collisions &col) {
    position = glm::vec3(0.0f);
    tex_num = num_of_tex;

    String vertexShaderSrc   = bindShader(shaderDir + "map/map.vert");
    String fragmentShaderSrc = bindShader(shaderDir + "map/map.frag");
    ps  = new ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    
    states = DOOR_IS_STANDING;
    
    doorArr[0] = num_of_tex;
    door_shape = new Cube(doorArr, 1, 1, 1.0f, x_gap, z_gap, 0.0f, col, 6.0f, 19.0f);
    
    angle_of_moving = fmodf(angle_of_moving, 360);
    cols = col._piecesOfMap.back();
    
    switch ((int) angle_of_moving / 90) {
        case 0: {
            znak = -1;
            coordinate = &position.z;
            gap = &cols->gap_z;
            min = &cols->minZ;
            max = &cols->maxZ;
            break;
        }
        case 1: {
            znak =  1;
            coordinate = &position.x;
            gap = &cols->gap_x;
            min = &cols->minX;
            max = &cols->maxX;
            break;
        }
        case 2: {
            znak = 1;
            coordinate = &position.z;
            gap = &cols->gap_z;
            min = &cols->minZ;
            max = &cols->maxZ;
            break;
        }
        case 3: {
            znak = -1;
            coordinate = &position.x;
            gap = &cols->gap_x;
            min = &cols->minX;
            max = &cols->maxX;
            break;
        }
    }
    // *max = -4;
    // *gap = 4;
    // *min = -5;
    // *min = -6;
    // *gap = 5;
    // *max = -5;
    point = *coordinate;
}

void S_Door::door_cheking(const glm::vec3 &position, const float &rotation) {
    float xf = position.x + cosf(glm::radians(rotation + 90));
    float zf = position.z + sinf(glm::radians(rotation + 90));

    int x = (xf) + cols->gap_x;
    int z = (zf) + cols->gap_z;

    x = abs(x);
    z = abs(z);
    
    if (inObj(*cols, glm::vec3(xf, 0.0f, zf))) {
        if (cols->obj[0] == tex_num) {
            states = DOOR_OPENS;
        }
    }
}

void S_Door::update() {
    if (*coordinate * znak > 2.0f && states == DOOR_OPENS) {
        states = DOOR_IS_STANDING;
    }
    
    if (states == DOOR_OPENS) {
        *coordinate += 0.01f * znak;
        if (fabsf(*coordinate - point) >= 0.9999f) {
            point = *coordinate;
            *min -= 1.0f * znak;
            *max -= 1.0f * znak;
            *gap  = -*max;
        }
    }
}

void S_Door::processing(glm::mat4 view, glm::mat4 proj) {
    update();
    draw(view, proj);
}


void S_Door::draw(glm::mat4 view, glm::mat4 proj) {
    glm::mat4 model = glm::mat4(1.0f);
    model *= glm::translate(model, position);
    
    ps->useProgram();
    glUniformMatrix4fv(glGetUniformLocation(ps->shaderProgram,  "view"),  1, GL_FALSE,  glm::value_ptr(view) );
    glUniformMatrix4fv(glGetUniformLocation(ps->shaderProgram,  "proj"),  1, GL_FALSE,  glm::value_ptr(proj) );
    glUniformMatrix4fv(glGetUniformLocation(ps->shaderProgram, "model"),  1, GL_FALSE,  glm::value_ptr(model));
    
    door_shape->draw();
}