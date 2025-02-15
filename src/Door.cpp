
#include "libs.h"
#include "settings.h"

String bindShader(std::string dir);
const static String shaderDir = "resource/Shaders/";

Door::Door(const float &xGap, const float &zGap, float rotation, Collisions &col, Texture &tex, int tod) {
    String vertexShaderSrc   = bindShader(shaderDir + "map/map.vert");
    String fragmentShaderSrc = bindShader(shaderDir + "map/map.frag");
    ps_door  = new ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    ps_plane = new ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    
    tex_num = tod;
    doorArr[0] = tod;
    
    states = DOOR_IS_STANDING;
    start = std::chrono::high_resolution_clock::now();
    
    pos = glm::vec3(0.0f);

    tex.uniform("tex0", *ps_door, 0);

    door_shape = new Cube(doorArr, 1, 1, 0.04f, xGap - 0.48f, zGap, rotation, col, 6.0f, 19.0f);

    plane1 = new Vertical_plane(xGap, zGap -        0.001f, rotation, xGap - 0.5f, zGap - 0.5f, 101, 6.0f, 19.0f);
    plane2 = new Vertical_plane(xGap, zGap - 1.0f + 0.001f, rotation, xGap - 0.5f, zGap - 0.5f, 101, 6.0f, 19.0f);

    coordinate = (rotation != 90.0f) ? &pos.z : &pos.x;
    cols = col._piecesOfMap.back();
}

void Door::door_cheking(const glm::vec3 &position, const float &rotation) {
    float xf = position.x + cosf(glm::radians(rotation + 90));
    float zf = position.z + sinf(glm::radians(rotation + 90));

    int x = (xf) + cols->gap_x;
    int z = (zf) + cols->gap_z;

    x = abs(x);
    z = abs(z);
    
    if (inObj(*cols, glm::vec3(xf, 0.0f, zf))) {
        if (cols->obj[0] == tex_num) {
            states = DOOR_OPENS;
            start = std::chrono::high_resolution_clock::now();
        }
    }
}

void Door::update(const glm::vec3 &player_position, std::vector<Enemy> *enemies) {
    std::chrono::duration<float> duration  = std::chrono::high_resolution_clock::now() - start;
    
    if (duration.count() >= 4.0f && states == DOOR_IS_STANDING && *coordinate <= -1.0f) {
        states = DOOR_CLOSES;
        if (inObj(*cols, player_position)) {
            states = DOOR_IS_STANDING;
        } else {
            for (Enemy &enemy : *enemies) {
                if (inObj(*cols, enemy.position)) {
                    states = DOOR_IS_STANDING;
                    break;
                }
            }
        }
        start = std::chrono::high_resolution_clock::now();
    }
    
    if (*coordinate < 0.0f && states == DOOR_CLOSES) {
        *coordinate += 0.01f;
        cols->obj[0] = tex_num;
    } else if (*coordinate > -0.001f && cols->obj[0] == 0 && states == DOOR_CLOSES) {
        states = DOOR_IS_STANDING;
    }
    
    if (-1.01f < *coordinate && states == DOOR_OPENS) {
        *coordinate -= 0.01f;
    } else if (*coordinate <= -1.0f && cols->obj[0] != 0 && states == DOOR_OPENS) {
        cols->obj[0] = 0;
        states = DOOR_IS_STANDING;
    }
}

void Door::processing(const glm::mat4 &view, const glm::mat4 &proj, const glm::vec3 &player_position, std::vector<Enemy> *enemies) {
    update(player_position, enemies);
    draw(view, proj);
}

void Door::draw(const glm::mat4 &view, const glm::mat4 &proj) {
    glm::mat4 model = glm::mat4(1.0f);
    model *= glm::translate(model, pos);

    ps_door->useProgram();
    glUniformMatrix4fv(glGetUniformLocation(ps_door->shaderProgram,  "view"),  1, GL_FALSE,  glm::value_ptr(view) );
    glUniformMatrix4fv(glGetUniformLocation(ps_door->shaderProgram,  "proj"),  1, GL_FALSE,  glm::value_ptr(proj) );
    glUniformMatrix4fv(glGetUniformLocation(ps_door->shaderProgram, "model"),  1, GL_FALSE,  glm::value_ptr(model));

    door_shape->draw();

    ps_plane->useProgram();
    model = glm::mat4(1.0f);

    glUniformMatrix4fv(glGetUniformLocation(ps_plane->shaderProgram,  "view"),  1, GL_FALSE,  glm::value_ptr(view) );
    glUniformMatrix4fv(glGetUniformLocation(ps_plane->shaderProgram,  "proj"),  1, GL_FALSE,  glm::value_ptr(proj) );
    glUniformMatrix4fv(glGetUniformLocation(ps_plane->shaderProgram, "model"),  1, GL_FALSE,  glm::value_ptr(model));

    plane1->draw();
    plane2->draw();
}

void Door::clear() {
    plane1->deletePlane();
    plane2->deletePlane();
    ps_door->deleteShader();
    ps_plane->deleteShader();

    delete doorArr;
    delete door_shape;
    delete plane1;
    delete plane2;
    delete ps_door;
    delete ps_plane;
}
