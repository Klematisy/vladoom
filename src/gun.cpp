#include "game.h"
#include "input.h"

const static String shaderDir = "resource/Shaders/";

String bindShader(std::string dir);

Gun::Gun()
{
    String vertexShaderSrc   = bindShader(shaderDir + "map1/map.vert");
    String fragmentShaderSrc = bindShader(shaderDir + "map1/map.frag");

    gun_ps  = new ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    gun_tex = new Texture("resource/images/guns.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
}

void Gun::update(Player &p, 
                 GLFWwindow *window) 
{
    if (KeyboardInput::KEY_1_PRESSED(window) && num_of_animation == 0 && p.invetory[0] == 1)
        p.typeOfGun = 1;
    if (KeyboardInput::KEY_2_PRESSED(window) && num_of_animation == 0 && p.invetory[1] == 2)
        p.typeOfGun = 2;
    if (KeyboardInput::KEY_3_PRESSED(window) && num_of_animation == 0 && p.invetory[2] == 3)
        p.typeOfGun = 3;
    if (KeyboardInput::KEY_4_PRESSED(window) && num_of_animation == 0 && p.invetory[3] == 4)
        p.typeOfGun = 4;
}

void Gun::draw(std::chrono::duration<float> duration, 
               Player &p, 
               GLFWwindow *window) 
{
    
    if (duration.count() - old_duration_gun.count() > 0.15f && num_of_animation > 0) {
        num_of_animation++;
        old_duration_gun = duration;
    }
    
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (p.typeOfGun == 4 && num_of_animation == 4 && p.ammo > 0 && (state == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS))
        num_of_animation = 2;

    if ((state == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) && num_of_animation == 0) {
        if (p.typeOfGun == 1 || p.ammo > 0)
            num_of_animation = 1;
    }

    if (num_of_animation == 5) num_of_animation = 0;

    gun_tex->bind(GL_TEXTURE0);
    gun_ps->useProgram();
    Rect r = { num_of_animation / 5.0f,
              (4.0f - p.typeOfGun) / 4,
              (num_of_animation + 1) / 5.0f,
              (4.0f - p.typeOfGun + 1.0f) / 4};

    Image::draw_once(0.475f, 0.0f, 1.0f, 1.5f, &r,  1.0f);
}

void Gun::processing(std::chrono::duration<float> duration, 
                     Player &p, 
                     GLFWwindow *window) 
{
    update(p, window);
    draw(duration, p, window);
}

Gun::~Gun()
{
    delete gun_tex;
    delete gun_ps;
}
