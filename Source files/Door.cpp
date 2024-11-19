#include "libs.h"

String bindShader(std::string dir);
const static String shaderDir = "Resource files/Shaders/";

Door::Door(int *map, const float &xGap, const float &zGap, float rotation, Collisions& col, Texture &tex) {
    String vertexShaderSrc   = bindShader(shaderDir + "map/map.vert");
    String fragmentShaderSrc = bindShader(shaderDir + "map/map.frag");
    ps = new ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());

    pos = glm::vec3(0.0f);

    tex.uniform("tex0", *ps, 0);

    cube = new Cube(map, 1, 1, 0.1f, xGap + 0.45f, zGap, rotation, col);
    coordinate = (rotation != 90) ? &pos.z : &pos.x;

    cols = col._piecesOfMap[col._piecesOfMap.size() - 1];
}

static float sin(float rotation) {
    if      (rotation == 0  ) { return  0.0f; }
    else if (rotation == 90 ) { return  1.0f; }
    else if (rotation == 180) { return  0.0f; }
    else if (rotation == 270) { return -1.0f; }
    else if (rotation == 360) { return  0.0f; }
    else { return glm::sin(glm::radians(rotation)); }
}

static float cos(float rotation) {
    if      (rotation == 0  ) { return  1.0f; }
    else if (rotation == 90 ) { return  0.0f; }
    else if (rotation == 180) { return -1.0f; }
    else if (rotation == 270) { return  0.0f; }
    else if (rotation == 360) { return  1.0f; }
    else { return glm::cos(glm::radians(rotation)); }
}

static int toUp(int a) {
    if (a < 0) { a *= (-1); }
    return a;
}

static bool inObj(const Map &pathOfMap, const glm::vec3 &p) {
    return (pathOfMap.maxX > p.x && p.x > pathOfMap.minX && pathOfMap.maxZ > p.z && p.z > pathOfMap.minZ);
}

void Door::draw(glm::vec3 &position, glm::mat4 &view, glm::mat4 &proj, GLFWwindow* window, float rotation) {

    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        pos.x += 0.01f;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        pos.x -= 0.01f;

    ps->useProgram();

    float xf = position.x + cosf(glm::radians(rotation + 90));
    float zf = position.z + sinf(glm::radians(rotation + 90));

    int x = (xf) + cols->gapX;
    int z = (zf) + cols->gapZ;

    x = toUp(x);
    z = toUp(z);

    if (inObj(*cols, glm::vec3(xf, 0.0f, zf))) {
        if (cols->obj[x + z * cols->width] == 6 && glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            *coordinate -= 0.001f;
        }
    }
    if (-1.01f < *coordinate && *coordinate < 0.0f && cols->obj[x + z * cols->width] != 0) {
        *coordinate -= 0.01f;
    } else if (*coordinate < -1.0f && cols->obj[0] != 0) {
        std::cout << x << " " << z << std::endl;
        cols->obj[x + z * cols->width] = 0;
    }

    glm::mat4 model = glm::mat4(1.0f);
    model *= glm::translate(model, pos);

    glUniformMatrix4fv(glGetUniformLocation(ps->shaderProgram,  "view"), 1, GL_FALSE,  glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(ps->shaderProgram,  "proj"), 1, GL_FALSE,  glm::value_ptr(proj));
    glUniformMatrix4fv(glGetUniformLocation(ps->shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

    cube->draw();
}

void Door::clear() {
    delete cube;
    delete ps;
}