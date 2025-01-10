
#include "libs.h"
#include "settings.h"

String bindShader(std::string dir);
const static String shaderDir = "resource/Shaders/";
// static auto start = std::chrono::high_resolution_clock::now();
// static std::chrono::time_point<std::chrono::high_resolution_clock>

Door::Door(int *map, const float &xGap, const float &zGap, float rotation, Collisions &col, Texture &tex) {
    String vertexShaderSrc   = bindShader(shaderDir + "map/map.vert");
    String fragmentShaderSrc = bindShader(shaderDir + "map/map.frag");
    ps_door  = new ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    ps_plane = new ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    
    states = DOOR_IS_STANDING;
    start = std::chrono::high_resolution_clock::now();
    
    pos = glm::vec3(0.0f);

    tex.uniform("tex0", *ps_door, 0);

    door_shape = new Cube(map, 1, 1, 0.04f, -xGap + 0.48f, -zGap, rotation, col);

    plane1 = new Vertical_plane(xGap, zGap -        0.001f, rotation, xGap - 0.5f, zGap - 0.5f, 9, 0.0f, 10.0f, 1.0f);
    plane2 = new Vertical_plane(xGap, zGap - 1.0f + 0.001f, rotation, xGap - 0.5f, zGap - 0.5f, 9, 0.0f, 10.0f, 1.0f);

    coordinate = (rotation != 90.0f) ? &pos.z : &pos.x;
    cols = col._piecesOfMap[col._piecesOfMap.size() - 1];
}

void Door::draw(glm::vec3 &position, glm::mat4 &view, glm::mat4 &proj, GLFWwindow* window, float rotation) {

    float xf = position.x + cosf(glm::radians(rotation + 90));
    float zf = position.z + sinf(glm::radians(rotation + 90));

    int x = (xf) + cols->gapX;
    int z = (zf) + cols->gapZ;

    x = abs(x);
    z = abs(z);
    
    std::chrono::duration<float> duration  = std::chrono::high_resolution_clock::now() - start;
    
    if (duration.count() >= 5.0f && states == DOOR_IS_STANDING && *coordinate <= -1.0f) {
        states = DOOR_CLOSES;
        start = std::chrono::high_resolution_clock::now();
    }
    
    if (inObj(*cols, glm::vec3(xf, 0.0f, zf))) {
        if (cols->obj[x + z * cols->width] == 6 && glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            states = DOOR_OPENS;
        }
    }
    
    if (*coordinate < 0.0f && states == DOOR_CLOSES) {
        *coordinate += 0.01f;
    } else if (*coordinate > -0.001f && cols->obj[0] == 0 && states == DOOR_CLOSES) {
        cols->obj[0] = 6;
        states = DOOR_IS_STANDING;
    }
    
    if (-1.01f < *coordinate && states == DOOR_OPENS) {
        *coordinate -= 0.01f;
    } else if (*coordinate <= -1.0f && cols->obj[0] != 0 && states == DOOR_OPENS) {
        cols->obj[0] = 0;
        states = DOOR_IS_STANDING;
    }
    
    // if (inObj(*cols, glm::vec3(xf, 0.0f, zf))) {
    //     if (cols->obj[x + z * cols->width] == 6 && glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
    //         *coordinate -= 0.001f;
    //     }
    // }
    // if (-1.01f < *coordinate && *coordinate < 0.0f) {
    //     *coordinate -= 0.01f;
    // } else if (*coordinate < -1.0f && cols->obj[0] != 0) {
    //     cols->obj[0] = 0;
    // }

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

Door::~Door() {
    plane1->deletePlane();
    plane2->deletePlane();
    ps_door->deleteShader();
    ps_plane->deleteShader();

    delete door_shape;
    delete plane1;
    delete plane2;
    delete ps_door;
    delete ps_plane;
}
