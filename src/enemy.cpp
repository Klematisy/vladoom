#include <cmath>
#include "game.h"
#include "VPlane.h"

const static String shaderDir = "resource/Shaders/";
String bindShader(std::string dir);

Enemy::Enemy(glm::vec3 position) : position(position) {
    String vertexShaderSrc   = bindShader(shaderDir + "map/map.vert");
    String fragmentShaderSrc = bindShader(shaderDir + "map/map.frag");

    ps = new ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    enemy_shape = new Vertical_plane(-0.5f, 0.0f, 0, -0.5f, 0.0f, 0, 1.0f);

    enemy_tex = new Texture("resource/images/enemies/vlad.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    enemy_tex->unbind();
    enemy_tex->uniform("tex0", *ps, 0);
}

void Enemy::draw(const Player &player, glm::mat4 &view, glm::mat4 &proj) {
    enemy_tex->bind(GL_TEXTURE0);
    ps->useProgram();

    glm::vec3 p(-player.position.x, -player.position.y, -player.position.z);
    float deltaX = fabsf(p.x - position.x + 0.5f);

    glm::vec3 v1(position.x - deltaX - position.x, position.y, 0.0f);
    glm::vec3 v2(p.x - position.x, position.y, p.z - position.z);

    float ab = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    float moda = glm::sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
    float modb = glm::sqrt(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);
    
    rotation = glm::acos(ab / (moda * modb));

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);

    if (p.z < position.z)
        model = glm::rotate(model, (glm::radians(90.0f) - rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    else
        model = glm::rotate(model, (glm::radians(90.0f) + rotation), glm::vec3(0.0f, 1.0f, 0.0f));

    int viewLoc  = glGetUniformLocation(ps->shaderProgram,  "view");
    glUniformMatrix4fv(viewLoc,  1, GL_FALSE, glm::value_ptr(view));
    int projLoc  = glGetUniformLocation(ps->shaderProgram,  "proj");
    glUniformMatrix4fv(projLoc,  1, GL_FALSE, glm::value_ptr(proj));
    int modelLoc = glGetUniformLocation(ps->shaderProgram,  "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    enemy_shape->draw();
}

Enemy::~Enemy() {
    // enemy_shape->deletePlane();
    // ps->deleteShader();

    // delete ps;
    // delete enemy_shape;
    // delete enemy_tex;
}