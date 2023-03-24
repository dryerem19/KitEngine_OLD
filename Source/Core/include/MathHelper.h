#pragma once
#include "pch.h"

static glm::vec3 btVec3ToGlmVec3(const btVector3& vec)
{
    return { vec.x(), vec.y(), vec.z() };
}