#include "game.h"
#include "input.h"

const static String shaderDir = "resource/Shaders/";
String bindShader(std::string dir);

Pause::Pause() : Menu("pause.png")
{}

void Pause::update(GLFWwindow *w, GAME_STATE &game_s, std::chrono::duration<float> duration) {
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
    
    if (KeyboardInput::KEY_ESCAPE_PRESSED(w))
        game_s = PLAY;
    
    if ((KeyboardInput::KEY_UP_PRESSED(w) || KeyboardInput::KEY_W_PRESSED(w)) && num > 0 && dur > time) {
        num_checker = num--;
        old_duration = duration;
    }
    
    if ((KeyboardInput::KEY_DOWN_PRESSED(w) || KeyboardInput::KEY_S_PRESSED(w)) && num < 2 && dur > time) {
        num_checker = num++;
        old_duration = duration;
    }
}
