#include "libs.h"
#include "game.h"
#include "VPlane.h"
#include <random>

const static String shaderDir = "resource/Shaders/";
String bindShader(std::string dir);
static auto start = std::chrono::high_resolution_clock::now();

void input_pause(GLFWwindow *window, GAME_STATE &game_s, uint &menu_counter);
void input_game(GAME_STATE &game_s,
                std::vector<S_Door*> &secret_doors,
                std::vector<Door*> &doors,
                Collisions &colls,
                Player &player, std::vector<Enemy*> &enemies,
                GLFWwindow *window,
                std::chrono::duration<float> duration,
                std::chrono::duration<float> &old_duration_shoot);
void input_pause(GAME_STATE &game_s, uint &menu_counter);

static float color(int i) { return i / 255.0f; }

GAME_STATE stage1(GLFWwindow *window, Player &player, Player player_copy, GAME_STATE &game_s) {
    /*---------------------------------------main code!---------------------------------------*/
    auto a = std::chrono::high_resolution_clock::now();
    
    String   vertexShaderSrc = bindShader(shaderDir + "map/map.vert");
    String fragmentShaderSrc = bindShader(shaderDir + "map/map.frag");
    ProgramShader map_shader = ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    
    vertexShaderSrc   = bindShader(shaderDir + "map1/map.vert");
    fragmentShaderSrc = bindShader(shaderDir + "map1/map.frag");
    ProgramShader    pick_ps(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    ProgramShader  damage_ps(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    ProgramShader  black_ps(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    
    Texture *pick_tex = new Texture("resource/images/pick_up.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    pick_tex->unbind();
    pick_tex->uniform("tex0", pick_ps, 0);
    
    Texture *damage_tex = new Texture("resource/images/damage.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    damage_tex->unbind();
    damage_tex->uniform("tex0", damage_ps, 0);
    
    Texture *black_tex = new Texture("resource/images/black.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    black_tex->unbind();
    black_tex->uniform("tex0", black_ps, 0);
    
    Texture *non_bind = new Texture("resource/images/non-blocking-objs.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    Texture *bind     = new Texture("resource/images/blocking-objs.png",     GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    Texture *Walls    = new Texture("resource/images/atlas.png",             GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    Walls->unbind();
    Walls->uniform("tex0", map_shader, 0);

    Collisions cWalls;

    int *jail = new int[] {
        0, 15, 15, 15, 15, 15, 15,  0, 15, 15, 15, 15, 15, 15, 0,
        15, 0,  0,  0,  0, 15,  0,  0,  0, 15,  0,  0,  0,  0, 15,
        15, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15,
        15, 0,  0,  0,  0, 15,  0,  0,  0, 15,  0,  0,  0,  0, 15,
        15, 0,  0,  0,  0, 15,  0,  0,  0, 15,  0,  0,  0,  0, 15,
        0, 15, 15, 15, 15, 15,  0,  0,  0, 15, 15, 15, 15,  15, 0,
        0, 15,  0,  0,  0, 15,  0,  0,  0, 15,  0,  0,  0,  15, 0,
        0, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  15, 0,
        0, 15,  0,  0,  0, 15,  0,  0,  0, 15,  0,  0,  0,  15, 0,
        0, 15, 15, 15, 15, 15,  0,  0,  0, 15, 15, 15, 15,  15, 0,
        15, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15,
        15, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15,
        15, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15,
        0,  9, 15, 15,  9, 15, 15, 13, 15, 15,  9, 15, 15,  9, 0
    };
    
    int *hall = new int[] {
        15, 15, 0, 15, 15,
        15, 0,  0,  0, 15,
        15, 0,  0,  0, 15,
        15, 0,  0,  0, 15,
        15, 0,  0,  0, 15,
        15, 0,  0,  0, 15,
        15, 0,  0,  0, 15,
        15, 0,  0,  0, 15,
        15, 0,  0,  0, 15,
        15, 0,  0,  0, 15,
        15, 0,  0,  0, 15,
        15, 0,  0,  0, 15,
    };

    int *central_hall = new int[] {
         2, 1, 1, 1, 5, 1, 0, 0, 0, 0, 0, 1, 5, 1, 1, 1,  1,
         2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  2,
        12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12,
         2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,
         2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,
         2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,
        12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12,
         2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  2,
         2, 1, 7, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 7, 1, 1,  1
    };
    
    int *wooden_thing = new int[] { // w: 18; h: 22;
         0, 23, 23, 23, 19, 23, 23, 23, 23, 23, 19, 23, 23, 23,  0,  0,  0,  0,
         0, 24,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 24,  0,  0,  0,  0,
         0, 20,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 20, 23, 23, 23, 23,
         0, 24,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 24,  0,  0,  0, 24,
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 20,
         0, 24,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 24,  0,  0,  0, 24,
         0, 22,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 22, 23, 23, 23, 23,
         0, 24,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 24,  0,  0,  0,  0,
         0, 23, 23, 23, 19, 23, 23,  0, 23, 23, 19, 23, 23, 23,  0,  0,  0,  0,
         0,  0,  0,  0,  0, 24,  0,  0,  0, 24,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0, 24,  0,  0,  0, 24,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0, 22,  0,  0,  0, 22,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0, 24,  0,  0,  0, 24,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0, 24,  0,  0,  0, 24,  0,  0,  0,  0,  0,  0,  0,  0,
        24, 24, 24, 24, 24, 24,  0,  0,  0, 24, 24, 24,  0,  0,  0,  0,  0,  0,
        24,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 24,  0,  0,  0,  0,  0,  0,
        24,  0,  0, 24, 24, 24,  0,  0,  0, 24, 24, 24,  0,  0,  0,  0,  0,  0,
        24,  0,  0, 24, 23, 24,  0,  0,  0, 24,  0,  0,  0,  0,  0,  0,  0,  0,
        24,  0,  0, 24, 23, 24,  0,  0,  0, 24,  0,  0,  0,  0,  0,  0,  0,  0,
        23, 23, 23, 23, 23, 20,  0,  0,  0, 20,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0, 24,  0,  0,  0, 24,  0,  0,  0,  0,  0,  0,  0,  0,
         0,  0,  0,  0,  0, 23, 19,  0, 19, 23,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    
    int *kennel = new int[] { // w:20 h: 19;
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16,  0,  0,  0,  0,  0,  0,  0,  0, 16,
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16,  0,  0,  0,  0,  0,  0,  0,  0, 16,
        15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 16,  0,  0,  0,  0,  0,  0,  0,  0, 16,
        15,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16,  0,  0,  0,  0,  0,  0,  0,  0, 16,
         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10,
        15,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16,  0,  0,  0,  0,  0,  0,  0,  0, 16,
        15, 15, 15,  0,  0,  0,  0, 15, 15, 15, 16,  0,  0,  0,  0,  0,  0,  0,  0, 16,
         0,  0,  0, 16,  0,  0, 15,  0,  0,  0, 16,  0,  0,  0,  0,  0,  0,  0,  0, 16,
         0,  0,  0, 16,  0,  0, 15,  0,  0,  0, 16,  0,  0,  0,  0,  0,  0,  0,  0, 16,
         0,  0,  0, 16,  0,  0, 15,  0,  0,  0,  0, 15, 15,  0, 15, 15,  0, 15, 15, 15,
         0,  0,  0, 16,  0,  0, 15,  0,  0,  0,  0,  0,  0, 15,  0,  0, 15,  0,  0,  0,
         0,  0,  0, 16,  0,  0, 15,  0,  0, 16,  0, 16,  0, 16,  0, 16,  0,  0,  0,  0,
         0,  0,  0, 16,  0,  0, 15, 15, 16,  0, 16,  0, 16,  0, 16,  0, 16, 16,  0,  0,
         0,  0,  0, 16,  0,  0,  0, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16,  0,  0,
         0,  0,  0, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10,  0,  0,
         0,  0,  0, 16,  0,  0,  0, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16,  0,  0,
         0,  0,  0, 16, 15, 15, 15, 15, 16,  0, 16,  0, 16,  0, 16,  0, 16, 16,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0,  0, 16,  0, 16,  0, 16,  0, 16,  0,  0,  0,  0
    };
    
    int *part_of_rockmap = new int[] { //w: 23; h: 14;
         2,  2,  2,  2,  2,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         2,  0,  0,  0,  0,  2,  0,  0,  0,  0,  0,  0,  2,  1,  1,  1,  1,  1,  1,  5,  1,  1,  1,
         2,  0,  0,  0,  0,  2,  0,  0,  0,  0,  0,  0,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         2,  0,  0,  0,  0,  0,  2,  0,  0,  0,  0,  0,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         2,  0,  0,  0,  0,  0,  2,  0,  0,  0,  0,  0,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         2,  1, 11,  1,  1,  0,  1,  1, 11,  1,  1,  0,  2,  0,  0,  0,  1,  1,  1,  5,  1,  1,  1,
         2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  0,  2,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,
         6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6,  1,  2,  0,  0,  0,  1,  2,  2,  0,  0,  0,  0,
         2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  0,  0,  0,  0,  0,  0,  0,  2,  0,  0,  0,  0,
         2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  0,  0,  0,  0,
         2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  0,  0,  0,  0,  0,  0,  0,  2,  0,  0,  0,  0,
         6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6,  1,  1,  1, 11,  1,  1,  1,  2,  0,  0,  0,  0,
         2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
         2,  1, 11,  1,  1,  0,  1,  1, 11,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    
    int *end_of_map = new int[] { //w: 27; h: 31;
        1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        2, 1, 0, 1, 1, 0, 0, 0, 6, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        2, 0, 0, 0, 2, 1, 1, 1, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        2, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        2, 0, 0, 0, 2, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        6, 0, 0, 0, 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        2, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        2, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        2, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        2, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        2, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        8, 0, 0, 0, 8, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        2, 0, 0, 0, 2, 1, 1, 1, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        2, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        2, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        2, 0, 0, 0, 2, 2, 2, 2, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        2, 0, 0, 0, 2, 1, 1, 1, 1, 0, 0, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1,11, 1, 1,  1, 0, 0,
        2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 12, 41,  1,
        2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 42,
        2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 12, 41,  1,
        2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1,11, 1, 1,  1, 0, 0,
    }; 
    
    int *last_secret = new int[] { //w: 7; h: 12;
        0,41, 6, 0, 0, 2, 0, 0, 0, 0, 0, 2,
       42, 0, 0, 0, 0, 2, 0, 0, 1, 0, 2, 0,
        0,41, 6, 0, 0, 0, 0, 0, 1, 1, 0, 0,
        0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0,
    };

    player.score = 0;
    player.ammo  = 8;
    
    std::vector<Furniture*> static_furnitures;
    {
        static_furnitures.push_back(    new Furniture(  -7.5f,  -7.5f, 4, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        static_furnitures.push_back(    new Furniture(  -7.5f,  -2.5f, 4, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        static_furnitures.push_back(    new Furniture(  -7.5f, -11.5f, 4, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        static_furnitures.push_back(    new Furniture( -11.5f, -11.5f, 4, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        static_furnitures.push_back(    new Furniture(  -3.5f, -11.5f, 4, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        static_furnitures.push_back(    new Furniture( -12.5f,  -7.5f, 6, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        static_furnitures.push_back(    new Furniture(  -1.5f,  -1.5f, 6, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        static_furnitures.push_back(    new Furniture( -11.5f,  -2.5f, 3, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        
        static_furnitures.push_back(    new Furniture( -7.5f,    1.5f, 4, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        static_furnitures.push_back(    new Furniture( -7.5f,    9.5f, 4, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        static_furnitures.push_back(    new Furniture( -7.5f,    5.5f, 4, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        
        static_furnitures.push_back(    new Furniture(  -7.5f,  16.5f, 2, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        static_furnitures.push_back(    new Furniture( -12.5f,  16.5f, 2, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        static_furnitures.push_back(    new Furniture(  -2.5f,  16.5f, 2, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        static_furnitures.push_back(    new Furniture(  -7.5f,  23.5f, 4, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        static_furnitures.push_back(    new Furniture(  -7.5f,  27.5f, 4, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        static_furnitures.push_back(    new Furniture(  -7.5f,  31.5f, 4, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        static_furnitures.push_back(    new Furniture(  -7.5f,  38.5f, 2, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        static_furnitures.push_back(    new Furniture( -32.5f,   5.5f, 7, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        static_furnitures.push_back(    new Furniture( -31.5f,  20.5f, 1, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        
        static_furnitures.push_back(    new Furniture(  16.5f,  26.5f, 4, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        static_furnitures.push_back(    new Furniture(  16.5f,  23.5f, 4, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        
        static_furnitures.push_back(    new Furniture(  14.5f,  18.5f, 4, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        static_furnitures.push_back(    new Furniture(  14.5f,  14.5f, 4, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        static_furnitures.push_back(    new Furniture(  18.5f,  14.5f, 4, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        static_furnitures.push_back(    new Furniture(  18.5f,  18.5f, 4, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        
        static_furnitures.push_back(    new Furniture(  24.5f,  28.5f, 4, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        
        static_furnitures.push_back(    new Furniture(  20.5f,  23.5f, 4, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        
        static_furnitures.push_back(    new Furniture(  24.5f,  24.5f, 4, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        static_furnitures.push_back(    new Furniture(  24.5f,  20.5f, 4, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        static_furnitures.push_back(    new Furniture(  24.5f,  11.5f, 4, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        static_furnitures.push_back(    new Furniture(  24.5f,   6.5f, 4, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
        
        static_furnitures.push_back(    new Furniture(  20.5f,   7.5f, 4, 4, 4, cWalls, IMAGINARY,   SHOOTABLE,   non_bind));
    }
        
    std::vector<Furniture*> non_static_furnitures;
    {
        non_static_furnitures.push_back(new Furniture( -0.5f,  13.5f,  8, 4, 5, cWalls, TANGIBLE,    SHOOTABLE,   bind));
        non_static_furnitures.push_back(new Furniture( -0.5f,  19.5f,  8, 4, 5, cWalls, TANGIBLE,    SHOOTABLE,   bind));
        non_static_furnitures.push_back(new Furniture(-14.5f,  19.5f,  8, 4, 5, cWalls, TANGIBLE,    SHOOTABLE,   bind));
        non_static_furnitures.push_back(new Furniture(-14.5f,  13.5f,  8, 4, 5, cWalls, TANGIBLE,    SHOOTABLE,   bind));
        non_static_furnitures.push_back(new Furniture(-15.5f,  17.5f,  8, 4, 5, cWalls, TANGIBLE,    SHOOTABLE,   bind));
        non_static_furnitures.push_back(new Furniture(-15.5f,  15.5f,  8, 4, 5, cWalls, TANGIBLE,    SHOOTABLE,   bind));
        non_static_furnitures.push_back(new Furniture( -0.5f,  13.5f,  8, 4, 5, cWalls, TANGIBLE,    SHOOTABLE,   bind));
        non_static_furnitures.push_back(new Furniture( -0.5f,  13.5f,  8, 4, 5, cWalls, TANGIBLE,    SHOOTABLE,   bind));
        non_static_furnitures.push_back(new Furniture( -5.5f,  20.5f,  8, 4, 5, cWalls, TANGIBLE,    SHOOTABLE,   bind));
        non_static_furnitures.push_back(new Furniture( -9.5f,  20.5f,  8, 4, 5, cWalls, TANGIBLE,    SHOOTABLE,   bind));
        non_static_furnitures.push_back(new Furniture(-10.5f,  27.5f, 11, 4, 5, cWalls, TANGIBLE,    SHOOTABLE,   bind));
        
        non_static_furnitures.push_back(new Furniture( -4.5f,  40.5f,  2, 4, 5, cWalls, TANGIBLE,    UNSHOOTABLE, bind));
        non_static_furnitures.push_back(new Furniture( -7.5f,  40.5f,  2, 4, 5, cWalls, TANGIBLE,    UNSHOOTABLE, bind));
        non_static_furnitures.push_back(new Furniture(-10.5f,  40.5f,  2, 4, 5, cWalls, TANGIBLE,    UNSHOOTABLE, bind));
        
        non_static_furnitures.push_back(new Furniture(-12.5f,  41.5f,  9, 4, 5, cWalls, TANGIBLE,    UNSHOOTABLE, bind));
        non_static_furnitures.push_back(new Furniture( -2.5f,  41.5f,  9, 4, 5, cWalls, TANGIBLE,    UNSHOOTABLE, bind));
        
        non_static_furnitures.push_back(new Furniture(-29.5f,  11.5f, 16, 4, 5, cWalls, TANGIBLE,    UNSHOOTABLE, bind));
        non_static_furnitures.push_back(new Furniture(-32.5f,  11.5f, 17, 4, 5, cWalls, TANGIBLE,    UNSHOOTABLE, bind));
        non_static_furnitures.push_back(new Furniture(-34.5f,  19.5f, 15, 4, 5, cWalls, TANGIBLE,    UNSHOOTABLE, bind));
        non_static_furnitures.push_back(new Furniture(-34.5f,  20.5f, 15, 4, 5, cWalls, TANGIBLE,    UNSHOOTABLE, bind));
        non_static_furnitures.push_back(new Furniture(-33.5f,  20.5f, 15, 4, 5, cWalls, TANGIBLE,    UNSHOOTABLE, bind));
        non_static_furnitures.push_back(new Furniture(-32.5f,  20.5f, 15, 4, 5, cWalls, TANGIBLE,    UNSHOOTABLE, bind));
        non_static_furnitures.push_back(new Furniture(-29.5f,  14.5f, 10, 4, 5, cWalls, TANGIBLE,    UNSHOOTABLE, bind));
        non_static_furnitures.push_back(new Furniture(-32.5f,  14.5f, 10, 4, 5, cWalls, TANGIBLE,    UNSHOOTABLE, bind));
        
        non_static_furnitures.push_back(new Furniture( 16.5f,  32.5f,  2, 4, 5, cWalls, TANGIBLE,    UNSHOOTABLE, bind));
        non_static_furnitures.push_back(new Furniture( 15.5f,  35.5f,  6, 4, 5, cWalls, TANGIBLE,    UNSHOOTABLE, bind));
        non_static_furnitures.push_back(new Furniture( 17.5f,  35.5f,  6, 4, 5, cWalls, TANGIBLE,    UNSHOOTABLE, bind));
        non_static_furnitures.push_back(new Furniture( 13.5f,  34.5f,  3, 4, 5, cWalls, TANGIBLE,    UNSHOOTABLE, bind));
        non_static_furnitures.push_back(new Furniture( 13.5f,  30.5f,  3, 4, 5, cWalls, TANGIBLE,    UNSHOOTABLE, bind));
        non_static_furnitures.push_back(new Furniture( 19.5f,  30.5f,  3, 4, 5, cWalls, TANGIBLE,    UNSHOOTABLE, bind));
        non_static_furnitures.push_back(new Furniture( 19.5f,  34.5f,  3, 4, 5, cWalls, TANGIBLE,    UNSHOOTABLE, bind));
        non_static_furnitures.push_back(new Furniture( 20.5f,  32.5f, 18, 4, 5, cWalls, TANGIBLE,    UNSHOOTABLE, bind));
        
        non_static_furnitures.push_back(new Furniture( 13.5f,  19.5f,  8, 4, 5, cWalls, TANGIBLE,    UNSHOOTABLE, bind));
        non_static_furnitures.push_back(new Furniture( 13.5f,  13.5f,  8, 4, 5, cWalls, TANGIBLE,    UNSHOOTABLE, bind));
        non_static_furnitures.push_back(new Furniture( 19.5f,  13.5f,  8, 4, 5, cWalls, TANGIBLE,    UNSHOOTABLE, bind));
        non_static_furnitures.push_back(new Furniture( 19.5f,  19.5f,  8, 4, 5, cWalls, TANGIBLE,    UNSHOOTABLE, bind));
        
        non_static_furnitures.push_back(new Furniture( 23.5f,  29.5f, 15, 4, 5, cWalls, TANGIBLE,    UNSHOOTABLE, bind));
        
        non_static_furnitures.push_back(new Furniture( 19.5f,   8.5f,  1, 4, 5, cWalls, TANGIBLE,    UNSHOOTABLE, bind));
    }
    
    std::vector<Item*> items;
    {
        items.push_back(new Item(-7.5, -5.5, 2, 500, player, GUN));
    }
    
    std::vector<Enemy*> enemies;
    {
        enemies.push_back(new Enemy(glm::vec3(-4.5f, 0.0f,  -7.5f), 90.0f,   0,  0, "Enemy-015.png", RIGHT_TURN));
        // enemies.push_back(new Enemy(glm::vec3(-9.5f, 0.0f, -11.5f), 90.0f, 100, 25, "Enemy-015.png", RIGHT_TURN));
        // enemies.push_back(new E_Dog(glm::vec3(-9.5f, 0.0f, -11.5f), 90.0f, 100, 25, "Enemy_dog.png"));
    }
    
    std::vector<Cube*> parts_of_map;
    {
        parts_of_map.push_back(new Cube(           jail, 15, 14, 1.0f,   0.0f,   0.0f, 0.0f, cWalls, 6.0f, 19.0f));
        parts_of_map.push_back(new Cube(           hall,  5, 12, 1.0f,  -5.0f,  12.0f, 0.0f, cWalls, 6.0f, 19.0f));
        parts_of_map.push_back(new Cube(   central_hall, 17,  9, 1.0f,   1.0f,  21.0f, 0.0f, cWalls, 6.0f, 19.0f));
        parts_of_map.push_back(new Cube(         kennel, 20, 19, 1.0f, -16.0f,  22.0f, 0.0f, cWalls, 6.0f, 19.0f));
        parts_of_map.push_back(new Cube(   wooden_thing, 18, 22, 1.0f,   0.0f,  43.0f, 0.0f, cWalls, 6.0f, 19.0f));
        parts_of_map.push_back(new Cube(part_of_rockmap, 23, 14, 1.0f,  22.0f,  42.0f, 0.0f, cWalls, 6.0f, 19.0f));
        parts_of_map.push_back(new Cube(     end_of_map, 27, 31, 1.0f,  27.0f,  31.0f, 0.0f, cWalls, 6.0f, 19.0f));
        parts_of_map.push_back(new Cube(    last_secret, 12,  7, 1.0f,  18.0f,   0.0f, 0.0f, cWalls, 6.0f, 19.0f));
    }
    
    std::vector<Door*> doors;
    {
        doors.emplace_back(new Door( -5.0f, -2.0f,  0.0f, cWalls, *Walls, STANDART));
        doors.emplace_back(new Door( -9.0f, -2.0f,  0.0f, cWalls, *Walls, STANDART));
        doors.emplace_back(new Door( -5.0f, -7.0f,  0.0f, cWalls, *Walls, STANDART));
        doors.emplace_back(new Door( -9.0f, -7.0f,  0.0f, cWalls, *Walls, STANDART));
        doors.emplace_back(new Door( -7.0f,  0.0f, 90.0f, cWalls, *Walls, STANDART));
        doors.emplace_back(new Door( -7.0f, 22.0f, 90.0f, cWalls, *Walls, STANDART));
        doors.emplace_back(new Door(-16.0f, 17.0f,  0.0f, cWalls, *Walls, STANDART));
        doors.emplace_back(new Door( -7.0f, 35.0f, 90.0f, cWalls, *Walls, STANDART));
        doors.emplace_back(new Door(-13.0f, 39.0f,  0.0f, cWalls, *Walls, STANDART));
        doors.emplace_back(new Door(-23.0f,  7.0f,  0.0f, cWalls, *Walls, STANDART));
        doors.emplace_back(new Door(-26.0f, 17.0f,  0.0f, cWalls, *Walls, STANDART));
        doors.emplace_back(new Door( -7.0f, 12.0f, 90.0f, cWalls, *Walls, STANDART));
        doors.emplace_back(new Door( -1.0f, 39.0f,  0.0f, cWalls, *Walls, STANDART));
        doors.emplace_back(new Door( 12.0f, 33.0f,  0.0f, cWalls, *Walls, STANDART));
        doors.emplace_back(new Door( 17.0f, 29.0f, 90.0f, cWalls, *Walls, STANDART));
        doors.emplace_back(new Door( 17.0f, 22.0f, 90.0f, cWalls, *Walls, STANDART));
        doors.emplace_back(new Door( 17.0f, 12.0f, 90.0f, cWalls, *Walls, STANDART));
        doors.emplace_back(new Door( 22.0f, 17.0f,  0.0f, cWalls, *Walls, STANDART));
        doors.emplace_back(new Door( 10.0f,  3.0f,  0.0f, cWalls, *Walls, STANDART));
        doors.emplace_back(new Door( 25.0f, 27.0f, 90.0f, cWalls, *Walls, STANDART));
        doors.emplace_back(new Door(  3.0f,  3.0f,  0.0f, cWalls, *Walls, ELEVATOR));
        doors.emplace_back(new Door( 16.0f, -1.0f,  0.0f, cWalls, *Walls, ELEVATOR));
    }
    
    std::vector<S_Door*> secret_doors;
    {
        secret_doors.push_back(new S_Door(  -3.0f, 28.0f, 270, 20, cWalls));
        secret_doors.push_back(new S_Door(  17.0f, 37.0f, 360,  7, cWalls));
        secret_doors.push_back(new S_Door(   9.0f,  1.0f, 180,  1, cWalls));
        secret_doors.push_back(new S_Door(  10.0f,  0.0f, 270,  2, cWalls));
        secret_doors.push_back(new S_Door(  14.0f, -3.0f, 180,  1, cWalls));
    }
    
    std::vector<Horizontal_plane> floors;
    {
        floors.emplace_back(jail, 15, 14,  0.0f, 0.0f,  0.0f, 111, 6.0f, 19.0f);
        floors.emplace_back(jail, 15, 14,  0.0f, 1.0f,  0.0f, 112, 6.0f, 19.0f);
        floors.emplace_back(hall,  5, 12, -5.0f, 0.0f, 12.0f, 111, 6.0f, 19.0f);
        floors.emplace_back(hall,  5, 12, -5.0f, 1.0f, 12.0f, 112, 6.0f, 19.0f);
        
        floors.emplace_back(   central_hall, 17,  9,   1.0f,  0.0f,  21.0f, 111, 6.0f, 19.0f);
        floors.emplace_back(   central_hall, 17,  9,   1.0f,  1.0f,  21.0f, 112, 6.0f, 19.0f);
        floors.emplace_back(   wooden_thing, 18, 22,   0.0f,  0.0f,  43.0f, 111, 6.0f, 19.0f);
        floors.emplace_back(   wooden_thing, 18, 22,   0.0f,  1.0f,  43.0f, 112, 6.0f, 19.0f);
        floors.emplace_back(         kennel, 20, 19, -16.0f,  0.0f,  22.0f, 111, 6.0f, 19.0f);
        floors.emplace_back(         kennel, 20, 19, -16.0f,  1.0f,  22.0f, 112, 6.0f, 19.0f);
        floors.emplace_back(part_of_rockmap, 23, 14,  22.0f,  0.0f,  42.0f, 111, 6.0f, 19.0f);
        floors.emplace_back(part_of_rockmap, 23, 14,  22.0f,  1.0f,  42.0f, 112, 6.0f, 19.0f);
        floors.emplace_back(     end_of_map, 27, 31,  27.0f,  0.0f,  31.0f, 111, 6.0f, 19.0f);
        floors.emplace_back(     end_of_map, 27, 31,  27.0f,  1.0f,  31.0f, 112, 6.0f, 19.0f);
        floors.emplace_back(    last_secret, 12,  7,  18.0f,  0.0f,   0.0f, 111, 6.0f, 19.0f);
        floors.emplace_back(    last_secret, 12,  7,  18.0f,  1.0f,   0.0f, 112, 6.0f, 19.0f);
    }
    
    Hud hud;
    Pause pause;
    
    auto b = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<float> duuuu = b - a;
    std::cout << duuuu.count() << std::endl;
    
    game_s = PLAY;
    
    int face = 0;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disti(0, 2);
    
    std::chrono::duration<float> old_duration_face  = std::chrono::high_resolution_clock::now() - start;
    std::chrono::duration<float> old_duration_shoot = std::chrono::high_resolution_clock::now() - start;
    std::chrono::duration<float> old_duration_black = std::chrono::high_resolution_clock::now() - start;
    std::chrono::duration<float> old_duration_pick  = std::chrono::high_resolution_clock::now() - start;
    
    float pick_opacity   = 0.0f;
    float damage_opacity = 0.0f;
    Rect r = {0.0f, 0.0f, 1.0f, 1.0f};
    
    while (game_s == PLAY) {
        
        double transition_opacity = 1.0f;
        while (!glfwWindowShouldClose(window) && transition_opacity <= 1.0f) //Main window loop
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(color(0), color(64), color(64), 1.0f);
            
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> duration = end - start;
            
            input_game(game_s, secret_doors, doors, cWalls, player, enemies, window, duration, old_duration_shoot);
            
            glViewport(60, HEIGHT / 2 - 20, WIDTH * 2 - 120, HEIGHT + HEIGHT / 2 - 40);
            
            Walls->bind(GL_TEXTURE0);
            map_shader.useProgram();
            
            glm::mat4 view  = glm::mat4(1.0f);
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 proj  = glm::mat4(1.0f);
            
            view = glm::rotate(view,  glm::radians(player.rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            view = glm::translate(view, player.position);
            proj = glm::perspective(glm::radians(60.0f), (float)(1.9f), 0.01f, 100.0f);
            
            int viewLoc  = glGetUniformLocation(map_shader.shaderProgram,  "view");
            glUniformMatrix4fv(viewLoc,  1, GL_FALSE, glm::value_ptr(view));
            int projLoc  = glGetUniformLocation(map_shader.shaderProgram,  "proj");
            glUniformMatrix4fv(projLoc,  1, GL_FALSE, glm::value_ptr(proj));
            int modelLoc = glGetUniformLocation(map_shader.shaderProgram, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            
            for (Cube *map : parts_of_map)
                map->draw();
            
            for (Horizontal_plane &floor : floors)
                floor.draw();
                
            for (Door *door : doors)
                door->processing(view, proj, player.position, &enemies);
                
            for (S_Door *sdoors : secret_doors)
                sdoors->processing(view, proj);
                
            for (Item *item : items)
                item->processing(player, view, proj);
                
            non_bind->bind(GL_TEXTURE0);
            for (Furniture *furniture : static_furnitures)
                furniture->draw(player, view, proj);
                
            bind->bind(GL_TEXTURE0);
            for (Furniture *furniture : non_static_furnitures)
                furniture->draw(player, view, proj);
            
            for (Enemy *enemy : enemies) {
                enemy->processing(cWalls, duration, player, view, proj, doors);
            }
            
            player.gun.processing(duration, player, window);
            
            pick_tex->bind(GL_TEXTURE0);
            pick_ps.useProgram();
            Image::draw_once(0.0f, 0.0f, 2.0f, 2.0f, &r, pick_opacity);
            
            if (player.pick_up) {
                player.pick_up = false;
                pick_opacity = 0.25f;
            }
            
            if (pick_opacity >= 0.0f && duration.count() - old_duration_pick.count() > 0.0008f) {
                pick_opacity -= 0.01f;
                old_duration_pick = duration;
            }
                
            if (player.hit_points > 100) player.hit_points = 100;
            
            if (player.ammo > 99) player.ammo = 99;
            
            glViewport(50, 50, WIDTH * 2 - 100, 270);
            
            player.rotation = fmodf(player.rotation, 360);
            if (duration.count() - old_duration_face.count() > 0.5f) {
                face = disti(gen);
                old_duration_face = duration;
            }
            hud.draw(player, face);
            
            glViewport(0, 0, WIDTH * 2, HEIGHT * 2);
            if (player.take_damage) {
                player.take_damage = false;
                if (player.hit_points <=  0) {
                    player.lives--;
                    break;
                }
                if (player.hit_points <= 25)   damage_opacity = 0.75;
                if (player.hit_points >= 25)   damage_opacity = 0.55;
                if (player.hit_points >= 50)   damage_opacity = 0.35;
                if (player.hit_points >= 75)   damage_opacity = 0.2;
            }
            
            if (damage_opacity != 0.0f) damage_opacity -= 0.01f;
            
            damage_tex->bind(GL_TEXTURE0);
            damage_ps.useProgram();
            Image::draw_once(0.0f, 0.0f, 2.0f, 2.0f, &r, damage_opacity);
            
            end = std::chrono::high_resolution_clock::now();
            duration = end - start;
            
            if (duration.count() - old_duration_black.count() > 0.00001f) {
                if (game_s != PLAY) {
                    transition_opacity += 0.03f;
                    old_duration_black = duration;
                } else if (transition_opacity >= 0.0f) {
                    transition_opacity -= 0.03f;
                    old_duration_black = duration;
                }
                old_duration_black = duration;
            }
            
            black_ps.useProgram();
            black_tex->bind(GL_TEXTURE0);
            
            Image::draw_once(0.0f, 0.0f, 2.0f, 2.0f, &r, transition_opacity);
            
            glfwPollEvents();
            glfwSwapBuffers(window);
        }
        
        // pause
        float pause_opacity = 0.0f;
        old_duration_black = std::chrono::high_resolution_clock::now() - start;
        while (pause_opacity >= 0.0f) 
        {
            glClearColor(color(0), color(0), color(0), 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> duration = end - start;
            
            pause.processing(window, game_s, duration, pause_opacity);
            if (duration.count() - old_duration_black.count() > 0.00001f) {
                if (game_s != PAUSE) {
                    pause_opacity -= 0.02f;
                } else if (pause_opacity <= 1.0f && game_s == PAUSE) {
                    pause_opacity += 0.02f;
                }
                old_duration_black = duration;
            }
            
            glfwPollEvents();
            glfwSwapBuffers(window);
        }
    }
    
    int lives = player.lives;
    player = player_copy;
    player.lives = lives;
    
    for (Cube *cube_map : parts_of_map) {
        cube_map->clear();
        delete cube_map;
    }
    
    for (Furniture *furniture : static_furnitures) {
        furniture->clear();
        delete furniture;
    }
    
    for (Furniture *furniture : non_static_furnitures) {
        furniture->clear();
        delete furniture;
    }
        
    for (Horizontal_plane &floor : floors) {
        floor.clear();
    }
    
    for (Enemy *enemy : enemies) {
        enemy->clear();
    }
    
    for (Door *door : doors) {
        door->clear();
        delete door;
    }
    
    delete[] jail;
    delete[] hall;
    delete[] central_hall;
    delete[] wooden_thing;
    delete[] kennel;
    delete[] part_of_rockmap;
    delete[] end_of_map;
    delete pick_tex;
    delete damage_tex;
    delete non_bind;
    delete bind;
    delete Walls;
    
    map_shader.deleteShader();
    
    return game_s;
}
