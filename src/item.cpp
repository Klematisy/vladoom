#include "game.h"

const static String shaderDir = "resource/Shaders/";
String bindShader(std::string dir);

Item::Item(float xGap, float zGap, int tex_num, float changeble, Player &player, TYPE_0F_ITEM type) {
    xGap *= -1;
    zGap *= -1;
    position = glm::vec3(-xGap, 0.0f, -zGap);
    this->tex_num = tex_num;
    this->changeble = changeble;
    this->type = type;
    
    switch (type) {
        case HEALTH: {
            tex_y = 3;
            break;
        }
        case GUN: {
            tex_y = 2;
            break;
        }
        case SCORE: {
            tex_y = 1;
            break;
        }
        case KEY: {
            tex_y = 0;
            break;
        }
    }
    
    String vertexShaderSrc   = bindShader(shaderDir + "map/map.vert");
    String fragmentShaderSrc = bindShader(shaderDir + "map/map.frag");
    
    ps = new ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    tex = new Texture("resource/images/items.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    tex->unbind();
    tex->uniform("tex0", *ps, 0);
}

void Item::update(Player &player) {
    if (fabsf(player.position.x - position.x) < 0.1f && fabsf(player.position.z - position.z) < 0.1f) {
        switch (type) {
            case HEALTH: {
                std::cout << "ldskjflkdsjf\n";
                if (player.hit_points < 100) {
                    player.hit_points += (int) changeble;
                    changeble = 0;
                }
                break;
            }
            case GUN: {
                switch (tex_num) {
                    case 1: {
                        if (player.ammo < 99) {
                            player.ammo += (int) changeble;
                            changeble = 0;
                        }
                        break;
                    }
                    case 2: {
                        if (player.invetory[2] != 3) {
                            player.invetory[2] = 3;
                            changeble = 0;
                        }
                        break;
                    }
                    case 3: {
                        if (player.invetory[3] != 4) {
                            player.invetory[3] = 4;
                            changeble = 0;
                        }
                    }
                }
                break;
            }
            case SCORE: {
                player.score += changeble;
                changeble = 0;
                break;
            }
            case KEY: {
                
            }
        }
    }
}

void Item::draw(const Player &player, glm::mat4 &view, glm::mat4 &proj) {
    ps->useProgram();
    tex->bind(GL_TEXTURE0);
    
    glm::vec3 p = player.position;
    float deltaX = fabsf(p.x - position.x + 0.5f);

    glm::vec2 v1 = take_vector2D({position.x + deltaX, 0.0f}, {position.x, 0.0f});
    glm::vec2 v2 = take_vector2D({position.x, position.z}, {p.x, p.z});

    float angle_btw_vecs = angle_between_vectors2D(v1, v2);

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
    
    int tex_x = tex_num - 1;
    
    Vertical_plane::draw_once(-0.5f, 0.0f, 0, -0.5f, 0.0f, tex_x, tex_y, 4, 4);
}

void Item::processing(Player &player, glm::mat4 &view, glm::mat4 &proj) {
    if (changeble > 0.0f) {
        update(player);
        draw(player, view, proj);
    }
}