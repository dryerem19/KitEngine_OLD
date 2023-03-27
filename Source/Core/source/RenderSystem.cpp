/**
 * @file RenderSystem.cpp
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief Render system implementation
 * @version 0.1
 * @date 2023-01-31
 * 
 * @copyright Copyright Denis Eremenko (c) 2023
 * 
 */
#include "pch.h"
#include "RenderSystem.h"

RenderSystem::RenderSystem(entt::registry &registry)
    : System(registry)
{
}

void RenderSystem::OnStart()
{
}

void RenderSystem::OnUpdate()
{
    Render::Renderer::Clear();

    auto cameras = mRegistry.view<TransformComponent, CameraComponent>();
    auto models  = mRegistry.view<TransformComponent, ModelComponent>();
    auto lights  = mRegistry.view<TransformComponent, LightComponent>();

    for (auto [cameraEntity, cameraTransform, cameraComponent] : cameras.each())
    {
        for (auto [modelEntity, modelTransform, modelComponent] : models.each())
        {
            for (auto& mesh : modelComponent.mModel->mMeshes)
            {
                auto& shader = mesh->mMaterial.mShader;
                if (!shader) {
                    continue;
                }

                mesh->mMaterial.Bind();
                shader->SetVec("uViewPos", cameraTransform.mPosition);

                for (auto& light : lights)
                {
                    glm::vec3 position = lights.get<TransformComponent>(light).mPosition;
                    lights.get<LightComponent>(light).SendToShader(shader, position);
                }

                glm::mat4 modelTransformMatrix = modelTransform.GetMatrix();
                glm::mat4 mvp = cameraComponent.mViewProjMatrix * modelTransformMatrix;
                
                
                // Debugging output
                // std::cout << "Model transform matrix: " << glm::to_string(modelTransformMatrix) << std::endl;
                // std::cout << "View matrix: " << glm::to_string(cameraView) << std::endl;
                // std::cout << "Projection matrix: " << glm::to_string(cameraProj) << std::endl;
                
                shader->SetMat("u_mvp_matrix", mvp);
                shader->SetMat("u_model_matrix", modelTransformMatrix);

                Render::Renderer::Draw(mesh->geometry.vao, mesh->geometry.ibo);
            }
        } 
    }
}

void RenderSystem::OnFinish()
{
}
