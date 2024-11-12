#include <libs.h>
#include <settingsAndVars.h>

void solve(int* map, float* vert, uint* ind, uint countOfUnits, const int mapWidth, const int mapHeight, float xGap, float zGap, float yGap);

Cube::Cube(int* map, int location, int mapWidth, int mapHeight, float xGap, float zGap, float yGap, Collisions& col) {
    uint countOfUnits = 0;

    col._piecesOfMap.push_back({ map, mapWidth, mapHeight, 
                                -xGap + 0.0f,
                                -zGap + 0.0f,
                                -(xGap + mapWidth + 0.0f),
                                -(zGap + mapHeight + 0.0f),
                                xGap,
                                zGap});

    std::cout << col._piecesOfMap[col._piecesOfMap.size() - 1].maxX << std::endl;
    std::cout << col._piecesOfMap[col._piecesOfMap.size() - 1].maxZ << std::endl;
    std::cout << col._piecesOfMap[col._piecesOfMap.size() - 1].minX << std::endl;
    std::cout << col._piecesOfMap[col._piecesOfMap.size() - 1].minZ << std::endl;

    for (int i = 0; i < mapWidth * mapHeight; i++) {
        if (map[i] > 0) countOfUnits++;
    }
    
    size = countOfUnits * 36;

    float vertices[countOfUnits * 48];
    uint  indices[size];

    ind = indices;

    solve(map, vertices, indices, countOfUnits, mapWidth, mapHeight, xGap, zGap, yGap);

    vao = new VAO();
    vbo = new VBO(vertices, sizeof(vertices));
    ebo = new EBO(indices,  sizeof(indices));

    vao->linkAttrib(*vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*) 0);
    vao->linkAttrib(*vbo, 1, 2, GL_FLOAT, 6 * sizeof(float), (void*) (3 * sizeof(float)));
    vao->linkAttrib(*vbo, 2, 1, GL_FLOAT, 6 * sizeof(float), (void*) (5 * sizeof(float)));

    vbo->unbind();
    vao->unbind();
    ebo->unbind();

    this->xGap = xGap;
    this->zGap = zGap;
}

void Cube::draw() {
    vao->bind();
    glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
}

void Cube::bind() {
    vao->bind();
}

Cube::~Cube() {
    vao->deleteVao();
    vbo->deleteVbo();
    ebo->deleteEbo();

    delete vao;
    delete vbo;
    delete ebo;
}