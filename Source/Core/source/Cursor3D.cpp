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

glm::vec3 Cursor3D::GetPickPoint(const Core::BaseCamera& camera)
{
    auto& app = Core::Application::Instance();
    const glm::vec2& frameBufferSize = app.GetWindow()->GetFrameBufferSize();

    // Step 1 - Viewport to NDC
    const glm::vec2 mp = Core::Input::mousePosition;
    glm::vec2 ndc {
        (2.0f * mp.x) / frameBufferSize.x - 1.0f,
        1.0f - (2.0f * mp.y) / frameBufferSize.y
    }; 

    // Step 2 - NDC to view
    glm::vec4 ray_clip { ndc.x, ndc.y, -1.0, 1.0 };

    // Step 3 - 3D Camera coordinates
    const glm::mat4& proj = camera.GetProj();
    glm::mat4 projInv = glm::inverse(proj);
    glm::vec4 ray_eye = projInv * ray_clip;
    ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);

    // Step 4 - 4D World coordinates
    const glm::mat4& view = camera.GetGlmView();
    glm::vec4 ray_world_4d = glm::inverse(view) * ray_eye;
    glm::vec3 ray_world { ray_world_4d.x, ray_world_4d.y, ray_world_4d.z };
    ray_world = glm::normalize(ray_world);

    return ray_world;
}
