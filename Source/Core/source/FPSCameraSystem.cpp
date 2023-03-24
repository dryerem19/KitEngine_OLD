#include "pch.h"
#include "FPSCameraSystem.h"

void FPSCameraSystem::update(entt::registry &registry, float deltaTime)
{
    // // Получаем все компоненты камеры и трансформации
    // auto view = registry.view<TransformComponent, CameraComponent>();
    // for (auto [entity, transform, camera] : view.each())
    // {
    //     // Получаем позицию, на которую смотрит камера
    //     glm::vec3 lookAt = transform.mPosition + transform.forward();

    //     // Обновляем матрицу вида
    //     camera.mView = glm::lookAt(transform.mPosition, lookAt, transform.up());

    //     // Обновляем матрицу проекции
    //     camera.mProj = glm::perspective(glm::radians(camera.mFov), camera.mAspect, camera.mNear, camera.mFar);

    //     // Обновляем матрицу вида и проекции
    //     camera.mViewProj = camera.mView * camera.mProj;
    // }
}