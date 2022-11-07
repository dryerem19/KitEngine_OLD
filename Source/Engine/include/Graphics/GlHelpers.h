//
// Created by dryerem19 on 10/28/22.
//

#pragma once
#include "core.h"

#define EXIT_WITH_ERROR(x) if (!(x)) exit(0);
#define GLCall(x) GLClearError();\
    x;\
    EXIT_WITH_ERROR(GLLogCall(#x, __FILE__, __LINE__))

namespace KitEngine::Graphics
{
    static void GLClearError() {
        while (glGetError() != GL_NO_ERROR);
    }

    static bool GLLogCall(const char* function, const char* file, int line) {
        while (GLenum iError = glGetError()) {
            std::cout << "[OpenGL Error] - (" << iError << "): "
                      << function << " " << file << ": " << line << std::endl;
            return false;
        }
        return true;
    }
}