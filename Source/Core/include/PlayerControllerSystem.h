/**
 * @file PlayerControllerSystem.h
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-07
 * 
 * @copyright Copyright Denis Eremenko (c) 2023
 * 
 */
#pragma once
#include "ISystem.h"
#include "Components.h"
#include "FPSCameraSystem.h"

class PlayerControllerSystem final : public ISystem
{
private:
    FPSCameraSystem mCameraSystem;
public:
    PlayerControllerSystem();
    void update(entt::registry& registry, float deltaTime) final override;
private:

    void updatePosition(TransformComponent& transform, CameraComponent& camera, PlayerComponent& player);
    void updateOrientation(TransformComponent& transform, CameraComponent& camera, PlayerComponent& player, glm::vec2& delta);

    /**
     * @brief Проверка того, находится ли персонаж на земле методом луча
     * 
     * @param rigidbodyComponent Компонент физического тела
     * @return true в случае, если перонаж находится на земле
     * @return false если персонаж в воздухе
     */
    bool checkIfGroundedRay(const RigidbodyComponent& rigidbodyComponent);

    /**
     * @brief Проверка того, находится ли персонаж на земле методом перебора контактных пар
     * 
     * @param rigidbodyComponent Компонент физического тела
     * @return true в случае, если перонаж находится на земле
     * @return false если персонаж в воздухе
     */
    bool checkIfGroundedBruteforce(const RigidbodyComponent& rigidbodyComponent);
};