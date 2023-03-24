/**
 * @file PhysicDebugSystem.h
 * @author Eremenko Denis (mamayma8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-01
 * 
 * @copyright Copyright Denis Eremenko (c) 2023
 * 
 */
#pragma once
#include "System.h"
#include "Components.h"
#include "PhysicSystem.h"
#include "Physics/GLDebugDrawer.h"

class PhysicDebugSystem : public System
{
private:
    PhysicSystem& mPhysicSystem;
    std::unique_ptr<GLDebugDrawer> mDebugRenderer;
public:
    PhysicDebugSystem(entt::registry& registry, PhysicSystem& physicSystem) :
        System(registry), mPhysicSystem(physicSystem) { }

    void OnStart()  override;
    void OnUpdate() override;
    void OnFinish() override;
};