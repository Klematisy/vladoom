#include "settings.h"


// LINE //
void Line::calculate(glm::vec2 p1, glm::vec2 p2) {
    k = (p1.y - p2.y) / (p1.x - p2.x);
    b = (p2.y - k * p2.x);
}

float Line::get_x(float y) {
    return (y - b) / k;
}

float Line::get_z(float x) {
    return k * x + b;
}

// Vmath //

float Vmath::radians(float angle) { return angle * 3.14f / 180.0f; }

float Vmath::sin(float rotation) {
    if      (rotation == 0  ) { return  0.0f; }
    else if (rotation == 90 ) { return  1.0f; }
    else if (rotation == 180) { return  0.0f; }
    else if (rotation == 270) { return -1.0f; }
    else if (rotation == 360) { return  0.0f; }
    else { return std::sin(radians(rotation)); }
}

float Vmath::cos(float rotation) {
    if      (rotation == 0  ) { return  1.0f; }
    else if (rotation == 90 ) { return  0.0f; }
    else if (rotation == 180) { return -1.0f; }
    else if (rotation == 270) { return  0.0f; }
    else if (rotation == 360) { return  1.0f; }
    else { return std::cos(radians(rotation)); }
}

// Index_6 //
Index_6::Index_6(int koif) {
    for (int i = 0; i < 6; i++) {
        indices[i] += koif * 4;
    }
}
void Index_6::convert(uint* arr, int i) {
    for (int j = 0; j < 6; j++) {
        *(arr + i + j) = indices[j];
    }
}

// Index_36 //

Index_36::Index_36(int koif) {
    for (int i = 0; i < 36; i++) {
        indices[i] += koif * 8;
    }
}

void Index_36::convert(uint* arr, int i) {
    for (int j = 0; j < sizeof(indices) / sizeof(int); j++) {
        *(arr + i + j) = indices[j];
    }
}

// Functions

float xR(float x, float y, float rotation) {
    glm::mat2 matrix(Vmath::cos(rotation), -Vmath::sin(rotation), Vmath::sin(rotation), Vmath::cos(rotation));
    x = matrix[0][0] *  x + matrix[0][1] * y;
    return x;
}

float zR(float x, float z, float rotation) {
    glm::mat2 matrix(Vmath::cos(rotation), -Vmath::sin(rotation), Vmath::sin(rotation), Vmath::cos(rotation));
    z = matrix[1][0] * x + matrix[1][1] * z;
    return z;
}

float vec_mod(const glm::vec3 &vec) {
    return glm::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

float vec_mod2D(const glm::vec2 &vec) {
    return glm::sqrt(vec.x * vec.x + vec.y * vec.y);
}

float angle_between_vectors(glm::vec3 v1, glm::vec3 v2) {
    float ab   = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    float moda = vec_mod(v1);
    float modb = vec_mod(v2);
    
    float res = (fabsf(ab / (moda * modb)) > 1.0f) ? (fabsf(ab / (moda * modb)) / (ab / (moda * modb))) : ab / (moda * modb);
    
    return std::acos(res);
}

float angle_between_vectors2D(glm::vec2 v1, glm::vec2 v2) {
    float ab   = v1.x * v2.x + v1.y * v2.y;
    float moda = vec_mod2D(v1);
    float modb = vec_mod2D(v2);
    
    float res = (fabsf(ab / (moda * modb)) > 1.0f) ? (fabsf(ab / (moda * modb)) / (ab / (moda * modb))) : ab / (moda * modb);
    
    return std::acos(res);
}

glm::vec2 take_vector2D(const glm::vec2 &v1, const glm::vec2 &v2) {
    return glm::vec2(v2.x - v1.x, v2.y - v1.y);
}

void multiply_vec_by_scalar(glm::vec3 &vector, float scalar) {
    vector = glm::vec3(vector.x * scalar, vector.y * scalar, vector.z * scalar);
}

bool inObj(const Map &map, const glm::vec3 &p) {
    return (map.maxX > p.x && p.x > map.minX && map.maxZ > p.z && p.z > map.minZ);
}

template <typename T>
void remove(std::vector<T>& v, size_t index) {
    v.erase(v.begin() + index);
}

bool Collides(int stX, int stZ, int x, int z) {
    return map.get()[12 + (stX - x) + (stZ - z) * 5] > 0;
}

int type_of_colls(int stX, int stZ, int x, int z) {
    return map.get()[12 + (stX - x) + (stZ - z) * 5];
}

bool CollidesRect(int startX, int startZ, float x, float z, float x_half_extent, float z_half_extent) {
    return Collides(startX, startZ, std::ceil(x - x_half_extent), std::ceil(z - z_half_extent))
        || Collides(startX, startZ, std::ceil(x + x_half_extent), std::ceil(z - z_half_extent))
        || Collides(startX, startZ, std::ceil(x + x_half_extent), std::ceil(z + z_half_extent))
        || Collides(startX, startZ, std::ceil(x - x_half_extent), std::ceil(z + z_half_extent));
}

std::unique_ptr<int> check_collisions(const Entity &creature, const Collisions &colls) {
    int x, z, x1, z1;
    glm::vec3 point_pos = creature.position;
    
    int *arr = new int[25] {
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0
    };

    for (const Map *path_of_map : colls._piecesOfMap) {
        for (float rot = 0.0f; rot < 360.0f; rot+=45.0f) {
            point_pos = creature.position;

            x = std::ceil(point_pos.x + path_of_map->gap_x);
            z = std::ceil(point_pos.z + path_of_map->gap_z);

            point_pos.x += cos(rot);
            point_pos.z += sin(rot);

            x1 = std::ceil(point_pos.x + path_of_map->gap_x);
            z1 = std::ceil(point_pos.z + path_of_map->gap_z);

            if (inObj(*path_of_map, point_pos) && path_of_map->obj[abs(x1) + abs(z1) * path_of_map->width] > 0) {
                arr[12 + (x - x1) + (z - z1) * 5] = path_of_map->obj[abs(x1) + abs(z1) * path_of_map->width];
            }
        }
    }
     
    return (std::unique_ptr<int>) arr;
}