#include <libs.h>
#include <settingsAndVars.h>

const static String shaderDir = "Resource files/Shaders/";
String bindShader(std::string dir);

void input(Collisions &collisions, glm::vec3 &position, float &rotation, GLFWwindow *window, bool &run);
bool gameIsRunning = true;

void game(GLFWwindow* window)
{
    /*--------------------------------------------------------main code!--------------------------------------------------------*/

    String vertexShaderSrc   = bindShader(shaderDir + "map/map.vert");
    String fragmentShaderSrc = bindShader(shaderDir + "map/map.frag");

    ProgramShader programShader = ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    ProgramShader ps            = ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    ProgramShader ps1           = ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());

    Texture* Walls = new Texture("Resource files/images/atlas.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    Walls->unbind();
    Walls->uniform("tex0", programShader, 0);

    Collisions cWalls;
    
    const int mapWidth  = 8;
    const int mapHeight = 11;
    int *map = new int[mapWidth * mapHeight] {
        0, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 1, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 3,
        1, 0, 0, 0, 1, 0, 0, 1,
        0, 1, 1, 1, 1, 1, 0, 3,
        1, 0, 0, 0, 1, 0, 0, 1,
        2, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 1, 1, 1, 1,
        3, 0, 0, 0, 0, 1, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 3, 1, 2, 1, 1, 1,
    };

    int *map2 = new int[mapWidth * mapHeight] {
        4, 4, 4, 4, 4, 4, 4, 4,
        4, 0, 0, 4, 4, 4, 4, 4,
        4, 0, 0, 0, 0, 0, 0, 4,
        4, 0, 0, 4, 4, 0, 4, 4,
        4, 0, 0, 4, 0, 0, 0, 4,
        1, 0, 0, 4, 4, 0, 4, 4,
        1, 0, 0, 4, 0, 0, 0, 4,
        1, 0, 0, 4, 0, 0, 0, 4,
        0, 0, 0, 4, 0, 0, 0, 4,
        0, 0, 0, 4, 0, 0, 0, 4,
        1, 1, 1, 1, 4, 4, 4, 4,
    };

    int *doorArr1 = new int[1] {6};
    int *doorArr2 = new int[1] {6};

    glm::vec3 position  = glm::vec3(-1.5f, -0.5f, -2.5f);
    float rotation = 90.0f;
    
    Cube part (map,  mapWidth, mapHeight, 1.0f,  0.0f,  0.0f,  0.0f, cWalls);
    Cube part1(map2, mapWidth, mapHeight, 1.0f,  8.0f,  0.0f,  0.0f, cWalls);

    Door door1(doorArr1,  4.0f, 2.0f, 0.0f,  cWalls, *Walls);
    Door door2(doorArr2, 13.0f, 3.0f, 90.0f, cWalls, *Walls);

    Plane room1( map,  mapWidth, mapHeight, 0.0f, 0.0f, 0.0f, 7.0f);
    Plane room15(map,  mapWidth, mapHeight, 0.0f, 1.0f, 0.0f, 8.0f);

    Plane room2( map2, mapWidth, mapHeight, -8.0f, 0.0f, 0.0f, 7.0f);
    Plane room25(map2, mapWidth, mapHeight, -8.0f, 1.0f, 0.0f, 9.0f);

    glEnable(GL_DEPTH_TEST); 

    while (!glfwWindowShouldClose(window) && gameIsRunning) //Main window loop
    {
        // break;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.1f, 0.3f, 0.3f);
        input(cWalls, position, rotation, window, gameIsRunning);
        
        Walls->bind(GL_TEXTURE0);
        programShader.useProgram();

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 proj  = glm::mat4(1.0f);
        glm::mat4 view  = glm::mat4(1.0f);

        view = glm::rotate(view,  glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::translate(view, position);
        proj = glm::perspective(glm::radians(70.0f), (float)(WIDTH / HEIGHT), 0.01f, 100.0f);

        int viewLoc  = glGetUniformLocation(programShader.shaderProgram,  "view");
        glUniformMatrix4fv(viewLoc,  1, GL_FALSE, glm::value_ptr(view));
        int projLoc  = glGetUniformLocation(programShader.shaderProgram,  "proj");
        glUniformMatrix4fv(projLoc,  1, GL_FALSE, glm::value_ptr(proj));
        int modelLoc  = glGetUniformLocation(programShader.shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        
        part.draw();
        part1.draw(); 
        room1.draw();
        room15.draw();
        room2.draw();
        room25.draw();

        door1.draw(position, view, proj, window, rotation);
        door2.draw(position, view, proj, window, rotation);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete map;
    delete map2;

    delete doorArr1;
    delete doorArr2;

    door1.clear();
    door2.clear();
}