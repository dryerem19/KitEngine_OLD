//
// Created by piokxix on 04.11.22.
//
#include "pch.h"
#include "BaseCamera.h"

// Modify dryerem19 30.12.2022

Core::BaseCamera::BaseCamera()
    : mFov(45),
      mAspect(1.778f), // 1280 / 720
      mNearClip(0.1f),
      mFarClip(1000.0f),
      mPosition(0.0f),
      mProjection(1.0f),
      mViewProjection(1.0f),
      mView(1.0f)
{
    SetProjection(glm::radians(mFov), mAspect, mNearClip, mFarClip);
    UpdateView();
}

Core::BaseCamera::BaseCamera(const float &fov, const float &aspect, const float &near, const float &far)
    : mFov(fov),
      mAspect(aspect),
      mNearClip(near),
      mFarClip(far),
      mPosition(0.0f),
      mProjection(1.0f),
      mViewProjection(1.0f),
      mView(1.0f)
{
    SetProjection(glm::radians(mFov), mAspect, mNearClip, mFarClip);
    UpdateView();
}      

void Core::BaseCamera::ScreenToWorldPoint(const glm::vec2 &position, const glm::vec2& screen, glm::vec3& outOrigin, glm::vec3& outDirection)
{
    // Преобразование координат мыши из пространства экрана в нормализованное пространство устройства
    // NDC - это пространство OpenGL в диапазоне от -1 (левый край) до 1 (правый край) 
    glm::vec4 rayStartNdc(
        (position.x / screen.x - 0.5f) * 2.0f, // [0, width]  -> [-1, 1]
        (position.y / screen.y - 0.5f) * 2.0f, // [0, height] -> [-1, 1]
        -1.0f,                                 // Near plane
        1.0f
    );

    glm::vec4 rayEndNdc(
        rayStartNdc.x,
        rayStartNdc.y,
        0.0f,
        1.0f
    );

    // Матрица проекции переходит из пространства камеры в NDC
    // Таким образом, обратная матрица проекции переходит из NDC в пространство камеры
    glm::mat4 projInv = glm::inverse(mProjection);

    // Матрица вида переходит из мирового пространства в пространство камеры
    // Таким образом, обратная матрица вида переходит из пространства камеры в пространство мира
    glm::mat4 viewInv = glm::inverse(mView);

    // Вычесляем начало луча в пространстве камеры
    glm::vec4 rayStartCamera = projInv * rayStartNdc;
    rayStartCamera /= rayStartCamera.w;

    // Вычисляем начало луча в пространства мира
    glm::vec4 rayStartWorld = viewInv * rayStartCamera;
    rayStartWorld /= rayStartWorld.w;

    // Вычисляем конец луча в пространства камеры
    glm::vec4 rayEndCamera = projInv * rayEndNdc;
    rayEndCamera /= rayEndCamera.w;

    // Вычисляем конец луча в пространстве мира
    glm::vec4 rayEndWorld = viewInv * rayEndCamera;
    rayEndWorld /= rayEndWorld.w;

    // Направление луча в пространстве мира
    glm::vec3 rayDirWorld(rayEndWorld - rayStartWorld);
    rayDirWorld = glm::normalize(rayDirWorld);

    outOrigin = glm::vec3(rayStartWorld);
    outDirection = rayDirWorld;
}

glm::vec3 Core::BaseCamera::ScreenToWorldToPoint(const glm::vec2 &position, const glm::vec2& screen)
{
    glm::vec4 viewport = glm::vec4(0, 0, screen.x, screen.y);
    glm::vec3 wincoord = glm::vec3(position.x, screen.y - position.y - 1, mNearClip);
    glm::vec3 objcoord = glm::unProject(wincoord, mView, mProjection, viewport);
    return objcoord;
}

glm::vec3 Core::BaseCamera::CreateRay(const glm::vec2 &mousePosition, const glm::vec2 &screenSize)
{
    // Translation of coordinates from the display range to the normalized OpenGL range [-1; 1]
    float mouseX = mousePosition.x / (screenSize.x * 0.5f) - 1.0f;
    float mouseY = mousePosition.y / (screenSize.y * 0.5f) - 1.0f;

    // Matrix of the view-projection in the space of the world
    glm::mat4 invertViewProjection = glm::inverse(mProjection * mView);
    glm::vec4 screenPosition = glm::vec4(mouseX, -mouseY, 1.0f, 1.0f);
    glm::vec3 worldPosition = invertViewProjection * screenPosition;

    glm::vec3 direction = glm::normalize(glm::vec3(worldPosition));
    return direction;  
}

void Core::BaseCamera::OnUpdate()
{
    UpdateView();
    mViewProjection = mProjection * mView;
}

glm::vec3 Core::BaseCamera::GetUp() const
{
    return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::vec3 Core::BaseCamera::GetRight() const
{
    return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
}

glm::vec3 Core::BaseCamera::GetForward() const
{
    return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
}

glm::quat Core::BaseCamera::GetOrientation() const
{
    return glm::quat(glm::vec3(-mPitch, -mYaw, 0.0f));
}

void Core::BaseCamera::SetProjection(const float& fov, const float& aspect, const float& near, const float& far)
{
    mProjection = glm::perspective(glm::radians(mFov), mAspect, mNearClip, mFarClip);
}

void Core::BaseCamera::UpdateProjection()
{
    mAspect = mViewportWidth / mViewportHeight;
    SetProjection(glm::radians(mFov), mAspect, mNearClip, mFarClip);
}

void Core::BaseCamera::UpdateView()
{
    glm::quat orientation = GetOrientation();
    mView = glm::translate(glm::mat4(1.0f), mPosition) * glm::toMat4(orientation);
    mView = glm::inverse(mView);
}