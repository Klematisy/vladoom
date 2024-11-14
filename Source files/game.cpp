#include <libs.h>
#include <settingsAndVars.h>

const static String shaderDir = "Resource files/Shaders/";
String bindShader(std::string dir);

void input(const Collisions &collisions, glm::vec3 &position, float &rotation, GLFWwindow *window, bool &run);
void matrices(float rotation, glm::vec3 position, ProgramShader ps);
bool gameIsRunning = true;

void game(GLFWwindow* window)
{   
    /*--------------------------------------------------------main code!--------------------------------------------------------*/

    String vertexShaderSrc   = bindShader(shaderDir + "map/map.vert");
    String fragmentShaderSrc = bindShader(shaderDir + "map/map.frag");

    ProgramShader programShader = ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    ProgramShader lol = ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());

    ProgramShader doorPS = ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());
    // ProgramShader door = ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());

    Collisions collisions;

    /*
    const int mapWidth  = 20;
    const int mapHeight = 20;
    int map[mapWidth * mapHeight] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
        1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    //*/
    
    const int mapWidth  = 8;
    const int mapHeight = 11;
    int map[mapWidth * mapHeight] {
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

    int map2[mapWidth * mapHeight] {
        4, 4, 4, 4, 4, 4, 4, 4,
        4, 0, 0, 4, 4, 4, 4, 4,
        4, 0, 0, 0, 0, 0, 0, 4,
        4, 0, 0, 4, 4, 6, 4, 4,
        4, 0, 0, 4, 0, 0, 0, 4,
        1, 0, 0, 4, 4, 0, 4, 4,
        1, 0, 0, 4, 0, 0, 0, 4,
        1, 0, 0, 4, 0, 0, 0, 4,
        0, 0, 0, 4, 0, 0, 0, 4,
        0, 0, 0, 4, 0, 0, 0, 4,
        1, 1, 1, 1, 4, 4, 4, 4,
    };

    int dver[4] {
        6
    };

    glm::vec3 position = glm::vec3(-1.5f, -0.5f, -2.5f);
    float rotation     = 90.0f;
    float rot          = 0.0f;
    
    Cube part (map,     0, mapWidth, mapHeight, 1.0f, 0.0f,  0.0f, collisions);
    Cube part1(map2,    0, mapWidth, mapHeight, 1.0f, 8.0f,  0.0f, collisions);
    Cube part2(dver,    0, 1,        1,         0.3f, 5.35f, 9.0f, collisions);

    Plane room1( map,  mapWidth, mapHeight, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 7.0f);
    Plane room15(map,  mapWidth, mapHeight, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 8.0f);

    Plane room2( map2, mapWidth, mapHeight, -8.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 7.0f);
    Plane room25(map2, mapWidth, mapHeight, -8.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 9.0f);

    programShader.useProgram();
    Texture Walls("Resource files/images/atlas.png", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    Walls.unbind();
    Walls.uniform("tex0", programShader, 0);

    glEnable(GL_DEPTH_TEST); 

    while (!glfwWindowShouldClose(window) && gameIsRunning) //Main window loop
    {
        input(collisions, position, rotation, window, gameIsRunning);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.1f, 0.3f, 0.3f);

        glm::mat4 proj = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);

        view = glm::rotate(view,  glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::translate(view, position);
        proj = glm::perspective(glm::radians(70.0f), (float)((WIDTH - 200) / HEIGHT), 0.01f, 100.0f);

        int viewLoc  = glGetUniformLocation(programShader.shaderProgram, "view");
        glUniformMatrix4fv(viewLoc,  1, GL_FALSE, glm::value_ptr(view));
        int projLoc  = glGetUniformLocation(programShader.shaderProgram, "proj");
        glUniformMatrix4fv(projLoc,  1, GL_FALSE, glm::value_ptr(proj));
        
        programShader.useProgram();
        Walls.bind(GL_TEXTURE0);
        part.draw();
        part1.draw();
        room1.draw();
        room15.draw();
        room2.draw();
        room25.draw();
        part2.draw();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
