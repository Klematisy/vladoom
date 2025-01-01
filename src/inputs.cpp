#include <cmath>
#include "libs.h"
#include "constants.h"
#include "settings.h"

static float speed;
static int *map;

bool Collides(int stX, int stZ, float x, float z) {
    int x1 = x;
    int z1 = z;
    x1 = toUp(x1);
    z1 = toUp(z1);
    return map[12 + (x1 - stX) + (z1 - stZ) * 5] == 1;
}

bool CollidesRect(int startX, int startZ, float x, float z, float x_half_extent, float z_half_extent) {
    return Collides(startX, startZ, x - x_half_extent, z - z_half_extent)
        || Collides(startX, startZ, x + x_half_extent, z - z_half_extent)
        || Collides(startX, startZ, x + x_half_extent, z + z_half_extent)
        || Collides(startX, startZ, x - x_half_extent, z + z_half_extent);
}

void input(Collisions& colls, glm::vec3 &position, float &rotation, GLFWwindow *window, bool &run) {

    std::vector<Map> collisions;
    int x, z, x1, z1;
    float spd = 0.04f;
    glm::vec3 pointPos = position;
    
    int arr[25] = {
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 2, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0
    };

    int k = 0;
    for (const Map *pathOfMap : colls._piecesOfMap) {
        for (float rot = 0.0f; rot < 360.0f; rot+=45.0f) {
            pointPos = position;

            x = std::ceil(pointPos.x + pathOfMap->gapX);
            z = std::ceil(pointPos.z + pathOfMap->gapZ);

            pointPos.x += cos(rot);
            pointPos.z += sin(rot);

            x1 = std::ceil(pointPos.x + pathOfMap->gapX);
            z1 = std::ceil(pointPos.z + pathOfMap->gapZ);

            if (inObj(*pathOfMap, pointPos) && pathOfMap->obj[toUp(x1) + toUp(z1) * pathOfMap->width] > 0) {
                arr[12 + (x - x1) + (z - z1) * 5] = 1;
            }
        }
    }

    map = arr;

    x = position.x;
    z = position.z;

    x = toUp(x);
    z = toUp(z);
    
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    glfwSetCursorPos(window, 2560 / 2.0f, 1600 / 2.0f);

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        speed = spd / 2;
    } else {
        speed = spd;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        if (!CollidesRect(x, z, position.x - sinf(-(90 + rotation) * 3.14 / 180.0f) * speed, position.z, 0.1f, 0.1f)) {
            position.x -= sinf(-(90 + rotation) * 3.14 / 180.0f) * speed;
        }
        if (!CollidesRect(x, z, position.x, position.z - cosf(-(90 + rotation) * 3.14 / 180.0f) * speed, 0.1f, 0.1f)) {
            position.z -= cosf(-(90 + rotation) * 3.14 / 180.0f) * speed;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)  {
        if (!CollidesRect(x, z, position.x + sinf(-(90 + rotation) * 3.14 / 180.0f) * speed, position.z, 0.1f, 0.1f)) {
            position.x += sinf(-(90 + rotation) * 3.14 / 180.0f) * speed;
        }
        if (!CollidesRect(x, z, position.x, position.z + cosf(-(90 + rotation) * 3.14 / 180.0f) * speed, 0.1f, 0.1f)) {
            position.z += cosf(-(90 + rotation) * 3.14 / 180.0f) * speed;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        if (!CollidesRect(x, z, position.x + cosf((90 + rotation) * 3.14 / 180.0f) * speed, position.z, 0.1f, 0.1f)) {
            position.x += cosf((90 + rotation) * 3.14 / 180.0f) * speed;
        }
        if (!CollidesRect(x, z, position.x, position.z + sinf((90 + rotation) * 3.14 / 180.0f) * speed, 0.1f, 0.1f)) {
            position.z += sinf((90 + rotation) * 3.14 / 180.0f) * speed;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        if (!CollidesRect(x, z, position.x - cosf((90 + rotation) * 3.14 / 180.0f) * speed, position.z, 0.1f, 0.1f)) {
            position.x -= cosf((90 + rotation) * 3.14 / 180.0f) * speed;
        }
        if (!CollidesRect(x, z, position.x, position.z - sinf((90 + rotation) * 3.14 / 180.0f) * speed, 0.1f, 0.1f)) {
            position.z -= sinf((90 + rotation) * 3.14 / 180.0f) * speed;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        run = false;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) 
        rotation -= 1.5f;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        rotation += 1.5f;

    if (xpos - 1280.0f != 0) {
        rotation += (xpos - 1280.0f) / 4;
    }
}