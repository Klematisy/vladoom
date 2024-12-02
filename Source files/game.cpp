#include "libs.h"
#include "game.h"
#include "VPlane.h"

const static String shaderDir = "Resource files/Shaders/";
String bindShader(std::string dir);

void input(Collisions &collisions, glm::vec3 &position, float &rotation, GLFWwindow *window, bool &run);
bool gameIsRunning = true;

float color(int i) {
return i / 255.0f;
}

void game(GLFWwindow* window) {
    /*---------------------------------------main code!---------------------------------------*/

    String vertexShaderSrc   = bindShader(shaderDir + "map/map.vert");
    String fragmentShaderSrc = bindShader(shaderDir + "map/map.frag");

    ProgramShader map_shader = ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());

    vertexShaderSrc   = bindShader(shaderDir + "map1/map.vert");
    fragmentShaderSrc = bindShader(shaderDir + "map1/map.frag");

    ProgramShader hud_shader  = ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    ProgramShader nums_shader = ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());

    Texture* Walls = new Texture("Resource files/images/atlas.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    Walls->unbind();
    Walls->uniform("tex0", map_shader, 0);

    Texture* hud_texture = new Texture("Resource files/images/hud.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    hud_texture->unbind();
    hud_texture->uniform("tex0", hud_shader, 0);

    Texture* nums_texture = new Texture("Resource files/images/nums.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    nums_texture->unbind();
    nums_texture->uniform("tex0", nums_shader, 0);

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
        0, 1, 3, 1, 2, 1, 1, 1,
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

    Symbol s(0.095f, 0.07f, 2);

    Symbol score1(0.28f, 0.07f, 0);
    Symbol score2(0.34f, 0.07f, 0);
    Symbol score3(0.40f, 0.07f, 0);
    Symbol score4(0.46f, 0.07f, 0);
    Symbol score5(0.52f, 0.07f, 0);

    Symbol lives(0.69f, 0.07f, 0);

    Symbol  health(1.045f, 0.07f, 0);
    Symbol health1(1.095f, 0.07f, 0);
    Symbol health2(1.145f, 0.07f, 0);

    Symbol  ammo(1.37f, 0.07f, 0);
    Symbol ammo1(1.42f, 0.07f, 0);

    player.hitPoints = 100;
    player.ammo = 42;
    int score_copy  = player.score;
    int health_copy = player.hitPoints;
    int ammo_copy   = player.ammo;
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    while (!glfwWindowShouldClose(window) && gameIsRunning) //Main window loop
    {
        // break;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(color(0), color(64), color(64), 1.0f);
        
        input(cWalls, player.position, player.rotation, window, gameIsRunning);
        ///*
        glViewport(60, HEIGHT / 2 - 20, WIDTH * 2 - 120, HEIGHT + HEIGHT / 2 - 40);

        Walls->bind(GL_TEXTURE0);
        map_shader.useProgram();

        glm::mat4 view   = glm::mat4(1.0f);
        glm::mat4 model  = glm::mat4(1.0f);
        glm::mat4 proj   = glm::mat4(1.0f);

        view = glm::rotate(view,  glm::radians(player.rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::translate(view, player.position);
        proj = glm::perspective(glm::radians(70.0f), (float)(1.8), 0.01f, 100.0f);

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

        glViewport(50, 50, WIDTH * 2 - 100, 1300);

        hud_texture->bind(GL_TEXTURE0);
        hud_shader.useProgram();
        hud.draw();

        nums_texture->bind(GL_TEXTURE0);
        nums_shader.useProgram();
        s.draw(1);

        score_copy = player.score;
        score1.draw(score_copy / 10000);
        score_copy %= 10000;
        score2.draw(score_copy / 1000);
        score_copy %= 1000;
        score3.draw(score_copy / 100);
        score_copy %= 100;
        score4.draw(score_copy / 10);
        score_copy %= 10;
        score5.draw(score_copy / 1);

        lives.draw(player.lives);

        health_copy = player.hitPoints;
        if (health_copy == 100) {
            health.draw(health_copy / 100);
            health_copy %= 100;
        }
        health1.draw(health_copy / 10);
        health_copy %= 10;
        health2.draw(health_copy / 1);
        
        ammo_copy = player.ammo;
        ammo.draw(ammo_copy / 10);
        ammo_copy %= 10;
        ammo1.draw(ammo_copy / 1);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    delete map;
    delete map2;
    delete map3;

    delete doorArr1;
    delete doorArr2;
    delete doorArr3;
    delete doorArr4;
}