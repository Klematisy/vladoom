#include "constants.h"
#include "libs.h"
#include "game.h"

GAME_STATE stage1(GLFWwindow *window, Player &player, Player player_copy, GAME_STATE &game_s);

void game(GLFWwindow *window) {
    // translation unit with settings and stages
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwPollEvents();
    glfwSetCursorPos(window, 2560 / 2, 1600 / 2);

    GAME_STATE game_s = PLAY;
    
    Player player = {glm::vec3(-3.5f, -0.5f, -11.5f), 90.0f, 100, Gun()};
    while (stage1(window, player, {glm::vec3(-3.5f, -0.5f, -11.5f), 90.0f, 100, Gun()}, game_s) != EXIT);
}