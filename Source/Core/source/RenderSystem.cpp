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
                // shader->SetMat("uView", cameraComponent.pCamera->GetView());
                // shader->SetMat("uProjection", cameraComponent.pCamera->GetProjection());
                shader->SetVec("uViewPos", cameraComponent.pCamera->GetPosition());

                for (auto& light : lights)
                {
                    glm::vec3 position = lights.get<TransformComponent>(light).GetPosition();
                    lights.get<LightComponent>(light).SendToShader(shader, position);
                }

                glm::mat4 modelTransformMatrix = modelTransform.GetMatrix();
                glm::mat4 modelViewProjectionMatrix = modelTransformMatrix * cameraComponent.pCamera->GetView() * cameraComponent.pCamera->GetProjection();
                shader->SetMat("u_mvp_matrix", modelViewProjectionMatrix);
                shader->SetMat("u_model_matrix", modelTransformMatrix);

                Render::Renderer::Draw(mesh->geometry.vao, mesh->geometry.ibo);
            }
        } 
    }


    // auto lights = mRegistry.view<LightComponent, TransformComponent>();

    // auto models_entity = mRegistry.view<TransformComponent, ModelComponent>();
    // for (auto model_entity : models_entity)
    // {
    //     auto &transformComponent = models_entity.get<TransformComponent>(model_entity);
    //     auto &modelComponent = models_entity.get<ModelComponent>(model_entity);

    //     auto& model = modelComponent.mModel;
    //     if (!model) {
    //         continue;
    //     }

    //     for (auto& mesh : model->mMeshes)
    //     {
    //         auto& shader = mesh->mMaterial.mShader;
    //         if (!shader) {
    //             continue;
    //         }

    //         mesh->mMaterial.Bind();
    //         // shader->SetMat("uView", ptrMainCamera->GetView());
    //         // shader->SetMat("uProjection", ptrMainCamera->GetProjection());
    //         // shader->SetVec("uViewPos", ptrMainCamera->GetPosition());

    //         shader->SetMat("uView", ptrMainCamera->mView);
    //         shader->SetMat("uProjection", ptrMainCamera->mProj);
    //         shader->SetVec("uViewPos", ptrMainCamera->getWorldPosition());

    //         for (auto& light : lights)
    //         {
    //             glm::vec3 position = lights.get<TransformComponent>(light).GetPosition();
    //             lights.get<LightComponent>(light).SendToShader(shader, position);
    //         }

    //         // glm::mat4 mvpMatrix = ptrMainCamera->GetProjection() * ptrMainCamera->GetView() * transformComponent.GetMatrix();
    //         // shader->SetMat("u_mvp_matrix", mvpMatrix);
    //         shader->SetMat("u_mvp_matrix", ptrMainCamera->mViewProj);
    //         shader->SetMat("u_model_matrix", transformComponent.GetMatrix());

    //         Render::Renderer::Draw(mesh->geometry.vao, mesh->geometry.ibo);
    //         //mesh->mMaterial.Unbind();
    //     }
    // }
}

void RenderSystem::OnFinish()
{
}
