//
// Created by dryerem19 on 21.10.22.
//

#include "Graphics/Renderer.h"

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum iError = glGetError()) {
        std::cout << "[OpenGL Error] - (" << iError << "): "
                  << function << " " << file << ": " << line << std::endl;
        return false;
    }
    return true;
}

namespace KitEngine::Graphics
{

}

