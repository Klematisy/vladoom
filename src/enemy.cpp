#include <cmath>
#include "game.h"
#include "VPlane.h"

const static String shaderDir = "resource/Shaders/";
String bindShader(std::string dir);

Enemy::Enemy(glm::vec3 position, float rotation, int hit_points) 
{
    String vertexShaderSrc   = bindShader(shaderDir + "map/map.vert");
    String fragmentShaderSrc = bindShader(shaderDir + "map/map.frag");

    ps = new ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());

    enemy_tex = new Texture("resource/images/enemies/Enemy-01.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    enemy_tex->unbind();
    enemy_tex->uniform("tex0", *ps, 0);
    this->rotation = rotation;
    this->hit_points = hit_points;
    this->position = position;
}

void Enemy::update(const Collisions &colls) {
    map = check_collisions(*this, colls);
    
    float speed = 0.002f;
    int x = abs(position.x);
    int z = abs(position.z);
    
    if (!CollidesRect(x, z, position.x + cosf((90 + rotation) * 3.14 / 180.0f) * speed, position.z, 0.1f, 0.1f)) {
        position.x += cosf((90 + rotation) * 3.14 / 180.0f) * speed;
    }
    if (!CollidesRect(x, z, position.x, position.z + sinf((90 + rotation) * 3.14 / 180.0f) * speed, 0.1f, 0.1f)) {
        position.z += sinf((90 + rotation) * 3.14 / 180.0f) * speed;
    }
}

void Enemy::processing(const Collisions &colls, std::chrono::duration<float> &old_duration_enemy, std::chrono::duration<float> duration, const Player &player, glm::mat4 &view, glm::mat4 &proj) {
    if (hit_points > 0)
        update(colls);
    draw(old_duration_enemy, duration, player, view, proj);
}

void Enemy::draw(std::chrono::duration<float> &old_duration_enemy, std::chrono::duration<float> duration, const Player &player, glm::mat4 &view, glm::mat4 &proj) {
    enemy_tex->bind(GL_TEXTURE0);
    ps->useProgram();

    glm::vec3 p = player.position;
    float deltaX = fabsf(p.x - position.x + 0.5f);

    glm::vec3 v1(-deltaX, position.y, 0.0f);
    glm::vec3 v2(p.x - position.x, position.y, p.z - position.z);

    float ab = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    float moda = glm::sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
    float modb = glm::sqrt(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);

    float angle_btw_vecs = glm::acos(ab / (moda * modb));

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
    if (p.z < position.z)
        tex_rotation -= (angle_btw_vecs * 180 / 3.14f) + 44;
    else
        tex_rotation += (angle_btw_vecs * 180 / 3.14f);
    // std::cout << tex_rotation << std::endl;
    if (hit_points <= 0) {
        if (tex_x < 5 && duration.count() - old_duration_enemy.count() > 0.16f) {
            tex_x++;
            old_duration_enemy = duration;
        }
        Vertical_plane::draw_once(-0.5f, 0.0f, 0, -0.5f, 0.0f, tex_x, 6, 8.0f, 7.0f);
    } else {
        if (fabsf(position.x - position_check.x) < 0.0000001 || fabsf(position.z - position_check.z) < 0.0000001) {
            Vertical_plane::draw_once(-0.5f, 0.0f, 0, -0.5f, 0.0f, std::ceil(tex_rotation / 45), 5, 8.0f, 7.0f);
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
