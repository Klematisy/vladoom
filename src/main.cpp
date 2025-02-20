#include <cmath>
#include "constants.h"
#include "libs.h"
#include "game.h"
#include "settings.h"

bool game(GLFWwindow *window, Player &player, Player player_copy);

int main(void)  {
    GLFWwindow *window;
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "VLAD", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << (const char*) glGetString(GL_VERSION) << std::endl;

    glfwSwapInterval(1);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwPollEvents();
    glfwSetCursorPos(window, 2560 / 2, 1600 / 2);

    Player player = {glm::vec3(-3.5f, -0.5f, -11.5f), 90.0f, 100, Gun()};
    while (game(window, player, {glm::vec3(-3.5f, -0.5f, -11.5f), 90.0f, 100, Gun()}) && player.lives != 0);
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
