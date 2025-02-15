#pragma once

#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "stb/stb_image.h"

#include <vector>
#include <string>
#include <chrono>
#include <thread>

#include "constants.h"

#include "VladEngine.hpp"

#include "door.h"
#include "secret_door.h"
#include "hud.h"

#include "collisions.h"

using namespace std::literals::chrono_literals;