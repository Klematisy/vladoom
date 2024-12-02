
struct Player {
    glm::vec3 position;
    float rotation;
    uint typeOfGun;
    int hitPoints = 100;
    int ammo = 100;
    int score = 0;
    uint lives = 4;
};

struct Enemy {
    glm::vec3 position;
    uint typeOfGun;
    int hitPoints = 100;
};