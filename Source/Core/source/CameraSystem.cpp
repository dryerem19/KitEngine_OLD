#include "pch.h"
#include "CameraSystem.h"

void CameraSystem::update(entt::registry &registry, float deltaTime)
{
    // // Получаем все сущности CameraComponent,TransformComponent, TargetComponent
    // auto view = registry.view<CameraComponent, TransformComponent, TargetComponent>();

    // // Обновляем CameraComponent
    // for (auto entity : view)
    // {
    //     auto& camera = view.get<CameraComponent>(entity);
    //     auto& target = view.get<TargetComponent>(entity);
    //     auto& transform = view.get<TransformComponent>(entity);
        
    //     camera.proj = glm::perspective(glm::radians(camera.fov), camera.aspect, camera.near, camera.far);
    //     camera.view = glm::lookAt(transform.GetPosition(), target.target, glm::vec3(0.0f, 1.0f, 0.0f))
    // }
}