#include "game.h"

const static String shaderDir = "resource/Shaders/";

String bindShader(std::string dir);

Gun::Gun()
{
    String vertexShaderSrc   = bindShader(shaderDir + "map1/map.vert");
    String fragmentShaderSrc = bindShader(shaderDir + "map1/map.frag");

    gun_ps  = new ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    gun_tex = new Texture("resource/images/guns1.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
}

void Gun::update
            (std::chrono::duration<float> &old_duration_gun, 
             std::chrono::duration<float> duration, 
             Player &p, 
             GLFWwindow *window) 
{
    
}

void Gun::draw(std::chrono::duration<float> &old_duration_gun, 
               std::chrono::duration<float> duration, 
               Player &p, 
               GLFWwindow *window) 
{

    if (duration.count() - old_duration_gun.count() > 0.15f && num_of_animation > 0) {
        num_of_animation++;
        old_duration_gun = duration;
    }

    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if ((state == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) && num_of_animation == 0) {
        if (p.typeOfGun == 1)
            num_of_animation = 1;
        else if (p.ammo > 0) {
            num_of_animation = 1;
            p.ammo--;
        }
    }

    if (num_of_animation == 5) num_of_animation = 0;

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && num_of_animation == 0) { 
        p.typeOfGun = 1;
        num_of_animation = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && num_of_animation == 0) {
        p.typeOfGun = 2;
        num_of_animation = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && num_of_animation == 0) { 
        p.typeOfGun = 3;
        num_of_animation = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && num_of_animation == 0) {
        p.typeOfGun = 4;
        num_of_animation = 0;
    }

    gun_tex->bind(GL_TEXTURE0);
    gun_ps->useProgram();
    Rect r = { num_of_animation / 5.0f,
              (4.0f - p.typeOfGun) / 4,
              (num_of_animation + 1) / 5.0f,
              (4.0f - p.typeOfGun + 1.0f) / 4};

    Image::draw_once(0.475f, 0.0f, 1.0f, 1.5f, &r);
}

void Gun::processing
            (std::chrono::duration<float> &old_duration_gun, 
             std::chrono::duration<float> duration, 
             Player &p, 
             GLFWwindow *window) 
{
    update(old_duration_gun, duration, p, window);
    
    draw(old_duration_gun, duration, p, window);
}

Gun::~Gun()
{
    delete gun_tex;
    delete gun_ps;
}
