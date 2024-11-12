#include <libs.h>

void matrices(float rotation, glm::vec3 position, ProgramShader ps) {
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 proj  = glm::mat4(1.0f);
    glm::mat4 view  = glm::mat4(1.0f);

    view  = glm::rotate(view,  glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    view  = glm::translate(view, position);
    proj  = glm::perspective(glm::radians(80.0f), (float)(640 / 480), 0.1f, 100.0f);

    int modelLoc = glGetUniformLocation(ps.shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    int viewLoc = glGetUniformLocation(ps.shaderProgram, "view");
    glUniformMatrix4fv(viewLoc,  1, GL_FALSE, glm::value_ptr(view));

    int projLoc = glGetUniformLocation(ps.shaderProgram, "proj");
    glUniformMatrix4fv(projLoc,  1, GL_FALSE, glm::value_ptr(proj));
}