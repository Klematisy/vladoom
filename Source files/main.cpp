#include <cmath>
#include "constants.h"
#include "libs.h"

void game(GLFWwindow* window);

int main(void) 
{
    //INICIALIZATION OF WINDOW AND LIBRARY
    GLFWwindow* window;
    if (!glfwInit())
        return -1;    

    //VERSION INICIALIZATION (4.1 OpenGL)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH, HEIGHT, "VLAD", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << (const char*) glGetString(GL_VERSION) << std::endl;

    glfwSwapInterval(1);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwPollEvents();
    glfwSetCursorPos(window, 2560 / 2, 1440 / 2);

    glEnable(GL_DEPTH_TEST);

    game(window);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}