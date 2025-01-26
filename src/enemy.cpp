#include <cmath>
#include "game.h"
#include "VPlane.h"

const static String shaderDir = "resource/Shaders/";
String bindShader(std::string dir);

Enemy::Enemy(GLFWwindow *window, glm::vec3 position, float rotation, int hit_points, String name_of_file, uint turn)
{
    String vertexShaderSrc   = bindShader(shaderDir + "map/map.vert");
    String fragmentShaderSrc = bindShader(shaderDir + "map/map.frag");
    
    this->turn   = turn;
    this->window = window;
    
    ps = new ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    
    state = DUTY;
    
    enemy_tex = new Texture((((String)"resource/images/enemies/").append(name_of_file)).c_str(), GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    enemy_tex->unbind();
    enemy_tex->uniform("tex0", *ps, 0);
    this->rotation = fmodf(rotation, 360);
    this->hit_points = hit_points;
    this->position = position;
}

void Enemy::update(const Collisions &colls, const std::vector<Door*> &doors, const glm::vec3 &player_pos) {
    map = check_collisions(*this, colls);
    
    float speed = 0.005f;
    
    int x = std::ceil(position.x);
    int z = std::ceil(position.z);
    
    float x1 = cosf((90 + rotation) * 3.14 / 180.0f);
    float z1 = sinf((90 + rotation) * 3.14 / 180.0f);
    
    switch (state) {
        case DUTY: {
            if ((int) rotation % turn == 0) {
                if (!CollidesRect(x, z, position.x + x1 * speed, position.z, 0.4f, 0.4f)) {
                    position.x += cosf((90 + rotation) * 3.14 / 180.0f) * speed;
                }
                if (!CollidesRect(x, z, position.x, position.z + z1 * speed, 0.4f, 0.4f)) {
                    position.z += sinf((90 + rotation) * 3.14 / 180.0f) * speed;
                }
                rotation = (int) rotation;
            } else {
                rotation += 0.5f;
                break;
            }
            
            int element = 12 + (x - (int) std::ceil(position.x + x1 * 0.55f)) + (z - (int) std::ceil(position.z + z1 * 0.55f)) * 5;
            if (map.get()[element] != 6 && map.get()[element] != 0) {
                rotation += 1.0f;
            } 
            break;
        }
        case SEARCH: {
            
            break;
        }
        case ATTACK:
            
        break;
    }
    
    if (fabsf(position.x - position_check.x) < 0.0000001 || fabsf(position.z - position_check.z) < 0.0000001) {
        for (Door *door : doors) {
            door->door_cheking(position, rotation);
        }
    }
}

void Enemy::processing(const Collisions &colls, std::chrono::duration<float> duration, const Player &player, glm::mat4 &view, glm::mat4 &proj, const std::vector<Door*> &doors) {
    if (hit_points > 0)
        update(colls, doors, player.position);
    rotation = fmodf(rotation, 360.0f);
    draw(duration, player, view, proj);
}

static float angle_between_vectors(glm::vec3 v1, glm::vec3 v2) {
    float ab   = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    float moda = glm::sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
    float modb = glm::sqrt(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);
    
    return glm::acos(ab / (moda * modb));
}

void Enemy::draw(std::chrono::duration<float> duration, const Player &player, glm::mat4 &view, glm::mat4 &proj) {
    enemy_tex->bind(GL_TEXTURE0);
    ps->useProgram();

    glm::vec3 p = player.position;
    float deltaX = fabsf(p.x - position.x + 0.5f);

    glm::vec3 v1(-deltaX, position.y, 0.0f);
    glm::vec3 v2(p.x - position.x, position.y, p.z - position.z);

    float angle_btw_vecs = angle_between_vectors(v1, v2);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, -position);

    if (p.z < position.z)
        model = glm::rotate(model, (glm::radians(90.0f) - angle_btw_vecs), glm::vec3(0.0f, 1.0f, 0.0f));
    else
        model = glm::rotate(model, (glm::radians(90.0f) + angle_btw_vecs), glm::vec3(0.0f, 1.0f, 0.0f));

    int viewLoc  = glGetUniformLocation(ps->shaderProgram,  "view");
    glUniformMatrix4fv(viewLoc,  1, GL_FALSE, glm::value_ptr(view));
    int projLoc  = glGetUniformLocation(ps->shaderProgram,  "proj");
    glUniformMatrix4fv(projLoc,  1, GL_FALSE, glm::value_ptr(proj));
    int modelLoc = glGetUniformLocation(ps->shaderProgram,  "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    int tex_rotation = 22;
    
    v1 = position;
    
    v1.x = (v1.x + cosf((90 + rotation) * 3.14 / 180.0f)) - v1.x;
    v1.z = (v1.z + sinf((90 + rotation) * 3.14 / 180.0f)) - v1.z;
    
    angle_btw_vecs = angle_between_vectors(v1, v2);
    
    //let's create a line equation
    
    float k = (position.z - (position.z + sinf((90 + rotation) * 3.14 / 180.0f))) / (position.x - (position.x + cosf((90 + rotation) * 3.14 / 180.0f)));
    float b = position.z + sinf((90 + rotation) * 3.14 / 180.0f) - k * (position.x + cosf((90 + rotation) * 3.14 / 180.0f));
    
    // std::cout << k << " " << b << "\n";
    
    int znak_x;
    int znak_z;
    
    znak_x = (rotation >  90)  ? -1 :  1;
    znak_x = (rotation > 270)  ? 1  :  znak_x;
    
    znak_z = (rotation >   0)  ? -1 :  1;
    znak_z = (rotation > 180)  ? 1  :  znak_z;
    
    if (znak_x * p.x < znak_x * (p.z - b) / k && znak_z * p.z > znak_z * (k * p.x + b)) {
        tex_rotation -= (angle_btw_vecs * 180 / 3.14f) + 44;
    } else {
        tex_rotation += (angle_btw_vecs * 180 / 3.14f);
    }
    // std::cout << tex_rotation << std::endl;

    if (hit_points <= 0) {
        if (tex_x < 5 && duration.count() - old_duration_enemy.count() > 0.16f) {
            tex_x++;
            old_duration_enemy = duration;
        }
        Vertical_plane::draw_once(-0.5f, 0.0f, 0, -0.5f, 0.0f, tex_x, 6, 8.0f, 7.0f);
    } else {
        if (fabsf(position.x - position_check.x) < 0.0001 && fabsf(position.z - position_check.z) < 0.0001) {
            Vertical_plane::draw_once(-0.5f, 0.0f, 0, -0.5f, 0.0f, std::ceil(tex_rotation / 45), 4, 8.0f, 7.0f);
        } else {
            if (duration.count() - old_duration_enemy.count() > 0.3f) {
                tex_y = (tex_y < 3) ? ++tex_y : 0;
                old_duration_enemy = duration;
            }
            Vertical_plane::draw_once(-0.5f, 0.0f, 0, -0.5f, 0.0f, std::ceil(tex_rotation / 45), tex_y, 8.0f, 7.0f);
        
            position_check = position;
        }
    }
}

void Enemy::clear() {
    ps->deleteShader();
    
    delete ps;
    delete enemy_tex;
}
