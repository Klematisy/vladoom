#include <cmath>
#include <vector>
#include <random>
#include "game.h"
#include "VPlane.h"

const static String shaderDir = "resource/Shaders/";
String bindShader(std::string dir);

static int znak_z_func(float rotation) {
    int znak_z;
    znak_z = (rotation >   0)  ? -1 :  1;
    znak_z = (rotation > 180)  ? 1  :  znak_z;
    return znak_z;
}

static int znak_x_func(float rotation) {
    int znak_x;
    znak_x = (rotation >  90)  ? -1 :  1;
    znak_x = (rotation > 270)  ? 1  :  znak_x;
    return znak_x;
}

E_Dog::E_Dog(glm::vec3 position, float rotation, int hit_points, int danage, String name_of_file)
    : Enemy(position, rotation, hit_points, danage, name_of_file, RIGHT_TURN)
{}

void E_Dog::update(Collisions &colls, std::chrono::duration<float> duration, const std::vector<Door*> &doors, Player &player) {
    map = check_collisions(*this, colls);

    float player_rotation = (player.rotation < 0) ? 360 + player.rotation : player.rotation;

    int i = rotation / fabsf(rotation);
    rotation = (rotation < 0) ? 360 + rotation : rotation;

    float speed = 0.005f;
    int x = std::ceil(position.x);
    int z = std::ceil(position.z);

    float x1 = cosf((90 + rotation) * 3.14 / 180.0f);
    float z1 = sinf((90 + rotation) * 3.14 / 180.0f);

    glm::vec2 enemy_pos2D(position.x, position.z);
    glm::vec2 player2D(player.position.x, player.position.z);
    
    glm::vec2 enemy_dir2D(
        position.x + cosf((90 + rotation) * 3.14 / 180.0f),
        position.z + sinf((90 + rotation) * 3.14 / 180.0f)
    );
    Line lweiw;  //line_where_enemy_is_watching
    lweiw.calculate(enemy_pos2D, enemy_dir2D);

    if (state != ATTACK) vision(colls, player.position);

    switch (state) {
        case DUTY: {
            
            break;
        }
        case SEARCH: {
            speed = 0.01f;
            Point2 point = {position.x, position.z};
            if (!way.empty()) {
                point = way.back();
            } else {
                state = DUTY;
                return;
            }

            int x = abs(std::ceil(position.x));
            int z = abs(std::ceil(position.z));

            point.x += 0.5f;
            point.z += 0.5f;

            if (fabsf(point.x - fabsf(position.x)) < 0.1f && fabsf(point.z - fabsf(position.z)) < 0.1f) {
                way.pop_back();
                if (way.empty()) {
                    state = DUTY;
                    return;
                } else {
                    Point2 point = way.back();
                    point.x += 0.5f;
                    point.z += 0.5f;
                }
            }

            point.x *= position.x / abs(position.x);
            point.z *= position.z / abs(position.z);

            float angle = angle_btw_point_and_enemy({point.x, 0.0f, point.z});

            angle *= (180.0f/M_PI);
            angle  = (int) angle;

            if (angle != 0.0f) {
                int znak_x = znak_x_func(rotation);
                int znak_z = znak_z_func(rotation);

                if (znak_x * point.x < znak_x * lweiw.get_x(point.z) && znak_z * point.z > znak_z * lweiw.get_z(point.x)) {
                    rotation += (angle >= 5.0f) ? 1.0f : angle;
                    angle    -= (angle >= 5.0f) ? 1.0f : angle;
                } else {
                    rotation -= (angle >= 5.0f) ? 1.0f : angle;
                    angle    += (angle >= 5.0f) ? 1.0f : angle;
                }
            }

            if (angle == 0.0f) {
                x = std::ceil(position.x);
                z = std::ceil(position.z);

                float x1 = cosf((90 + rotation) * 3.14 / 180.0f);
                float z1 = sinf((90 + rotation) * 3.14 / 180.0f);
                if (!CollidesRect(x, z, position.x + x1 * speed, position.z, 0.4f, 0.4f)) {
                    position.x += cosf((90 + rotation) * 3.14 / 180.0f) * speed;
                }
                if (!CollidesRect(x, z, position.x, position.z + z1 * speed, 0.4f, 0.4f)) {
                    position.z += sinf((90 + rotation) * 3.14 / 180.0f) * speed;
                }
            }

            //*/
            break;
        }
        case ATTACK: {
            speed = 0.026f;
            float mod = vec_mod2D(take_vector2D({position.x, position.z}, {player.position.x, player.position.z}));

            if (mod <= 0.4f) {
                a_states = SHOOT;
            }
            
            Line lbpae;
            lbpae.calculate(enemy_pos2D, player2D);
            glm::vec3 pos_of_bullet = position;
            bool loop = true;
            while (loop) {
                pos_of_bullet.x += cosf((90 + lbpae.rotation) * 3.14 / 180.0f) * 0.2f;
                pos_of_bullet.z += sinf((90 + lbpae.rotation) * 3.14 / 180.0f) * 0.2f;
                for (const Map *path_of_map : colls._piecesOfMap) {
                    if (!inObj(*path_of_map, pos_of_bullet)) continue;
                    
                    x = abs(std::ceil(pos_of_bullet.x + path_of_map->gap_x));
                    z = abs(std::ceil(pos_of_bullet.z + path_of_map->gap_z));
                    
                    if (path_of_map->obj[x + z * path_of_map->width] > 0) {
                        search_player(*path_of_map, player.position);
                        state = SEARCH;
                        loop = false;
                        break;
                    }
                }
                
                if (fabsf(pos_of_bullet.x - player2D.x) <= 0.2f && fabsf(pos_of_bullet.z - player2D.y) <= 0.2f) {
                    break;
                }
                
                if (vec_mod2D(take_vector2D(enemy_pos2D, {pos_of_bullet.x, pos_of_bullet.z})) >= mod) {
                    break;
                }
            }
            if (!loop) break;
            
            switch (a_states) {
                case MANEUVERING: {
                    speed = 0.027f;
                    if (ufm.line_calculator_turner) {
                        // Line between enemy and player
                        ufm.line_for_maneuvering.calculate(enemy_pos2D, player2D);
                        ufm.line_for_maneuvering.rotation = (int) ufm.line_for_maneuvering.rotation;

                        ufm.movement = glm::vec2(player.position.x, player.position.z);

                        std::random_device rd;
                        std::mt19937 gen(rd());
                        std::uniform_int_distribution<> disti(0, 1);
                        ufm.maneuvering = (disti(gen) == 0) ? Utills_for_maneuvering::RIGHT : Utills_for_maneuvering::LEFT;

                        ufm.line_calculator_turner = false;
                    }

                    // float angle = angle_between_vectors2D(ufm.line_for_maneuvering.vector, lweiw.vector);
                    // Замеряем угол между ведущей линией и линией обзора противника
                    float angle_gap = 75.0f;
                    bool checker = true;

                    float angle1 = 0.0f;
                    if (ufm.maneuvering == Utills_for_maneuvering::RIGHT) {
                        angle1 = fmodf(ufm.line_for_maneuvering.rotation + angle_gap, 360.0f);
                    } else {
                        if (ufm.line_for_maneuvering.rotation - angle_gap < 0)  // я сделат тренарный оператор И ПОЛУЧИЛОСЬ НЕЧИТАЕМОЕ ДЕРЬМО!!! поэтому так (. Y .)
                            angle1 = 360.0f + ufm.line_for_maneuvering.rotation - angle_gap;
                        else
                            angle1 = ufm.line_for_maneuvering.rotation - angle_gap;
                    }

                    if (!(fabsf(angle1 - rotation) <= 4)) {
                        if (angle1 < rotation) {
                            float right = 360.0f + angle1;
                            if (right - rotation < rotation - angle1)   rotation += 4.0f;
                            else                                        rotation -= 4.0f;
                        } else {
                            float right = 360.0f + rotation;
                            if (angle1 - rotation < right - angle1)     rotation += 4.0f;
                            else                                        rotation -= 4.0f;
                        }
                        checker = !checker;
                        
                        if (rotation > 360.0f) {
                            rotation = angle1;
                        }
                    }

                    if (fabsf(angle1 - rotation) <= 4) {
                        x = std::ceil(position.x);
                        z = std::ceil(position.z);
                        x1 = cosf((90 + rotation) * 3.14 / 180.0f);
                        z1 = sinf((90 + rotation) * 3.14 / 180.0f);
                        if (!CollidesRect(x, z, position.x + x1 * speed, position.z, 0.4f, 0.4f)) {
                            position.x += x1 * speed;
                        }
                        if (!CollidesRect(x, z, position.x, position.z + z1 * speed, 0.4f, 0.4f)) {
                            position.z += z1 * speed;
                        }
                        ufm.flag_of_run.x += x1 * speed;
                        ufm.flag_of_run.y += z1 * speed;
                    }

                    float mod = vec_mod2D(take_vector2D({0.0f, 0.0f}, {ufm.flag_of_run.x, ufm.flag_of_run.y}));
                    if (fabsf(mod) >= 2.0f) {
                        ufm.maneuvering = (ufm.maneuvering == Utills_for_maneuvering::RIGHT) ? Utills_for_maneuvering::LEFT : Utills_for_maneuvering::RIGHT;
                        ufm.flag_of_run.x = 0.0f;
                        ufm.flag_of_run.y = 0.0f;
                        ufm.move_counter++;
                    }
                    
                    if (ufm.move_counter >= 5) {
                        a_states = RUN;
                        ufm.move_counter = 0;
                    }
                    
                    if (vec_mod2D(take_vector2D(player2D, ufm.movement)) >= 1.0f) {
                        ufm.line_calculator_turner = true;
                    }

                    break;
                }
                case SHOOT: {
                    glm::vec3 pos_of_bite = position;
                    pos_of_bite.x += cosf((90 + rotation) * 3.14 / 180.0f) * 0.4f;
                    pos_of_bite.z += sinf((90 + rotation) * 3.14 / 180.0f) * 0.4f;

                    glm::vec2 position2d(position.x, position.z);
                    glm::vec2 player_pos2D(player.position.x, player.position.z);
                    glm::vec2 pos_of_bite2d(pos_of_bite.x, pos_of_bite.z);

                    float mod1 = vec_mod2D(take_vector2D(position2d, pos_of_bite2d));
                    float mod2 = vec_mod2D(take_vector2D(position2d, player_pos2D));

                    if (shot) {
                        if (fabsf(mod1 - mod2) <= 0.4f) {
                            player.hit_points -= danage;
                            player.take_damage = true;
                        }
                        ufm.move_counter = 0;
                        a_states = MANEUVERING;
                        shot = false;
                    }
                    break;
                }
                case RUN: {
                    float angle = angle_btw_point_and_enemy(player.position);

                    angle *= (180.0f/M_PI);
                    angle  = (int) angle;

                    if (angle != 0.0f) {
                        int znak_x = znak_x_func(rotation);
                        int znak_z = znak_z_func(rotation);

                        if (znak_x * player.position.x < znak_x * lweiw.get_x(player.position.z) && znak_z * player.position.z > znak_z * lweiw.get_z(player.position.x))
                            rotation += angle;
                        else
                            rotation -= angle;
                        angle -= angle;
                    }

                    if (angle == 0.0f) {
                        x = std::ceil(position.x);
                        z = std::ceil(position.z);
                        x1 = cosf((90 + rotation) * 3.14 / 180.0f);
                        z1 = sinf((90 + rotation) * 3.14 / 180.0f);
                        if (!CollidesRect(x, z, position.x + x1 * speed, position.z, 0.4f, 0.4f)) {
                            position.x += x1 * speed;
                            ufm.flag_of_run.x += x1 * speed;
                        }
                        if (!CollidesRect(x, z, position.x, position.z + z1 * speed, 0.4f, 0.4f)) {
                            position.z += z1 * speed;
                            ufm.flag_of_run.y += z1 * speed;
                        }
                    }

                    if (vec_mod2D(take_vector2D({ufm.flag_of_run.x, ufm.flag_of_run.y}, {0.0f, 0.0f})) >= 6.0f) {
                        ufm.move_counter = 0;
                        ufm.flag_of_run.x = 0.0f;
                        ufm.flag_of_run.y = 0.0f;
                        a_states = MANEUVERING;
                        shot = false;
                    }
                    break;
                }
            }
            break;
        }
    }

    rotation = (i < 0) ? rotation - 360 : rotation;
}

void E_Dog::processing(Collisions &colls, std::chrono::duration<float> duration, Player &player, glm::mat4 &view, glm::mat4 &proj, const std::vector<Door*> &doors) {
    if (hit_points > 0)
        update(colls, duration, doors, player);
    else if (death_fact) {
        tex_x = 0;
        death_fact = false;
    }
    rotation = fmodf((rotation), 360.0f);

    draw(duration, player, view, proj);
}

void E_Dog::draw(std::chrono::duration<float> duration, const Player &player, glm::mat4 &view, glm::mat4 &proj) {
    enemy_tex->bind(GL_TEXTURE0);
    ps->useProgram();

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

    int tex_rotation = 22;

    int i = rotation / fabsf(rotation);
    rotation = (rotation < 0) ? 360 + rotation : rotation;

    v1 = {position.x, position.z};
    v1 = take_vector2D(v1, {v1.x + cosf((90 + rotation) * 3.14 / 180.0f),
                            v1.y + sinf((90 + rotation) * 3.14 / 180.0f)});

    angle_btw_vecs = angle_btw_point_and_enemy(p);

    //let's create a line equation
    Line line;

    glm::vec2 p1(position.x,
                 position.z);
    glm::vec2 p2(position.x + cosf((90 + rotation) * 3.14 / 180.0f),
                 position.z + sinf((90 + rotation) * 3.14 / 180.0f));
    line.calculate(p1, p2);

    int znak_x = znak_x_func(rotation);
    int znak_z = znak_z_func(rotation);

    rotation = (i < 0) ? rotation - 360 : rotation;

    if (znak_x * p.x < znak_x * line.get_x(p.z) && znak_z * p.z > znak_z * line.get_z(p.x)) {
        tex_rotation -= (angle_btw_vecs * 180 / 3.14f) + 44;
    } else {
        tex_rotation += (angle_btw_vecs * 180 / 3.14f);
    }
    // std::cout << tex_rotation << std::endl;

    if (hit_points <= 0) {
        if (tex_x < 4 && duration.count() - old_duration_enemy.count() > 0.16f) {
            tex_x++;
            old_duration_enemy = duration;
        }
        Vertical_plane::draw_once(-0.5f, 0.0f, 0, -0.5f, 0.0f, tex_x, 5, 8.0f, 6.0f);
    } else {
        if (a_states == SHOOT) {
            if (duration.count() - old_duration_shoot.count() >= duration_for_shooting) {
                tex_x = (tex_x >= 2) ? 0 : ++tex_x;
                old_duration_shoot = duration;
                shot = (tex_x == 2) ? true : shot;
            }
            Vertical_plane::draw_once(-0.5f, 0.0f, 0, -0.5f, 0.0f, tex_x, 4, 8.0f, 6.0f);
        } else if (fabsf(position.x - position_check.x) < 0.001 && fabsf(position.z - position_check.z) < 0.001) {
            Vertical_plane::draw_once(-0.5f, 0.0f, 0, -0.5f, 0.0f, std::ceil(tex_rotation / 45), 3, 8.0f, 6.0f);
        } else {
            float secs = (state == DUTY) ? 0.4f : 0.3f;
            secs = (state == ATTACK) ? 0.19f : secs;
            if (duration.count() - old_duration_enemy.count() > secs) {
                tex_y = (tex_y < 2) ? ++tex_y : 0;
                old_duration_enemy = duration;
            }
            Vertical_plane::draw_once(-0.5f, 0.0f, 0, -0.5f, 0.0f, std::ceil(tex_rotation / 45), tex_y, 8.0f, 6.0f);
            position_check = position;
        }
    }
}