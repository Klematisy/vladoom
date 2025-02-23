struct KeyboardInput {
    static bool        KEY_1_PRESSED(GLFWwindow *w)         { return glfwGetKey(w, GLFW_KEY_1)                == GLFW_PRESS; }
    static bool        KEY_2_PRESSED(GLFWwindow *w)         { return glfwGetKey(w, GLFW_KEY_2)                == GLFW_PRESS; }
    static bool        KEY_3_PRESSED(GLFWwindow *w)         { return glfwGetKey(w, GLFW_KEY_3)                == GLFW_PRESS; }
    static bool        KEY_4_PRESSED(GLFWwindow *w)         { return glfwGetKey(w, GLFW_KEY_4)                == GLFW_PRESS; }
    static bool        KEY_I_PRESSED(GLFWwindow *w)         { return glfwGetKey(w, GLFW_KEY_I)                == GLFW_PRESS; }
    static bool        KEY_K_PRESSED(GLFWwindow *w)         { return glfwGetKey(w, GLFW_KEY_K)                == GLFW_PRESS; }
    static bool        KEY_W_PRESSED(GLFWwindow *w)         { return glfwGetKey(w, GLFW_KEY_W)                == GLFW_PRESS; }
    static bool        KEY_A_PRESSED(GLFWwindow *w)         { return glfwGetKey(w, GLFW_KEY_A)                == GLFW_PRESS; }
    static bool        KEY_S_PRESSED(GLFWwindow *w)         { return glfwGetKey(w, GLFW_KEY_S)                == GLFW_PRESS; }
    static bool        KEY_D_PRESSED(GLFWwindow *w)         { return glfwGetKey(w, GLFW_KEY_D)                == GLFW_PRESS; }
    static bool        KEY_E_PRESSED(GLFWwindow *w)         { return glfwGetKey(w, GLFW_KEY_E)                == GLFW_PRESS; }
    static bool       KEY_UP_PRESSED(GLFWwindow *w)         { return glfwGetKey(w, GLFW_KEY_UP)               == GLFW_PRESS; }
    static bool     KEY_DOWN_PRESSED(GLFWwindow *w)         { return glfwGetKey(w, GLFW_KEY_DOWN)             == GLFW_PRESS; }
    static bool     KEY_LEFT_PRESSED(GLFWwindow *w)         { return glfwGetKey(w, GLFW_KEY_LEFT)             == GLFW_PRESS; }
    static bool    KEY_RIGHT_PRESSED(GLFWwindow *w)         { return glfwGetKey(w, GLFW_KEY_RIGHT)            == GLFW_PRESS; }
    static bool    KEY_ENTER_PRESSED(GLFWwindow *w)         { return glfwGetKey(w, GLFW_KEY_ENTER)            == GLFW_PRESS; }
    static bool   KEY_LSHIFT_PRESSED(GLFWwindow *w)         { return glfwGetKey(w, GLFW_KEY_LEFT_SHIFT)       == GLFW_PRESS; }
    static bool   KEY_RSHIFT_PRESSED(GLFWwindow *w)         { return glfwGetKey(w, GLFW_KEY_RIGHT_SHIFT)      == GLFW_PRESS; }
    static bool   KEY_ESCAPE_PRESSED(GLFWwindow *w)         { return glfwGetKey(w, GLFW_KEY_ESCAPE)           == GLFW_PRESS; }
};

struct MouseInput {
    static bool     LEFT_KEY_PRESSED(GLFWwindow *w) { return glfwGetMouseButton(w, GLFW_MOUSE_BUTTON_LEFT)    == GLFW_PRESS; }
    static bool   RRIGHT_KEY_PRESSED(GLFWwindow *w) { return glfwGetMouseButton(w, GLFW_MOUSE_BUTTON_RIGHT)   == GLFW_PRESS; }
};