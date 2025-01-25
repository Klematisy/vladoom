#include <random>
#include "libs.h"
#include "game.h"
#include "VPlane.h"

const static String shaderDir = "resource/Shaders/";
String bindShader(std::string dir);

void input(const std::vector<Door*> &doors, Collisions &collisions, Player &player, std::vector<Enemy> &enemies, GLFWwindow *window, bool &run, std::chrono::duration<float> duration, std::chrono::duration<float> &old_duration_shoot);
bool gameIsRunning = true;

float color(int i) { return i / 255.0f; }

auto start = std::chrono::high_resolution_clock::now();

void game(GLFWwindow *window) {
    /*---------------------------------------main code!---------------------------------------*/
    String vertexShaderSrc   = bindShader(shaderDir + "map/map.vert");
    String fragmentShaderSrc = bindShader(shaderDir + "map/map.frag");

    ProgramShader map_shader = ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());

    Texture *Walls = new Texture("resource/images/atlas2.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    Walls->unbind();
    Walls->uniform("tex0", map_shader, 0);

    Collisions cWalls;

    int *map  = new int[] {
        0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0,
        1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
        0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0,
        0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0,
        0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
        0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0,
        0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        0, 2, 1, 1, 3, 1, 1, 2, 1, 1, 2, 1, 1, 3, 0
    };

    Player player = {glm::vec3(-3.5f, -0.5f, -7.5f), 90.0f, 100, Gun()};
    player.score = 0;
    player.ammo = 99;
    
    std::vector<Enemy> enemies;
    
    enemies.push_back(Enemy(glm::vec3(-7.5f, 0.0f, -5.0f), 180.0f, 100, "Enemy-02.png"));
    // enemies.push_back(Enemy(glm::vec3(-7.5f, 0.0f, -7.0f),   0.0f, 100, "Enemy-02.png"));

    Cube part (map, 15, 14, 1.0f, 0.0f, 0.0f, 0.0f, cWalls, 5.0f, 2.0f);

    std::vector<Door*> doors;
    
    doors.push_back(new Door(-5.0f, -2.0f,  0.0f, cWalls, *Walls));
    doors.push_back(new Door(-9.0f, -2.0f,  0.0f, cWalls, *Walls));
    doors.push_back(new Door(-5.0f, -7.0f,  0.0f, cWalls, *Walls));
    doors.push_back(new Door(-9.0f, -7.0f,  0.0f, cWalls, *Walls));
    doors.push_back(new Door(-7.0f,  0.0f, 90.0f, cWalls, *Walls));

    Horizontal_plane room1( map, 15, 14, 0.0f, 0.0f,  0.0f,  8, 5.0f, 2.0f);
    Horizontal_plane room15(map, 15, 14, 0.0f, 1.0f,  0.0f,  9, 5.0f, 2.0f);

    Hud hud;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    int k = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disti(0, 2);

    std::chrono::duration<float> old_duration_face  = std::chrono::high_resolution_clock::now() - start;
    std::chrono::duration<float> old_duration_gun   = std::chrono::high_resolution_clock::now() - start;
    std::chrono::duration<float> old_duration_shoot = std::chrono::high_resolution_clock::now() - start;
    std::chrono::duration<float> old_duration_enemy = std::chrono::high_resolution_clock::now() - start;

    while (!glfwWindowShouldClose(window) && gameIsRunning) //Main window loop
    {
        // break;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(color(0), color(64), color(64), 1.0f);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = end - start;

        input(doors, cWalls, player, enemies, window, gameIsRunning, duration, old_duration_shoot);

        glViewport(60, HEIGHT / 2 - 20, WIDTH * 2 - 120, HEIGHT + HEIGHT / 2 - 40);

        Walls->bind(GL_TEXTURE0);
        map_shader.useProgram();

        glm::mat4 view  = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 proj  = glm::mat4(1.0f);

        view = glm::rotate(view,  glm::radians(player.rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::translate(view, player.position);
        proj = glm::perspective(glm::radians(60.0f), (float)(1.8), 0.01f, 100.0f);

        int viewLoc  = glGetUniformLocation(map_shader.shaderProgram,  "view");
        glUniformMatrix4fv(viewLoc,  1, GL_FALSE, glm::value_ptr(view));
        int projLoc  = glGetUniformLocation(map_shader.shaderProgram,  "proj");
        glUniformMatrix4fv(projLoc,  1, GL_FALSE, glm::value_ptr(proj));
        int modelLoc = glGetUniformLocation(map_shader.shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        part.draw();
        
        room1.draw();
        room15.draw();
        
        for (Door *door : doors)
            door->processing(player.position, view, proj, window, player.rotation);
        
        for (int i = enemies.size() - 1; i >= 0; i--) {
            enemies[i].processing(cWalls, duration, player, view, proj, doors);
        }
        
        player.gun.processing(old_duration_gun, duration, player, window);

        player.rotation = fmodf(player.rotation, 360);
        
        glViewport(50, 50, WIDTH * 2 - 100, 270);

        if (duration.count() - old_duration_face.count() > 0.5f) {
            k = disti(gen);
            old_duration_face = duration;
        }
        hud.draw(player, k);

        if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS && player.hit_points < 100) {
            player.hit_points += 1.0f;
        }
        
        if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS && player.hit_points > 0) {
            player.hit_points -= 1.0f;
        }

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    for (Enemy &enemy : enemies) {
        enemy.clear();
    }
    
    for (Door *door : doors) {
        door->clear();
    }
    
    for (Door *door : doors) {
        delete door;
    }

    map_shader.deleteShader();
}
