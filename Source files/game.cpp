#include <libs.h>
#include <settingsAndVars.h>

String shaderDir = "Resource files/Shaders/";
String bindShader(std::string dir);

void solve(int *map, float *vert, uint *ind, uint countOfUnits, const int mapWidth, const int mapHeight, float xGap, float zGap);
void input(const Collisions &collisions, glm::vec3 &position, float &rotation, GLFWwindow *window, bool &run);
void matrices(float rotation, glm::vec3 position, ProgramShader ps);
bool gameIsRunning = true;

void game(GLFWwindow* window)
{   
    /*--------------------------------------------------------main code!--------------------------------------------------------*/

    String vertexShaderSrc   = bindShader(shaderDir + "map/map.vert");
    String fragmentShaderSrc = bindShader(shaderDir + "map/map.frag");

    ProgramShader programShader = ProgramShader(vertexShaderSrc.c_str(), fragmentShaderSrc.c_str());

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
        4, 0, 0, 4, 4, 9, 4, 4,
        4, 0, 0, 4, 0, 0, 0, 4,
        1, 0, 0, 4, 4, 0, 4, 4,
        1, 0, 0, 4, 0, 0, 0, 4,
        1, 0, 0, 4, 0, 0, 0, 4,
        0, 0, 0, 4, 0, 0, 0, 4,
        0, 0, 0, 4, 0, 0, 0, 4,
        1, 1, 1, 1, 4, 4, 4, 4,
    };

    int dver[4] {
        9
    };

    glm::vec3 position = glm::vec3(-1.5f, -0.5f, -2.5f);
    float rotation     = 90.0f;
    float rot          = 0.0f;
     
    Cube part(map,      0, mapWidth, mapHeight, 0.0f, 0.0f, 0.0f, collisions);
    Cube part1(map2,    0, mapWidth, mapHeight, 8.0f, 0.0f, 0.0f, collisions);
    Cube part2(dver,    0, 1,        1,         5.0f, 9.0f, 0.0f, collisions);


    Plane room1( map,  mapWidth, mapHeight, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 17.0f);
    Plane room15(map,  mapWidth, mapHeight, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 18.0f);

    Plane room2( map2, mapWidth, mapHeight, -8.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 17.0f);
    Plane room25(map2, mapWidth, mapHeight, -8.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 19.0f);

    // Plane door(doorArr, 1, 1, -5.0f, 0.5f, -9.0f, 9, 0.0f, 0.0f, 0.0f);

    programShader.useProgram(); 
    Texture BWall1("Resource files/images/BlueWall1.jpg", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE0);
    BWall1.unbind();
    BWall1.uniform("tex1", programShader, 0);

    Texture BWall2("Resource files/images/BlueWall2.jpg", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE1);
    BWall2.unbind();
    BWall2.uniform("tex2", programShader, 1);

    Texture BWall3("Resource files/images/BlueWall3.jpg", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE2);
    BWall2.unbind();
    BWall2.uniform("tex3", programShader, 2);

    Texture GWall("Resource files/images/GrayWall.jpg", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE3);
    GWall.unbind();
    GWall.uniform("tex4", programShader, 3);

    Texture Door("Resource files/images/Door.jpg", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE5);
    Door.unbind();
    Door.uniform("door", programShader, 5);

    Texture Potolok("Resource files/images/potolok.jpg", GL_RGBA, GL_UNSIGNED_BYTE, GL_TEXTURE4);
    Potolok.unbind();
    Potolok.uniform("potolok", programShader, 4);

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
        
        BWall1.bind(GL_TEXTURE0);
        BWall2.bind(GL_TEXTURE1);
        BWall3.bind(GL_TEXTURE2);
        GWall.bind(GL_TEXTURE3);
        Door.bind(GL_TEXTURE5);
        Potolok.bind(GL_TEXTURE4);

        programShader.useProgram();
        int viewLoc  = glGetUniformLocation(programShader.shaderProgram, "view");
        glUniformMatrix4fv(viewLoc,  1, GL_FALSE, glm::value_ptr(view));
        int projLoc  = glGetUniformLocation(programShader.shaderProgram, "proj");
        glUniformMatrix4fv(projLoc,  1, GL_FALSE, glm::value_ptr(proj));
        
        part.draw();
        room1.draw();
        room15.draw();
        part1.draw();
        room2.draw();
        room25.draw();
        part2.draw();

        // glm::mat4 model = glm::mat4(1.0f);

        // doorPS.useProgram();
        // int modelLoc = glGetUniformLocation(doorPS.shaderProgram, "model");
        // glUniformMatrix4fv(modelLoc,  1, GL_FALSE, glm::value_ptr(model));
        // viewLoc  = glGetUniformLocation(doorPS.shaderProgram, "view");
        // glUniformMatrix4fv(viewLoc,  1, GL_FALSE, glm::value_ptr(view));
        // projLoc  = glGetUniformLocation(doorPS.shaderProgram, "proj");
        // glUniformMatrix4fv(projLoc,  1, GL_FALSE, glm::value_ptr(proj));

        /*
        // {
        //     ps.useProgram();
        //     glm::mat4 model = glm::mat4(1.0f);
        //     model  = glm::translate(model, glm::vec3(5.0f, 0.0f, 4.0f));
        //     model  = glm::rotate(model,  glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
        //     rot += 0.5f;

        //     int viewCube  = glGetUniformLocation(ps.shaderProgram, "view");
        //     glUniformMatrix4fv(viewCube,  1, GL_FALSE, glm::value_ptr(view));

        //     int modelCube  = glGetUniformLocation(ps.shaderProgram, "model");
        //     glUniformMatrix4fv(modelCube,  1, GL_FALSE, glm::value_ptr(model));

        //     int projCube  = glGetUniformLocation(ps.shaderProgram, "proj");
        //     glUniformMatrix4fv(projCube,  1, GL_FALSE, glm::value_ptr(proj));
        // }
        // partCube.draw();
        //*/
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}