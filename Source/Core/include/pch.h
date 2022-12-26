#pragma once

// STL includes
#include <filesystem>
#include <functional>
#include <exception>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <list>


// External includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>
#include <sail/sail-c++/sail-c++.h>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <imgui_internal.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <yaml-cpp/yaml.h>
#include <entt/entt.hpp>

#include <AL/alc.h>
#include <AL/alext.h>
#include <sndfile.h>

#include <BulletDynamics/btBulletDynamicsCommon.h>
#include <LinearMath/btIDebugDraw.h>

#include "Helpers.h"