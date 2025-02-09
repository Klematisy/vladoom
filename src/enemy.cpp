// слава России zvzvz
#include <cmath>
#include <vector>
#include <random>
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

int Enemy::search_player_rec(const Map &map, 
                                   int *main_map, 
                                   std::vector<Point2> &solution, 
                                   std::vector<Point2> &main_array, 
                             const Point2 &p_p, 
                                   int depth, 
                                   int &min_depth) 
{
    size_t size = map.width * map.height;
    int element;
    
    Point2 point = main_array[depth++];
    
    if (point.x == p_p.x && point.z == p_p.z) {
        if (depth < min_depth) {
            min_depth = depth - 1;
            solution = main_array;
        }
        return 1;
    }
    
    if (depth >= min_depth) {
        return 0;
    }
    
    int copy_map[size];
    std::vector<Point2> copy_array;
    for (size_t i = 0; i < size; i++) {
        copy_map[i] = main_map[i];
    }
    copy_array = main_array;
    
    if (fmodf((point.x + 1), map.width) != 1) {
        element = point.z * map.width + point.x - 1;
        if (copy_map[element] == 0) {
            copy_map[element] = 1;
            copy_array.push_back({point.x - 1, point.z});
            search_player_rec(map, copy_map, solution, copy_array, p_p, depth, min_depth);
            copy_array.pop_back();
        }
    }

    if (fmodf((point.x + 1), map.width) != 0) {
        element = point.z * map.width + point.x + 1;
        if (copy_map[element] == 0) {
            copy_map[element] = 1;
            copy_array.push_back({point.x + 1, point.z});
            search_player_rec(map, copy_map, solution, copy_array, p_p, depth, min_depth);
            copy_array.pop_back();
        }
    }

    if (fmodf(point.z, map.height) != 0) {
        element = (point.z + 1) * map.width + point.x;
        if (copy_map[element] == 0) {
            copy_map[element] = 1;
            copy_array.push_back({point.x, point.z + 1});
            search_player_rec(map, copy_map, solution, copy_array, p_p, depth, min_depth);
            copy_array.pop_back();
        }
    }
    
    if (fmodf(point.z, map.height) != 1) {
        element = (point.z - 1) * map.width + point.x;
        if (copy_map[element] == 0) {
            copy_map[element] = 1;
            copy_array.push_back({point.x, point.z - 1});
            search_player_rec(map, copy_map, solution, copy_array, p_p, depth, min_depth);
            copy_array.pop_back();
        }
    }
    
    return 0;
}

int Enemy::search_player(const Map &map, const glm::vec3 &player_position) {
    way.clear();
    
    const int max_depth = 13;
    const size_t size = map.width * map.height;
    
    int copy_map[size];
    std::vector<Point2> solution;
    std::vector<Point2> main_array;
    
    for (size_t i = 0; i < size; i++) {
        copy_map[i] = map.obj[i];
    }
    
    int x = std::ceil(player_position.x + map.gap_x);
    int z = std::ceil(player_position.z + map.gap_z);
    
    Point2 p_p = {
        fabsf(x),
        fabsf(z)
    };
    
    x = std::ceil(position.x + map.gap_x);
    z = std::ceil(position.z + map.gap_z);
    
    Point2 e_p = {
        fabsf(x),
        fabsf(z)
    };
    
    main_array.push_back(e_p);
    copy_map[(int) (e_p.x + e_p.z * map.width)] = 1;
    
    int min_depth = max_depth;
    search_player_rec(map, copy_map, solution, main_array, p_p, 0, min_depth);
    
    while (!(solution.empty())) {
        way.emplace_back(solution[solution.size() - 1]);
        solution.pop_back();
    }
    
    if (way.empty())    state = DUTY;
    else                way.pop_back();
    
    return 0;
}

int znak_z_func(float rotation) {
    int znak_z;
    znak_z = (rotation >   0)  ? -1 :  1;
    znak_z = (rotation > 180)  ? 1  :  znak_z;
    return znak_z;
}

int znak_x_func(float rotation) {
    int znak_x;
    znak_x = (rotation >  90)  ? -1 :  1;
    znak_x = (rotation > 270)  ? 1  :  znak_x;
    return znak_x;
}

int Enemy::vision(Collisions &colls, const glm::vec3 &player_position) {
    float field_of_view    = 60.0f;
    float distance_of_view = 10.0f;

    glm::vec3 enemy_go_up(
        position.x + cosf((90 + rotation) * 3.14 / 180.0f), 
        0.0f,
        position.z + sinf((90 + rotation) * 3.14 / 180.0f)
    );
    
    glm::vec2 player = take_vector2D({position.x, position.z}, {player_position.x, player_position.z});
    glm::vec2 enemy_view = take_vector2D({position.x, position.z}, {enemy_go_up.x, enemy_go_up.z});
    
    float angle_btw_vecs = angle_between_vectors2D(player, enemy_view);
    angle_btw_vecs *= (180.0f / 3.14f);
    
    if (angle_btw_vecs <= field_of_view) {
        int x, z, x1, z1;
        int znak = -1;

        Line line;
        glm::vec2 v1(position.x, 
                     position.z);
        glm::vec2 v2(enemy_go_up.x, 
                     enemy_go_up.z);
        line.calculate(v2, v1);
        int znak_x, znak_z;
        glm::vec3 view = position;
        
        znak_x = znak_x_func(rotation);
        znak_z = znak_z_func(rotation);
        
        if ((znak_x * player_position.x <= znak_x * line.get_x(player_position.z) && znak_z * player_position.z >= znak_z * line.get_z(player_position.x))) {
            znak = 1;
        }
        
        bool loop = true;
        
        x = fabsf(std::ceil(view.x));
        z = fabsf(std::ceil(view.z));

        while (loop) {
            view.x += cosf(((90 + rotation + znak * angle_btw_vecs) * 3.14 / 180.0f)) * 0.2f;
            view.z += sinf(((90 + rotation + znak * angle_btw_vecs) * 3.14 / 180.0f)) * 0.2f;
            
            if (fabsf(view.x - player_position.x) <= 0.2f && fabsf(view.z - player_position.z) <= 0.2f) {
                break;
            }
            if (vec_mod2D(take_vector2D({position.x, position.z}, {view.x, view.z})) > distance_of_view) {
                return 1;
                break;
            }
            
            for (const Map *path_of_map : colls._piecesOfMap) {
                if (!inObj(*path_of_map, view)) continue;
                
                x = fabsf(std::ceil(view.x + path_of_map->gap_x));
                z = fabsf(std::ceil(view.z + path_of_map->gap_z));
                
                if (path_of_map->obj[x + z * path_of_map->width] > 0) {
                    loop = false;
                }
            }
        }
        state = (!loop) ? state : ATTACK;
    }
    
    return 0;
}

float Enemy::angle_btw_point_and_enemy(const glm::vec3 &point) {
    glm::vec2 point1(position.x, position.z);
    glm::vec2 point2(position.x + cosf((90 + rotation) * 3.14 / 180.0f),
                     position.z + sinf((90 + rotation) * 3.14 / 180.0f));
    
    glm::vec2 v1 = take_vector2D(point1, point2);
    glm::vec2 v2 = take_vector2D({position.x, position.z}, {point.x, point.z});
    return angle_between_vectors2D(v1, v2);
}

void Enemy::update(Collisions &colls, 
                   std::chrono::duration<float> duration, 
             const std::vector<Door*> &doors, 
             const Entity &player)
{
    map = check_collisions(*this, colls);
    int i = rotation / fabsf(rotation);
    rotation = (rotation < 0) ? 360 + rotation : rotation;
    
    float speed = 0.005f;
    int x = std::ceil(position.x);
    int z = std::ceil(position.z);
    
    float x1 = cosf((90 + rotation) * 3.14 / 180.0f);
    float z1 = sinf((90 + rotation) * 3.14 / 180.0f);
    
    if (state != ATTACK) vision(colls, player.position);
    
    switch (state) {
        case DUTY: {
            ///*
            if ((int) fabsf(rotation) % turn == 0) {
                if (!CollidesRect(x, z, position.x + x1 * speed, position.z, 0.4f, 0.4f)) {
                    position.x += x1 * speed;
                }
                if (!CollidesRect(x, z, position.x, position.z + z1 * speed, 0.4f, 0.4f)) {
                    position.z += z1 * speed;
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
            //*/
            break;
        }
        case SEARCH: {
            speed = 0.01f;
            Point2 point = way.back();
            
            int x = abs(std::ceil(position.x));
            int z = abs(std::ceil(position.z));
            
            point.x += 0.5f;
            point.z += 0.5f;
            
            if (fabsf(point.x - fabsf(position.x)) < 0.1f && fabsf(point.z - fabsf(position.z)) < 0.1f) {                
                way.pop_back();
                if (way.empty()) {
                    state = DUTY;
                    break;
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
                glm::vec2 p1(position.x, position.z);
                glm::vec2 p2(
                    position.x + cosf((90 + rotation) * 3.14 / 180.0f), 
                    position.z + sinf((90 + rotation) * 3.14 / 180.0f)
                );
                Line line;
                line.calculate(p1, p2);
                
                int znak_x = znak_x_func(rotation);
                int znak_z = znak_z_func(rotation);
                
                if (znak_x * point.x < znak_x * line.get_x(point.z) && znak_z * point.z > znak_z * line.get_z(point.x)) {
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
            if (duration.count() - old_duration_atack.count() >= 3.0f) {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> disti(0, 2);
                int random_number = disti(gen);
                // int random_number = 0;
                switch (random_number) {
                    case 0: a_states = MANEUVERING;    
                    break;
                    case 1: a_states = RUN;
                    break;
                    case 2: a_states = SHOOT;
                    break;
                }
                old_duration_atack = duration;
            }
            
            float mod = vec_mod2D(take_vector2D({position.x, position.z}, {player.position.x, player.position.z}));
            
            if (mod <= 1.0f) {
                a_states = SHOOT;
            }
            
            switch (a_states) {
                case MANEUVERING: {
                    speed = 0.01f;
                    float mod = vec_mod2D(take_vector2D({flag_of_maneuvering.x, flag_of_maneuvering.z}, {position.x, position.z}));
                    float angle = angle_btw_point_and_enemy(player.position);
                    angle *= (180.0f/M_PI);
                    angle = (int) angle;
                    
                    // std::cout << mod << " " << angle << std::endl;
                    if (mod > 0.4f) {
                        Line line1;
                        line1.calculate({player.position.x, player.position.z}, 
                                       {player.position.x + cosf((90 + player.rotation) * 3.14 / 180.0f), 
                                        player.position.z + sinf((90 + player.rotation) * 3.14 / 180.0f)});
                        
                        int znak_x = znak_x_func(player.rotation);
                        int znak_z = znak_z_func(player.rotation);
                        
                        rotation += 3.0f * maneuvering;
                        if (angle / 24 == 1 || angle / 25 == 1 || angle / 26 == 1 || angle / 27 == 1) {
                            if (znak_x * (position.x + x1) <= znak_x * line1.get_x(position.z + z1) && znak_z * (position.z + z1) >= znak_z * line1.get_z((position.x + x1))) {
                                // std::cout << "RIGHT" << std::endl;
                                if (maneuvering < 0) {
                                    flag_of_maneuvering = position;
                                    maneuvering *= -1;
                                }
                            } else {
                                // std::cout << "LEFT" << std::endl;
                                if (maneuvering > 0) {
                                    flag_of_maneuvering = position;
                                    maneuvering *= -1;
                                }
                            }
                        }
                        
                    } else {
                        x = std::ceil(position.x);
                        z = std::ceil(position.z);
                        if (!CollidesRect(x, z, position.x + x1 * speed, position.z, 0.4f, 0.4f)) {
                            position.x += x1 * speed;
                        }
                        if (!CollidesRect(x, z, position.x, position.z + z1 * speed, 0.4f, 0.4f)) {
                            position.z += z1 * speed;
                        }
                    }
                    break;
                }
                case RUN: {
                    speed = 0.01f;
                    float angle = angle_btw_point_and_enemy(player.position);
                    angle *= (180.0f/M_PI);
                    angle = (int) angle;

                    if (angle != 0) {
                        glm::vec2 p1(position.x, position.z);
                        glm::vec2 p2(
                            position.x + cosf((90 + rotation) * 3.14 / 180.0f), 
                            position.z + sinf((90 + rotation) * 3.14 / 180.0f)
                        );
                        Line line;
                        line.calculate(p1, p2);
                        
                        int znak_x = znak_x_func(rotation);
                        int znak_z = znak_z_func(rotation);
                        
                        if (znak_x * player.position.x <= znak_x * line.get_x(player.position.z) && znak_z * player.position.z >= znak_z * line.get_z(player.position.x)) {
                            rotation += (angle >= 5.0f) ? 3.0f : angle;
                            angle    -= (angle >= 5.0f) ? 3.0f : angle;
                        } else {    
                            rotation -= (angle >= 5.0f) ? 3.0f : angle;
                            angle    += (angle >= 5.0f) ? 3.0f : angle;
                        }
                    }
                    
                    if (angle == 0) {
                        x = std::ceil(position.x);
                        z = std::ceil(position.z);
                        if (!CollidesRect(x, z, position.x + x1 * speed, position.z, 0.4f, 0.4f)) {
                            position.x += x1 * speed;
                        }
                        if (!CollidesRect(x, z, position.x, position.z + z1 * speed, 0.4f, 0.4f)) {
                            position.z += z1 * speed;
                        }
                    }
                    break;
                }
                case SHOOT: {
                    
                    break;
                }
            }
        }
        break;
    }
    
    rotation = (i < 0) ? rotation - 360 : rotation;
    if (fabsf(position.x - position_check.x) < 0.0000001 || fabsf(position.z - position_check.z) < 0.0000001) {
        for (Door *door : doors) {
            door->door_cheking(position, rotation);
        }
    }
}

void Enemy::processing(Collisions &colls, std::chrono::duration<float> duration, const Player &player, glm::mat4 &view, glm::mat4 &proj, const std::vector<Door*> &doors) {
    if (hit_points > 0)
        update(colls, duration, doors, player);
    rotation = fmodf((rotation), 360.0f);
    draw(duration, player, view, proj);
}

void Enemy::draw(std::chrono::duration<float> duration, const Player &player, glm::mat4 &view, glm::mat4 &proj) {
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
        if (tex_x < 5 && duration.count() - old_duration_enemy.count() > 0.16f) {
            tex_x++;
            old_duration_enemy = duration;
        }
        Vertical_plane::draw_once(-0.5f, 0.0f, 0, -0.5f, 0.0f, tex_x, 6, 8.0f, 7.0f);
    } else {
        if (fabsf(position.x - position_check.x) < 0.001 && fabsf(position.z - position_check.z) < 0.001) {
            Vertical_plane::draw_once(-0.5f, 0.0f, 0, -0.5f, 0.0f, std::ceil(tex_rotation / 45), 4, 8.0f, 7.0f);
        } else {
            float secs = (state == DUTY) ? 0.4f : 0.3f;
            secs = (state == ATTACK) ? 0.19f : secs;
            if (duration.count() - old_duration_enemy.count() > secs) {
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
