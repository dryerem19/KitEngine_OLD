#pragma once
#include "pch.h"

struct ISystem
{
    virtual void update(entt::registry& registry, float deltaTime) = 0;
    virtual ~ISystem() = default;
};