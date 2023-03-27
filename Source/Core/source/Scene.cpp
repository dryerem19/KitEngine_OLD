/**
 * @file Scene.cpp
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief Scene implementation
 * @version 0.1
 * @date 2023-01-29
 * 
 * @copyright Copyright Denis Eremenko (c) 2023
 * 
 */
#include "pch.h"
#include "Scene.h"
#include "Entity.h"
#include "TransformComponent.h"

Scene::Scene()
    : mRenderSystem(mRegistry), mPhysicSystem(mRegistry), mPhysicDebugSystem(mRegistry, mPhysicSystem)
{

}

Entity Scene::CreateEntity(const std::string& name)
{
    std::string entityName = name.empty() ? "Entity" : name;

    entt::entity entityId = mRegistry.create();
    mEntities.push_back(entityId);

    Entity entity(entityId, this);
    entity.AddComponent<TransformComponent>();
    entity.AddComponent<TagComponent>(entityName);
    return entity;
}

void Scene::OnViewportResize(float width, float height)
{
    auto view = mRegistry.view<CameraComponent>();
    for (auto entity : view)
    {
        auto& camera = view.get<CameraComponent>(entity);
       // camera.mAspect = width / height;

        camera.mViewportWidth = width;
        camera.mViewportHeight = height;

        //camera.pCamera->SetViewportSize(width, height);
    }
}

void Scene::OnStart()
{
    mRenderSystem.OnStart();

    mPhysicSystem.OnStart();
    mPhysicDebugSystem.OnStart();
}

void Scene::OnUpdate()
{
    //mPhysicSystem.OnUpdate();

    for (auto& system : mSystems)
    {
        system->update(mRegistry, 1 / (float)60);
    }

    // auto view = mRegistry.view<CameraComponent>();
    // for (auto entity : view)
    // {
    //     auto& cameraComponent = view.get<CameraComponent>(entity);
    //     //cameraComponent.mCamera.OnUpdate();
    //     cameraComponent.pCamera->OnUpdate();
    // }

    mRenderSystem.OnUpdate();
    //mPhysicDebugSystem.OnUpdate();
}

void Scene::OnFinish()
{
    mRenderSystem.OnFinish();

    mRegistry.destroy(mEntities.begin(), mEntities.end());
    mEntities.clear();
}
