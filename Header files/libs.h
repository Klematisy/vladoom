#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

#include <vector>
#include <string>
#include <chrono>
#include <thread>

#include "constants.h"

#include "programShader.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "image.h"
#include "Cube.h"
#include "Plane.h"
#include "collisions.h"
#include "Texture.h"
#include "door.h"
#include "symbol.h"
#include "hud.h"

using namespace std::literals::chrono_literals;