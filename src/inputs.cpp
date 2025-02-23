#include <cmath>
#include <vector>
#include <memory>
#include "libs.h"
#include "input.h"
#include "constants.h"
#include "game.h"
#include "settings.h"

static float speed;

void input_pause(GLFWwindow *window, GAME_STATE &game_s, uint &menu_counter) {
    
}

void input_game(GAME_STATE &game_s,
                std::vector<S_Door*> &secret_doors, 
                std::vector<Door*> &doors, 
                Collisions &colls, Player &player, 
                std::vector<Enemy*> &enemies, 
                GLFWwindow *window,
                std::chrono::duration<float> duration, 
                std::chrono::duration<float> &old_duration_shoot) 
{

    float spd = 0.04f;
    int x, z, x1, z1;
    float player_width = 0.1f;
    map = check_collisions(player, colls);
    
    x = std::ceil(player.position.x);
    z = std::ceil(player.position.z);
    
    // std::cout << x << " " << z << std::endl;

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    glfwSetCursorPos(window, 2560 / 2.0f, 1600 / 2.0f);

    if (KeyboardInput::KEY_LSHIFT_PRESSED(window) || KeyboardInput::KEY_RSHIFT_PRESSED(window)) {
        speed = spd / 2;
    } else {
        speed = spd;
    }
    if (KeyboardInput::KEY_A_PRESSED(window)) {
        if (!CollidesRect(x, z, player.position.x - sinf(-(90 + player.rotation) * 3.14 / 180.0f) * speed, player.position.z, player_width, player_width)) {
            player.position.x -= sinf(-(90 + player.rotation) * 3.14 / 180.0f) * speed;
        }
        if (!CollidesRect(x, z, player.position.x, player.position.z - cosf(-(90 + player.rotation) * 3.14 / 180.0f) * speed, player_width, player_width)) {
            player.position.z -= cosf(-(90 + player.rotation) * 3.14 / 180.0f) * speed;
        }
    }
    if (KeyboardInput::KEY_D_PRESSED(window))  {
        if (!CollidesRect(x, z, player.position.x + sinf(-(90 + player.rotation) * 3.14 / 180.0f) * speed, player.position.z, player_width, player_width)) {
            player.position.x += sinf(-(90 + player.rotation) * 3.14 / 180.0f) * speed;
        }
        if (!CollidesRect(x, z, player.position.x, player.position.z + cosf(-(90 + player.rotation) * 3.14 / 180.0f) * speed, player_width, player_width)) {
            player.position.z += cosf(-(90 + player.rotation) * 3.14 / 180.0f) * speed;
        }
    }
    if (KeyboardInput::KEY_W_PRESSED(window)) {
        if (!CollidesRect(x, z, player.position.x + cosf((90 + player.rotation) * 3.14 / 180.0f) * speed, player.position.z,  player_width, player_width)) {
            player.position.x += cosf((90 + player.rotation) * 3.14 / 180.0f) * speed;
        }
        if (!CollidesRect(x, z, player.position.x, player.position.z + sinf((90 + player.rotation) * 3.14 / 180.0f) * speed,  player_width, player_width)) {
            player.position.z += sinf((90 + player.rotation) * 3.14 / 180.0f) * speed;
        }
    }
    if (KeyboardInput::KEY_S_PRESSED(window)) {
        if (!CollidesRect(x, z, player.position.x - cosf((90 + player.rotation) * 3.14 / 180.0f) * speed, player.position.z,  player_width, player_width)) {
            player.position.x -= cosf((90 + player.rotation) * 3.14 / 180.0f) * speed;
        }
        if (!CollidesRect(x, z, player.position.x, player.position.z - sinf((90 + player.rotation) * 3.14 / 180.0f) * speed,  player_width, player_width)) {
            player.position.z -= sinf((90 + player.rotation) * 3.14 / 180.0f) * speed;
        }
    }
    
    if (KeyboardInput::KEY_I_PRESSED(window) && player.hit_points < 100) {
        player.hit_points += 1.0f;
    }
    
    if (KeyboardInput::KEY_K_PRESSED(window) && player.hit_points > 0) {
        player.hit_points -= 1.0f;
    }
    
    if (KeyboardInput::KEY_E_PRESSED(window)) {
        for (Door *door : doors) {
            door->door_cheking(player.position, player.rotation);
        }
        for (S_Door *sdoors : secret_doors) {
            sdoors->door_cheking(player.position, player.rotation);
        }
    }
    
    if (KeyboardInput::KEY_ESCAPE_PRESSED(window)) {
        game_s = PAUSE;
    }
    if (KeyboardInput::KEY_LEFT_PRESSED(window))
        player.rotation -= 1.5f;
    if (KeyboardInput::KEY_RIGHT_PRESSED(window))
        player.rotation += 1.5f;

    if (xpos - 1280.0f != 0) {
        player.rotation += (xpos - 1280.0f) / 4;
    }
    
    if (MouseInput::LEFT_KEY_PRESSED(window) ||
        KeyboardInput::KEY_UP_PRESSED(window))
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
        
        float time = 0.05f;
        
        if (player.typeOfGun != 1 && player.ammo > 0 && (player.gun.num_of_animation == 0 || (player.gun.num_of_animation == 3 && player.typeOfGun == 4 && duration.count() - old_duration_shoot.count() > time))) {
            for (const Map *path_of_map : colls._piecesOfMap) {
                if (!inObj(*path_of_map, player.position)) continue;
                for (Enemy *enemy : enemies) {
                    if (inObj(*path_of_map, enemy->position) && enemy->state != Enemy::ATTACK) {
                        enemy->state = Enemy::SEARCH;
                        enemy->search_player(*path_of_map, player.position);
                    }
                }
                break;
            }
        }
        
        while (loop && player.typeOfGun != 1 && player.ammo > 0 && 
              (player.gun.num_of_animation == 0 || 
             ((player.gun.num_of_animation == 2 || player.gun.num_of_animation == 3) && 
               player.typeOfGun == 4 && duration.count() - old_duration_shoot.count() > time))) 
        {
            pos_of_bullet.x += cosf((90 + player.rotation) * 3.14 / 180.0f) * 0.2f;
            pos_of_bullet.z += sinf((90 + player.rotation) * 3.14 / 180.0f) * 0.2f;
            for (const Map *path_of_map : colls._piecesOfMap) {
                if (!inObj(*path_of_map, pos_of_bullet) || path_of_map->type == UNSHOOTABLE) continue;

                x = abs(std::ceil(pos_of_bullet.x + path_of_map->gap_x));
                z = abs(std::ceil(pos_of_bullet.z + path_of_map->gap_z));

                if (path_of_map->obj[x + z * path_of_map->width] > 0) {
                    player.ammo--;
                    loop = false;
                    // std::cout << abs(std::ceil(pos_of_bullet.x)) << " " << abs(std::ceil(pos_of_bullet.z)) << " " << player.ammo << std::endl;
                    break;
                }
            }
            
            for (size_t i = 0; i < enemies.size(); i++) {
                if (enemies[i]->hit_points > 0 && fabsf(pos_of_bullet.x - enemies[i]->position.x) < 0.2f && fabsf(pos_of_bullet.z - enemies[i]->position.z) < 0.2f) {
                    player.ammo--;
                    enemies[i]->hit_points -= damage;
                    std::cout << enemies[i]->hit_points << std::endl;
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
            pos_of_bullet.x += cosf((90 + player.rotation) * 3.14 / 180.0f) * 0.4f;
            pos_of_bullet.z += sinf((90 + player.rotation) * 3.14 / 180.0f) * 0.4f;
            for (size_t i = 0; i < enemies.size(); i++) {
                if (enemies[i]->hit_points > 0 && fabsf(pos_of_bullet.x - enemies[i]->position.x) < 0.3f && fabsf(pos_of_bullet.z - enemies[i]->position.z) < 0.3f) {
                    if (enemies[i]->state != Enemy::ATTACK) enemies[i]->hit_points -= enemies[i]->hit_points;
                    else                                   enemies[i]->hit_points -= damage;
                    std::cout << enemies[i]->hit_points << std::endl;
                    loop = false;
                    break;
                }
            }
        }
    }
}