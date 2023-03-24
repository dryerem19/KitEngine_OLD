#pragma once
#include "Components.h"
#include "ISystem.h"

class FPSCameraSystem final : public ISystem
{
public:
    FPSCameraSystem() = default;
    void update(entt::registry& registry, float deltaTime) final override;
};