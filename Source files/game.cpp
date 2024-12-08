#include <random>
#include "libs.h"
#include "game.h"
#include "VPlane.h"

const static String shaderDir = "Resource files/Shaders/";
String bindShader(std::string dir);

void input(Collisions &collisions, glm::vec3 &position, float &rotation, GLFWwindow *window, bool &run);
bool gameIsRunning = true;

float color(int i) { return i / 255.0f; }

auto start = std::chrono::high_resolution_clock::now();

void game(GLFWwindow* window) {
    /*---------------------------------------main code!---------------------------------------*/

    String vertexShaderSrc   = bindShader(shaderDir + "map/map.vert");
    String fragmentShaderSrc = bindShader(shaderDir + "map/map.frag");

    ProgramShader map_shader = ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());

    Texture* Walls = new Texture("Resource files/images/atlas.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    Walls->unbind();
    Walls->uniform("tex0", map_shader, 0);

    Collisions cWalls;

    const int mapWidth  = 8;
    const int mapHeight = 11;
    int *map  = new int[mapWidth * mapHeight] {
        0, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 1, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 3,
        1, 0, 0, 0, 1, 0, 0, 1,
        0, 1, 1, 1, 1, 1, 0, 3,
        1, 0, 0, 0, 1, 0, 0, 1,
        2, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 1, 1, 1, 1,
        3, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 3, 1, 2, 1, 1, 1
    };

    int *map2 = new int[mapWidth * mapHeight] {
        4, 4, 4, 4, 4, 4, 4, 4,
        4, 0, 0, 4, 4, 4, 4, 4,
        4, 0, 0, 0, 0, 0, 0, 4,
        4, 0, 0, 4, 4, 0, 4, 4,
        4, 0, 0, 4, 0, 0, 0, 4,
        4, 0, 0, 4, 4, 0, 4, 4,
        4, 0, 0, 4, 0, 0, 0, 4,
        4, 0, 0, 4, 0, 0, 0, 4,
        0, 0, 0, 4, 0, 0, 0, 4,
        0, 0, 0, 4, 0, 0, 0, 4,
        4, 4, 4, 4, 4, 0, 4, 4,
    };

    int *map3 = new int[mapWidth * mapHeight] {
        5, 5, 4, 5, 5, 0, 5, 5,
        5, 0, 0, 0, 0, 0, 0, 5,
        4, 0, 0, 5, 0, 0, 0, 5,
        5, 0, 0, 5, 5, 0, 5, 5,
        4, 0, 0, 5, 0, 0, 0, 4,
        5, 0, 0, 4, 0, 0, 0, 5,
        4, 0, 0, 0, 0, 0, 0, 4,
        5, 0, 0, 0, 0, 0, 0, 5,
        4, 0, 0, 0, 0, 0, 0, 4,
        5, 0, 0, 4, 0, 0, 0, 5,
        5, 5, 4, 5, 4, 5, 4, 5,
    };

    int *doorArr1 = new int[1] {6};
    int *doorArr2 = new int[1] {6};
    int *doorArr3 = new int[1] {6};
    int *doorArr4 = new int[1] {6};

    Player player = {glm::vec3(-1.5f, -0.5f, -2.5f), 90.0f, 0};
    player.score = 11110;

    Cube part (map,  mapWidth, mapHeight, 1.0f,  0.0f,  0.0f,  0.0f, cWalls);
    Cube part1(map2, mapWidth, mapHeight, 1.0f,  8.0f,  0.0f,  0.0f, cWalls);
    Cube part2(map3, mapWidth, mapHeight, 1.0f,  8.0f, 11.0f,  0.0f, cWalls);

    Door door1(doorArr1,  4.0f,  2.0f,  0.0f, cWalls, *Walls);
    Door door2(doorArr2, 13.0f,  3.0f, 90.0f, cWalls, *Walls);
    Door door3(doorArr3,  7.0f,  9.0f,  0.0f, cWalls, *Walls);
    Door door4(doorArr4, 13.0f, 10.0f, 90.0f, cWalls, *Walls);

    Horizontal_plane room1( map,  mapWidth, mapHeight, 0.0f, 0.0f, 0.0f, 7.0f);
    Horizontal_plane room15(map,  mapWidth, mapHeight, 0.0f, 1.0f, 0.0f, 8.0f);

    Horizontal_plane room2( map2, mapWidth, mapHeight, 8.0f, 0.0f, 0.0f, 7.0f);
    Horizontal_plane room25(map2, mapWidth, mapHeight, 8.0f, 1.0f, 0.0f, 9.0f);

    Horizontal_plane room3( map3, mapWidth, mapHeight, 8.0f, 0.0f, 11.0f, 7.0f);
    Horizontal_plane room35(map3, mapWidth, mapHeight, 8.0f, 1.0f, 11.0f, 9.0f);

    Hud hud;

    Enemy e = glm::vec3(2.5f, 0.0f, 8.0f);

    player.hitPoints = 100;
    player.ammo = 42;
    int score_copy  = player.score;
    int health_copy = player.hitPoints;
    int ammo_copy   = player.ammo;
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);


    int k = 0;
    std::random_device rd;   // non-deterministic generator
    std::mt19937 gen(rd());  // to seed mersenne twister.
    std::uniform_int_distribution<int> dist(0,2); // distribute results between 1 and 6 inclusive.

    std::chrono::duration<float> old_duration = std::chrono::high_resolution_clock::now() - start;
    while (!glfwWindowShouldClose(window) && gameIsRunning) //Main window loop
    {
        // break;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(color(0), color(64), color(64), 1.0f);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = end - start;

        // if (duration.count() > 10.0f) {
        //     std::cout << "HELLO" << std::endl;
        //     start = std::chrono::high_resolution_clock::now();
        // }

        input(cWalls, player.position, player.rotation, window, gameIsRunning);

        glViewport(60, HEIGHT / 2 - 20, WIDTH * 2 - 120, HEIGHT + HEIGHT / 2 - 40);

        Walls->bind(GL_TEXTURE0);
        map_shader.useProgram();

        glm::mat4 view  = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 proj  = glm::mat4(1.0f);

        view = glm::rotate(view,  glm::radians(player.rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::translate(view, player.position);
        proj = glm::perspective(glm::radians(60.0f), (float)(1.8), 0.01f, 100.0f);

        int viewLoc   = glGetUniformLocation(map_shader.shaderProgram,  "view");
        glUniformMatrix4fv(viewLoc,  1, GL_FALSE, glm::value_ptr(view));
        int projLoc   = glGetUniformLocation(map_shader.shaderProgram,  "proj");
        glUniformMatrix4fv(projLoc,  1, GL_FALSE, glm::value_ptr(proj));
        int modelLoc  = glGetUniformLocation(map_shader.shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        
        part.draw();
        part1.draw(); 
        part2.draw();

        room1.draw();
        room15.draw();
        room2.draw();
        room25.draw();
        room3.draw();
        room35.draw();

        door1.draw(player.position, view, proj, window, player.rotation);
        door2.draw(player.position, view, proj, window, player.rotation);
        door3.draw(player.position, view, proj, window, player.rotation);
        door4.draw(player.position, view, proj, window, player.rotation);

        e.draw(player, view, proj);

        glViewport(50, 50, WIDTH * 2 - 100, 270);
        
        if (duration.count() - old_duration.count() > 1.0f) {
            // k = (k == 2) ? 0 : k + 1;
            k = dist(gen);
            old_duration = duration;
            // std::cout << player.position.x << " " << player.position.y << std::endl;
        }
        hud.draw(player, k);

        if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
            player.hitPoints -= 1.0f;
        }

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    map_shader.deleteShader();

    delete map;
    delete map2;
    delete map3;

    delete doorArr1;
    delete doorArr2;
    delete doorArr3;
    delete doorArr4;
}