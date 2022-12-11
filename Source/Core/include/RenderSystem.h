/**
 * @file RenderSystem.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "RenderBackend.h"
#include "BaseCamera.h"
#include "GameLevel.h"

class RenderSystem
{
private:
    RenderSystem() = default;
    RenderSystem(const RenderSystem&) = delete;
    RenderSystem& operator=(const RenderSystem&) = delete;
public:

    static RenderSystem& Instance()
    {
        static RenderSystem instance;
        return instance;
    }

    void Render(const Core::BaseCamera& camera)
    {
        auto& level = Render::GameLevel::Get();
        auto& backend = RenderBackend::Get();
        backend.Clear();

        for (auto& entity : level.mEntities)
        {
            auto model = entity->GetModel();
            if (model)
            {
                for (auto& mesh : model->mMeshes)
                {
                    auto material = mesh->GetMaterial();
                    if (!material)
                    {
                        return;
                    }

                    if (!material->mShader)
                    {
                        return;
                    }

                    material->Use();
                    material->mShader->SetUniformMatrix4fv("uView", 1, GL_FALSE, camera.GetView());
                    material->mShader->SetUniformMatrix4fv("uProjection", 1, GL_FALSE, camera.GetPerspective()); 
                    material->mShader->SetUniformMatrix4fv("uTransform", 1, GL_FALSE, entity->GetTransform().GetModelMatrix());

                    backend.SetGeometry(&mesh->geometry);
                    backend.Render();
                }
            }
        }
    }
};