#include <cmath>
#include "constants.h"
#include "libs.h"
#include "game.h"
#include "settings.h"

void game(GLFWwindow *window);

int main(void)  {
    // translation unit for creating a window
    
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

    game(window); // Go to the game
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
