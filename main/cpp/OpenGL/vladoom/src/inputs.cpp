#include <cmath>
#include <vector>
#include <memory>
#include "libs.h"
#include "constants.h"
#include "settings.h"

static float speed;

void input(Collisions &colls, Player &player, std::vector<Enemy> &enemies, GLFWwindow *window, bool &run) {

    std::vector<Map> collisions;
    float spd = 0.04f;
    int x, z, x1, z1;
    map = check_collisions(player, colls);

    x = player.position.x;
    z = player.position.z;

    x = abs(x);
    z = abs(z);
    // std::cout << enemies[0].position.x << " " << enemies[0].position.z << std::endl;
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
        glm::vec3 pos_of_bullet = player.position;
        pos_of_bullet = player.position;
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
            break;
        }

        if (player.typeOfGun == 1) {
            pos_of_bullet.x += cosf((90 + player.rotation) * 3.14 / 180.0f) * 0.2f;
            pos_of_bullet.z += sinf((90 + player.rotation) * 3.14 / 180.0f) * 0.2f;
            for (size_t i = 0; i < enemies.size(); i++) {
                if (enemies[i].hit_points <= 0)
                    remove<Enemy>(enemies, i);

                if (fabsf(pos_of_bullet.x - enemies[i].position.x) < 0.2f && fabsf(pos_of_bullet.z - enemies[i].position.z) < 0.2f) {
                    enemies[i].hit_points -= damage;
                    std::cout << enemies[i].hit_points << std::endl;
                    loop = false;
                    break;
                }
            }
        }
        
        while (loop && player.typeOfGun != 1 && player.ammo > 0) {
            pos_of_bullet.x += cosf((90 + player.rotation) * 3.14 / 180.0f) * 0.2f;
            pos_of_bullet.z += sinf((90 + player.rotation) * 3.14 / 180.0f) * 0.2f;
            for (const Map *pathOfMap : colls._piecesOfMap) {
                if (!inObj(*pathOfMap, pos_of_bullet)) continue;

                x = abs(std::ceil(pos_of_bullet.x + pathOfMap->gapX));
                z = abs(std::ceil(pos_of_bullet.z + pathOfMap->gapZ));

                x1 = abs(std::ceil(pos_of_bullet.x));
                z1 = abs(std::ceil(pos_of_bullet.z));

                for (size_t i = 0; i < enemies.size(); i++) {
                    if (enemies[i].hit_points <= 0) {
                        remove<Enemy>(enemies, i);
                    }
                    if (fabsf(pos_of_bullet.x - enemies[i].position.x) < 0.2f && fabsf(pos_of_bullet.z - enemies[i].position.z) < 0.2f) {
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
            if (sqrt((pos_of_bullet.x - player.position.x) * (pos_of_bullet.x - player.position.x)
                   + (pos_of_bullet.z - player.position.z) * (pos_of_bullet.z - player.position.z)) >= 30) {
                break;
            }
        }
    }
}
