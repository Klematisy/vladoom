#include "game.h"
#include "input.h"

const static String shaderDir = "resource/Shaders/";
String bindShader(std::string dir);

Menu::Menu(String picture) {
    String vertexShaderSrc   = bindShader(shaderDir + "map1/map.vert");
    String fragmentShaderSrc = bindShader(shaderDir + "map1/map.frag");

    pause_ps   = new ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    pause_tex  = new Texture((((String)"resource/images/").append(picture)).c_str(), GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    cursor_tex = new Texture("resource/images/cursor.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
}

void Menu::update(GLFWwindow *w, GAME_STATE &game_s, std::chrono::duration<float> duration) {
    float dur = duration.count() - old_duration.count();
    float time = 0.1f;
    if (num % 2 != 0 && num_checker < num && dur > time) {
        num_checker = ++num;
    } else if (num % 2 != 0 && dur > time) {
        num_checker = --num;
    }
    
    if (KeyboardInput::KEY_E_PRESSED(w) || KeyboardInput::KEY_ENTER_PRESSED(w)) {
        if (num == 0) {
            game_s = PLAY;
        } else if (num == 2) {
            game_s = EXIT;
        }
    }
    
    if (KeyboardInput::KEY_ESCAPE_PRESSED(w)) {
        std::cout << "EXIT\n";
        game_s = EXIT;
    }
    
    if ((KeyboardInput::KEY_UP_PRESSED(w) || KeyboardInput::KEY_W_PRESSED(w)) && num > 0 && dur > time) {
        num_checker = num--;
        old_duration = duration;
    }
    
    if ((KeyboardInput::KEY_DOWN_PRESSED(w) || KeyboardInput::KEY_S_PRESSED(w)) && num < 2 && dur > time) {
        num_checker = num++;
        old_duration = duration;
    }
}

void Menu::processing(GLFWwindow *w, GAME_STATE &game_s, std::chrono::duration<float> duration, float opacity) {
    if (opacity >= 1.0f) update(w, game_s, duration);
    draw(opacity);
}

void Menu::draw(float opacity) {
    pause_ps->useProgram();
    pause_tex->bind(GL_TEXTURE0);
    
    Rect r = {0.0f, 0.0f, 1.0f, 1.0f};
    
    Image::draw_once(0.0f, 0.0f, 2.0f, 2.0f, &r, opacity);
    
    cursor_tex->bind(GL_TEXTURE0);
    
    r = {0.0f, 0.0f, 1.0f, 1.0f};
    
    Image::draw_once(0.469f, 1.02f - 0.09 * num, 0.108f, 0.09f, &r, opacity);
}
