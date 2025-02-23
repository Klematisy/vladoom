#include "libs.h"
#include "game.h"
#include <random>

const static String shaderDir = "resource/Shaders/";
String bindShader(std::string dir);
static auto start = std::chrono::high_resolution_clock::now();
static float color(int i) { return i / 255.0f; }

GAME_STATE main_menu(GLFWwindow *window, GAME_STATE &game_s) {
    Menu menu("main_menu.png");
    
    float menu_opacity = 0.0f;
    std::chrono::duration<float> old_duration_black = std::chrono::high_resolution_clock::now() - start;
    while (menu_opacity >= 0.0f) 
    {
        glClearColor(color(0), color(0), color(0), 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = end - start;
        
        menu.processing(window, game_s, duration, menu_opacity);
        if (duration.count() - old_duration_black.count() > 0.00001f) {
            if (game_s != MAIN_MENU) {
                menu_opacity -= 0.02f;
            } else if (menu_opacity <= 1.0f && game_s == MAIN_MENU) {
                menu_opacity += 0.02f;
            }
            old_duration_black = duration;
        }
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}