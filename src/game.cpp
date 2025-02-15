#include "libs.h"
#include "game.h"
#include "VPlane.h"
#include <random>

const static String shaderDir = "resource/Shaders/";
String bindShader(std::string dir);

void input(std::vector<S_Door*> &secret_doors, std::vector<Door*> &doors, Collisions &colls, Player &player, std::vector<Enemy> &enemies, GLFWwindow *window, bool &run, std::chrono::duration<float> duration, std::chrono::duration<float> &old_duration_shoot);
bool gameIsRunning = true;

float color(int i) { return i / 255.0f; }

auto start = std::chrono::high_resolution_clock::now();

void game(GLFWwindow *window) {
    /*---------------------------------------main code!---------------------------------------*/
    String vertexShaderSrc   = bindShader(shaderDir + "map/map.vert");
    String fragmentShaderSrc = bindShader(shaderDir + "map/map.frag");

    ProgramShader map_shader = ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    
    Texture *non_bind = new Texture("resource/images/non-blocking-objs.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    Texture *bind     = new Texture("resource/images/blocking-objs.png",     GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE1);

    Texture *Walls = new Texture("resource/images/atlas.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
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
    
    // Player player = {glm::vec3(-3.5f, -0.5f, -7.5f), 90.0f, 100, Gun()};
    // Player player = {glm::vec3(16.5f, -0.5f, 34.5f), 180.0f, 100, Gun()};
    Player player = {glm::vec3(12.5f, -0.5f, 2.5f), 90.0f, 100, Gun()};
    player.score = 0;
    player.ammo  = 99;
    
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
        // items.push_back(new Item(-7.5, -5.5, 2, 500, player, SCORE));
    }
    
    std::vector<Enemy> enemies;
    {
        enemies.emplace_back(window, glm::vec3(-4.5f, 0.0f,  -7.5f), 90.0f,   0,  0, "Enemy-015.png", RIGHT_TURN);
        enemies.emplace_back(window, glm::vec3(-9.5f, 0.0f, -10.5f), 90.0f, 100, 25, "Enemy-015.png", RIGHT_TURN);
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
        secret_doors.push_back(new S_Door( -3.0f,  28.0f, 270, 20, cWalls));
        secret_doors.push_back(new S_Door(  17.0f, 37.0f,   0,  7, cWalls));
        secret_doors.push_back(new S_Door(   9.0f,  1.0f, 180,  1, cWalls));
        secret_doors.push_back(new S_Door(  10.0f,  0.0f, 270,  2, cWalls));
        secret_doors.push_back(new S_Door(  14.0f, -3.0f, 180,  2, cWalls));
    }
    
    std::vector<Horizontal_plane> floors;
    {
        floors.emplace_back(jail, 15, 14, 0.0f, 0.0f,   0.0f, 111, 6.0f, 19.0f);
        floors.emplace_back(jail, 15, 14, 0.0f, 1.0f,   0.0f, 112, 6.0f, 19.0f);
        floors.emplace_back(hall,  5, 12, 5.0f, 0.0f, -12.0f, 111, 6.0f, 19.0f);
        floors.emplace_back(hall,  5, 12, 5.0f, 1.0f, -12.0f, 112, 6.0f, 19.0f);
        
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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    int face = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disti(0, 2);

    std::chrono::duration<float> old_duration_face  = std::chrono::high_resolution_clock::now() - start;
    std::chrono::duration<float> old_duration_shoot = std::chrono::high_resolution_clock::now() - start;

    while (!glfwWindowShouldClose(window) && gameIsRunning) //Main window loop
    {
        // break;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(color(0), color(64), color(64), 1.0f);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = end - start;

        input(secret_doors, doors, cWalls, player, enemies, window, gameIsRunning, duration, old_duration_shoot);

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
            
        bind->bind(GL_TEXTURE1);
        for (Furniture *furniture : non_static_furnitures)
            furniture->draw(player, view, proj);
            
        for (int i = enemies.size() - 1; i >= 0; i--) {
            enemies[i].processing(cWalls, duration, player, view, proj, doors);
        }
        
        player.gun.processing(duration, player, window);
        if (player.hit_points > 100) {
            player.hit_points = 100;
        }
        
        if (player.ammo > 99) {
            player.ammo = 99;
        }
        
        glViewport(50, 50, WIDTH * 2 - 100, 270);
        player.rotation = fmodf(player.rotation, 360);
        if (duration.count() - old_duration_face.count() > 0.5f) {
            face = disti(gen);
            old_duration_face = duration;
        }
        hud.draw(player, face);

        if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS && player.hit_points < 100) {
            player.hit_points += 1.0f;
        }
        
        if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS && player.hit_points > 0) {
            player.hit_points -= 1.0f;
        }

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
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
    
    for (Enemy &enemy : enemies) {
        enemy.clear();
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

    map_shader.deleteShader();
}
