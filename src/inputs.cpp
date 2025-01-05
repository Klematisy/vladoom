#include <cmath>
#include <vector>
#include "libs.h"
#include "constants.h"
#include "settings.h"

static float speed;
static int *map;

template <typename T>
void remove(std::vector<T>& v, size_t index) {
    v.erase(v.begin() + index);
}

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

void input(Collisions& colls, Player &player, std::vector<Enemy> &enemies, GLFWwindow *window, bool &run) {

    std::vector<Map> collisions;
    int x, z, x1, z1;
    float spd = 0.04f;
    glm::vec3 pointPos = player.position;
    
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
            pointPos = player.position;

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

    x = player.position.x;
    z = player.position.z;

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
        if (!CollidesRect(x, z, player.position.x - sinf(-(90 + player.rotation) * 3.14 / 180.0f) * speed, player.position.z, 0.1f, 0.1f)) {
            player.position.x -= sinf(-(90 + player.rotation) * 3.14 / 180.0f) * speed;
        }
        if (!CollidesRect(x, z, player.position.x, player.position.z - cosf(-(90 + player.rotation) * 3.14 / 180.0f) * speed, 0.1f, 0.1f)) {
            player.position.z -= cosf(-(90 + player.rotation) * 3.14 / 180.0f) * speed;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)  {
        if (!CollidesRect(x, z, player.position.x + sinf(-(90 + player.rotation) * 3.14 / 180.0f) * speed, player.position.z, 0.1f, 0.1f)) {
            player.position.x += sinf(-(90 + player.rotation) * 3.14 / 180.0f) * speed;
        }
        if (!CollidesRect(x, z, player.position.x, player.position.z + cosf(-(90 + player.rotation) * 3.14 / 180.0f) * speed, 0.1f, 0.1f)) {
            player.position.z += cosf(-(90 + player.rotation) * 3.14 / 180.0f) * speed;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        if (!CollidesRect(x, z, player.position.x + cosf((90 + player.rotation) * 3.14 / 180.0f) * speed, player.position.z, 0.1f, 0.1f)) {
            player.position.x += cosf((90 + player.rotation) * 3.14 / 180.0f) * speed;
        }
        if (!CollidesRect(x, z, player.position.x, player.position.z + sinf((90 + player.rotation) * 3.14 / 180.0f) * speed, 0.1f, 0.1f)) {
            player.position.z += sinf((90 + player.rotation) * 3.14 / 180.0f) * speed;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        if (!CollidesRect(x, z, player.position.x - cosf((90 + player.rotation) * 3.14 / 180.0f) * speed, player.position.z, 0.1f, 0.1f)) {
            player.position.x -= cosf((90 + player.rotation) * 3.14 / 180.0f) * speed;
        }
        if (!CollidesRect(x, z, player.position.x, player.position.z - sinf((90 + player.rotation) * 3.14 / 180.0f) * speed, 0.1f, 0.1f)) {
            player.position.z -= sinf((90 + player.rotation) * 3.14 / 180.0f) * speed;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        run = false;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) 
        player.rotation -= 1.5f;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        player.rotation += 1.5f;

    if (xpos - 1280.0f != 0) {
        player.rotation += (xpos - 1280.0f) / 4;
    }

    if (player.gun.num_of_animation == 0 && 
        (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS))
    {
        pointPos = player.position;
        bool loop = true;
        int damage = 0;
        switch (player.typeOfGun) {
            case 1: damage = 10;
            break;
            case 2: damage = 20;
            break;
            case 3: damage = 50;
            break;
            case 4: damage = 100;
        }

        if (player.typeOfGun == 1) {
            pointPos.x += cosf((90 + player.rotation) * 3.14 / 180.0f) * 0.2f;
            pointPos.z += sinf((90 + player.rotation) * 3.14 / 180.0f) * 0.2f;
            for (size_t i = 0; i < enemies.size(); i++) {
                if (enemies[i].hit_points <= 0)
                    remove<Enemy>(enemies, i);
                    
                if (fabsf(pointPos.x + enemies[i].position.x) < 0.2f && fabsf(pointPos.z + enemies[i].position.z) < 0.2f) {
                    enemies[i].hit_points -= damage;
                    std::cout << enemies[i].hit_points << std::endl;
                    loop = false;
                    break;
                }
            }
        }

        while (loop && player.typeOfGun != 1 && player.ammo > 0) {
            pointPos.x += cosf((90 + player.rotation) * 3.14 / 180.0f) * 0.2f;
            pointPos.z += sinf((90 + player.rotation) * 3.14 / 180.0f) * 0.2f;
            for (const Map *pathOfMap : colls._piecesOfMap) {
                if (!inObj(*pathOfMap, pointPos)) continue;

                x = toUp(std::ceil(pointPos.x + pathOfMap->gapX));
                z = toUp(std::ceil(pointPos.z + pathOfMap->gapZ));

                x1 = toUp(std::ceil(pointPos.x));
                z1 = toUp(std::ceil(pointPos.z));
                
                for (size_t i = 0; i < enemies.size(); i++) {
                    if (enemies[i].hit_points <= 0) {
                        remove<Enemy>(enemies, i);
                    }
                    if (fabsf(pointPos.x + enemies[i].position.x) < 0.2f && fabsf(pointPos.z + enemies[i].position.z) < 0.2f) {
                        enemies[i].hit_points -= damage;
                        std::cout << enemies[i].hit_points << std::endl;
                        loop = false;
                        break;
                    }
                }

                if (pathOfMap->obj[x + z * pathOfMap->width] > 0) {
                    loop = false;
                    std::cout << x1 << " " << z1 << std::endl;
                    break;
                }
            }
        }
    }
}