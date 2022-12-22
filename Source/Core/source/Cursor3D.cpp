/**
 * @file Cursor3D.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "pch.h"
#include "Cursor3D.h"

glm::vec3 Cursor3D::GetPickPoint(const Core::BaseCamera& camera, const glm::vec2& viewport)
{
    auto& app = Core::Application::Instance();
    
    float mouseX = Core::Input::mousePosition.x;
    float mouseY = Core::Input::mousePosition.y;

    glm::vec2 normalizedCoords = GetNormalizedDeviceCoords(mouseX, mouseY);
    glm::vec4 clipCoords = glm::vec4(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
    glm::vec4 eyeCoords = ToEyeCoords(clipCoords, camera);
    glm::vec3 worldRay = ToWorldCoords(eyeCoords, camera);

    return worldRay;
}

glm::vec3 Cursor3D::ToWorldCoords(const glm::vec4 &eyeCoords, const Core::BaseCamera &camera)
{
    glm::mat4 invertedView = glm::inverse(camera.GetGlmView());
    glm::vec4 rayWorld = invertedView * eyeCoords;
    glm::vec3 mouseRay = glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z);
    mouseRay = glm::normalize(mouseRay);
    return mouseRay;
}

glm::vec4 Cursor3D::ToEyeCoords(const glm::vec4 &clipCoords, const Core::BaseCamera &camera)
{
    const glm::mat4& proj = camera.GetProj();
    glm::mat4 projInv = glm::inverse(proj);

    glm::vec4 eyeCoords = projInv * clipCoords;
    return glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 1.0f);
}

glm::vec2 Cursor3D::GetNormalizedDeviceCoords(const float &mouseX, const float &mouseY)
{
    auto& app = Core::Application::Instance();
    float width = app.GetWindow()->GetWidth();
    float height = app.GetWindow()->GetHeight();

    float x = (2.0f * mouseX) / width - 1.0f;
    float y = (2.0f * mouseY) / height - 1.0f;

    return glm::vec2(x, y);
}
