#include <cmath>
#include <vector>
#include <memory>
#include "libs.h"
#include "constants.h"
#include "settings.h"

static float speed;

void input(const std::vector<Door*> &doors, Collisions &colls, Player &player, std::vector<Enemy> &enemies, GLFWwindow *window, bool &run, std::chrono::duration<float> duration, std::chrono::duration<float> &old_duration_shoot) {

    std::vector<Map> collisions;
    float spd = 0.04f;
    int x, z, x1, z1;
    float player_width = 0.1f;
    map = check_collisions(player, colls);
    
    x = std::ceil(player.position.x);
    z = std::ceil(player.position.z);

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    glfwSetCursorPos(window, 2560 / 2.0f, 1600 / 2.0f);

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        speed = spd / 2;
    } else {
        speed = spd;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        if (!CollidesRect(x, z, player.position.x - sinf(-(90 + player.rotation) * 3.14 / 180.0f) * speed, player.position.z, player_width, player_width)) {
            player.position.x -= sinf(-(90 + player.rotation) * 3.14 / 180.0f) * speed;
        }
        if (!CollidesRect(x, z, player.position.x, player.position.z - cosf(-(90 + player.rotation) * 3.14 / 180.0f) * speed, player_width, player_width)) {
            player.position.z -= cosf(-(90 + player.rotation) * 3.14 / 180.0f) * speed;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)  {
        if (!CollidesRect(x, z, player.position.x + sinf(-(90 + player.rotation) * 3.14 / 180.0f) * speed, player.position.z, player_width, player_width)) {
            player.position.x += sinf(-(90 + player.rotation) * 3.14 / 180.0f) * speed;
        }
        if (!CollidesRect(x, z, player.position.x, player.position.z + cosf(-(90 + player.rotation) * 3.14 / 180.0f) * speed, player_width, player_width)) {
            player.position.z += cosf(-(90 + player.rotation) * 3.14 / 180.0f) * speed;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        if (!CollidesRect(x, z, player.position.x + cosf((90 + player.rotation) * 3.14 / 180.0f) * speed, player.position.z,  player_width, player_width)) {
            player.position.x += cosf((90 + player.rotation) * 3.14 / 180.0f) * speed;
        }
        if (!CollidesRect(x, z, player.position.x, player.position.z + sinf((90 + player.rotation) * 3.14 / 180.0f) * speed,  player_width, player_width)) {
            player.position.z += sinf((90 + player.rotation) * 3.14 / 180.0f) * speed;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        if (!CollidesRect(x, z, player.position.x - cosf((90 + player.rotation) * 3.14 / 180.0f) * speed, player.position.z,  player_width, player_width)) {
            player.position.x -= cosf((90 + player.rotation) * 3.14 / 180.0f) * speed;
        }
        if (!CollidesRect(x, z, player.position.x, player.position.z - sinf((90 + player.rotation) * 3.14 / 180.0f) * speed,  player_width, player_width)) {
            player.position.z -= sinf((90 + player.rotation) * 3.14 / 180.0f) * speed;
        }
    }
    
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        for (Door *door : doors) {
            door->door_cheking(player.position, player.rotation);
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
    
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        glm::vec3 pos_of_bullet = player.position;
        pos_of_bullet = player.position;
        bool loop = true;
        int damage = 0;
        switch (player.typeOfGun) {
            case 1: damage = 25;
            break;
            case 2: damage = 34;
            break;
            case 3: damage = 50;
            break;
            case 4: damage = 25;
            break;
        }
        
        float time = 0.03f;
        while (loop && player.typeOfGun != 1 && player.ammo > 0 && (player.gun.num_of_animation == 0 || (player.gun.num_of_animation == 3 && player.typeOfGun == 4 && duration.count() - old_duration_shoot.count() > time))) {
            pos_of_bullet.x += cosf((90 + player.rotation) * 3.14 / 180.0f) * 0.2f;
            pos_of_bullet.z += sinf((90 + player.rotation) * 3.14 / 180.0f) * 0.2f;
            for (const Map *pathOfMap : colls._piecesOfMap) {
                if (!inObj(*pathOfMap, pos_of_bullet)) continue;

                x = abs(std::ceil(pos_of_bullet.x + pathOfMap->gapX));
                z = abs(std::ceil(pos_of_bullet.z + pathOfMap->gapZ));

                x1 = abs(std::ceil(pos_of_bullet.x));
                z1 = abs(std::ceil(pos_of_bullet.z));

                if (pathOfMap->obj[x + z * pathOfMap->width] > 0) {
                    player.ammo--;
                    loop = false;
                    std::cout << x1 << " " << z1 << " " << player.ammo << std::endl;
                    break;
                }
            }
            
            for (size_t i = 0; i < enemies.size(); i++) {
                if (enemies[i].hit_points > 0 && fabsf(pos_of_bullet.x - enemies[i].position.x) < 0.2f && fabsf(pos_of_bullet.z - enemies[i].position.z) < 0.2f) {
                    player.ammo--;
                    enemies[i].hit_points -= damage;
                    std::cout << enemies[i].hit_points << std::endl;
                    loop = false;
                    break;
                }
            }
            
            if (sqrt((pos_of_bullet.x - player.position.x) * (pos_of_bullet.x - player.position.x)
                   + (pos_of_bullet.z - player.position.z) * (pos_of_bullet.z - player.position.z)) >= 30) {
                player.ammo--;
                break;
            }
        }
        
        if (duration.count() - old_duration_shoot.count() > time) {
            old_duration_shoot = duration;
        }
        
        if (player.typeOfGun == 1 && player.gun.num_of_animation == 0) {
            pos_of_bullet.x += cosf((90 + player.rotation) * 3.14 / 180.0f) * 0.2f;
            pos_of_bullet.z += sinf((90 + player.rotation) * 3.14 / 180.0f) * 0.2f;
            for (size_t i = 0; i < enemies.size(); i++) {
                if (fabsf(pos_of_bullet.x - enemies[i].position.x) < 0.2f && fabsf(pos_of_bullet.z - enemies[i].position.z) < 0.2f) {
                    enemies[i].hit_points -= damage;
                    std::cout << enemies[i].hit_points << std::endl;
                    loop = false;
                    break;
                }
            }
        }
    }
}