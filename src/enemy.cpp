#include <cmath>
#include "game.h"
#include "VPlane.h"

const static String shaderDir = "resource/Shaders/";
String bindShader(std::string dir);

Enemy::Enemy(glm::vec3 position) : position(position) {
    String vertexShaderSrc   = bindShader(shaderDir + "map/map.vert");
    String fragmentShaderSrc = bindShader(shaderDir + "map/map.frag");

    ps = new ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());

    enemy_tex = new Texture("resource/images/enemies/Enemy-0001.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    enemy_tex->unbind();
    enemy_tex->uniform("tex0", *ps, 0);
}

void Enemy::update() {

}

void Enemy::processing(std::chrono::duration<float> &old_duration_enemy, std::chrono::duration<float> duration, const Player &player, glm::mat4 &view, glm::mat4 &proj) {
    // std::cout << hitPoints << std::endl;
    draw(old_duration_enemy, duration, player, view, proj);
    update();
}

void Enemy::draw(std::chrono::duration<float> &old_duration_enemy, std::chrono::duration<float> duration, const Player &player, glm::mat4 &view, glm::mat4 &proj) {
    enemy_tex->bind(GL_TEXTURE0);
    ps->useProgram();

    glm::vec3 p = -player.position;
    float deltaX = fabsf(p.x - position.x + 0.5f);

    glm::vec3 v1(-deltaX, position.y, 0.0f);
    glm::vec3 v2(p.x - position.x, position.y, p.z - position.z);

    float ab = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    float moda = glm::sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
    float modb = glm::sqrt(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);
    
    float angle_btw_vecs = glm::acos(ab / (moda * modb));

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);

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
        tex_rotation += (angle_btw_vecs * 180 / 3.14f) + 180;
    else
        tex_rotation += 180 - (angle_btw_vecs * 180 / 3.14f);
    // std::cout << tex_rotation << std::endl;
    if (hit_points <= 0) {
        if (num_of_sprite < 5 && duration.count() - old_duration_enemy.count() > 0.2f) {
            num_of_sprite++;
            old_duration_enemy = duration;
        }
        Vertical_plane::draw_once(-0.5f, 0.0f, 0, -0.5f, 0.0f, num_of_sprite, 6, 8.0f, 7.0f);
    } else {
        Vertical_plane::draw_once(-0.5f, 0.0f, 0, -0.5f, 0.0f, std::ceil(tex_rotation / 45), 5, 8.0f, 7.0f);
    }
}

void Enemy::clear() {
    ps->deleteShader();

    delete ps;
    delete enemy_tex;
}