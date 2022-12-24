//
// Created by piokxix on 04.11.22.
//
#include "pch.h"
#include "BaseCamera.h"


void Core::BaseCamera::SetPerspective(float fovy, float aspect, float zNear, float zFar) 
{
    mFovy = fovy;
    mAspect = aspect;
    mZNear = zNear;
    mZFar = zFar;
    mProjection = glm::perspective(fovy, aspect, zNear, zFar);
}

void Core::BaseCamera::SetLookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up) {
    mView = glm::lookAt(eye,center,up);
}

const float* Core::BaseCamera::GetView() const {
    return glm::value_ptr(mView);
}

const float* Core::BaseCamera::GetPerspective() const {
    return glm::value_ptr(mProjection);
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

float &Core::BaseCamera::GetZNear()
{
    return mZNear;
}

void Core::BaseCamera::UpdateAspect(const float &aspect)
{
    mAspect = aspect;
    SetPerspective(mFovy, mAspect, mZNear, mZFar);
}
