//
// Created by dryerem19 on 21.10.22.
//

#pragma once
#include "KitEnginePch.h"

#define EXIT_WITH_ERROR(x) if (!(x)) exit(0);
#define GLCall(x) GLClearError();\
    x;\
    EXIT_WITH_ERROR(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

namespace KitEngine::Graphics
{

}