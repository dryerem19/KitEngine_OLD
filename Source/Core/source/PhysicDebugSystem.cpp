/**
 * @file PhysicDebugSystem.cpp
 * @author Eremenko Denis (mamayma8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-01
 * 
 * @copyright Copyright Eremenko Denis (c) 2023
 * 
 */
#include "pch.h"
#include "PhysicDebugSystem.h"

void PhysicDebugSystem::OnStart()
{
    // Setup debug drawer
    mDebugRenderer = std::make_unique<GLDebugDrawer>();
    mPhysicSystem.GetDynamicsWorld().setDebugDrawer(mDebugRenderer.get());
    mPhysicSystem.GetDynamicsWorld().getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_MAX_DEBUG_DRAW_MODE);
}

void PhysicDebugSystem::OnUpdate()
{
    if (!mDebugRenderer) {
        return;
    }

    // TODO: Move this code to Scene class and find main camera one time for optimize
    auto cameras = mRegistry.view<TransformComponent, CameraComponent>();
    for (auto entity : cameras) {
        const auto&[transform, camera] = cameras.get<TransformComponent, CameraComponent>(entity);

        // const glm::mat4 matMvp = camera.mProj * camera.mView * glm::mat4(1.0f);
        // mDebugRenderer->SetMVP(matMvp);
        // mPhysicSystem.GetDynamicsWorld().debugDrawWorld();

        // if (camera.mCamera->IsMainCamera()) {
        //     const glm::mat4& matProj = camera.mCamera->GetProjection();
        //     const glm::mat4& matView = camera.mCamera->GetView();
        //     const glm::mat4 matMvp = matProj * matView * glm::mat4(1.0f);
        //     mDebugRenderer->SetMVP(matMvp);
        //     mPhysicSystem.GetDynamicsWorld().debugDrawWorld();
        // }
    }
}

void PhysicDebugSystem::OnFinish()
{
    if (mDebugRenderer) {
        mDebugRenderer.release();
    }
}
