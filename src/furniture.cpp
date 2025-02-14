#include "game.h"

const static String shaderDir = "resource/Shaders/";
String bindShader(std::string dir);

Furniture::Furniture(
        float xGap, float zGap, 
        int num_of_tex, 
        float x_count_of_objs, float y_count_of_objs,
        Collisions &col, 
        AVAILABILITY av, TYPE_OF_COLLISION toc,
        Texture *tex) 
{
    xGap *= -1;
    zGap *= -1;
    position = glm::vec3(-xGap, 0.0f, -zGap);
    map[0] = num_of_tex;
    this->x_count_of_objs = x_count_of_objs;
    this->y_count_of_objs = y_count_of_objs;
    this->num_of_tex = num_of_tex;
    this->tex = tex;
    
    float xGapfl = std::floor(xGap);
    float zGapfl = std::floor(zGap);
    
    if (av == TANGIBLE) {
        std::cout << "\nlkdsjf\n\n";
        Map *m = new Map({ map, 1, 1, 
                          -xGapfl + 0.0f,
                          -zGapfl + 0.0f,
                         -(xGapfl + 1.0f),
                         -(zGapfl + 1.0f),
                           xGapfl + 0.0f,
                           zGapfl + 0.0f,
                           1.0f });
        m->type = toc;
        col._piecesOfMap.push_back({m});
    }
    
    String vertexShaderSrc   = bindShader(shaderDir + "map/map.vert");
    String fragmentShaderSrc = bindShader(shaderDir + "map/map.frag");
    
    ps = new ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    
    tex->unbind();
    tex->uniform("tex0", *ps, 0);
    this->tex = tex;
}

void Furniture::draw(const Player &player, glm::mat4 &view, glm::mat4 &proj) {
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
    
    int tex_x =                       ((num_of_tex - 1) % x_count_of_objs);
    int tex_y = y_count_of_objs - 1 - ((num_of_tex - 1) / x_count_of_objs);
    
    Vertical_plane::draw_once(-0.5f, 0.0f, 0, -0.5f, 0.0f, tex_x, tex_y, x_count_of_objs, y_count_of_objs);
}

void Furniture::clear() {
    delete ps;
}