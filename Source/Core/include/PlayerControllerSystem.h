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

class PlayerControllerSystem final : public ISystem
{
public:
    PlayerControllerSystem();
    void update(entt::registry& registry, float deltaTime) final override;
private:

    /**
     * @brief Обрабатывает ввод с клавиатуры для движения камеры
     */
    void processKeyboardMovement(const PlayerComponent& player,
        TransformComponent& transform, const CameraComponent& camera);
    
    /**
     * @brief Обрабатывает ввод с мыши для вращения камеры
     */
    void processMouseMovement(const PlayerComponent& player,
        TransformComponent& transform, CameraComponent& camera, const float&);

    /**
     * @brief Обновляет матрицу вида и проекции камеры
     * @param camera 
     */
    void updateCamera(CameraComponent&, TransformComponent&);

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