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
        auto& level = GameLevel::Get();
        auto& backend = RenderBackend::Get();
        backend.Clear();

        KitLight* light = level._lights.empty() ? nullptr : level._lights[0].get();

        for (auto& entity : level._objects)
        {
            if(entity->Type() != KIT_OBJECT_ENTITY)
                continue;
            auto model = entity->dnm_cast_entity()->GetModel();
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
                    if(light)
                    {
                        material->mShader->SetUniform3f("uLigthPos", light->transform.GetPosition().x,light->transform.GetPosition().y,
                                                                     light->transform.GetPosition().z);
                        material->mShader->SetUniform4f("uLightColor", light->mColor[0], light->mColor[1], 
                                                                         light->mColor[2], light->mColor[3]);
                        material->mShader->SetUniform1f("uAmbientStrength", light->mAmbientStrength);
                    }
                    material->mShader->SetUniformMatrix4fv("uView", 1, GL_FALSE, camera.GetView());
                    material->mShader->SetUniformMatrix4fv("uProjection", 1, GL_FALSE, camera.GetPerspective()); 
                    material->mShader->SetUniformMatrix4fv("uTransform", 1, GL_FALSE, entity->transform.GetModelMatrix());

                    backend.SetGeometry(&mesh->geometry);
                    backend.Render();
                }
            }
        }
        level.GetSkybox().Render(camera);
    }
};