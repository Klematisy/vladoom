#include "constants.h"
#include "libs.h"
#include "game.h"

GAME_STATE main_menu(GLFWwindow *window, GAME_STATE &game_s);
GAME_STATE    stage1(GLFWwindow *window, Player &player, Player player_copy, GAME_STATE &game_s);

void game(GLFWwindow *window) {
    // translation unit with settings and stages
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwPollEvents();
    glfwSetCursorPos(window, 2560 / 2, 1600 / 2);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    GAME_STATE game_s = MAIN_MENU;
    
    main_menu(window, game_s);
    
    Player player = {glm::vec3(-3.5f, -0.5f, -11.5f), 90.0f, 100, Gun()};
    while (game_s != EXIT) {
        stage1(window, player, {glm::vec3(-3.5f, -0.5f, -11.5f), 90.0f, 100, Gun()}, game_s);
    }
    
}