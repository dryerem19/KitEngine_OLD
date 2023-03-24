/**
 * @file PhysicSystem.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "Components.h"
#include "System.h"
#include "Physics/GLDebugDrawer.h"


#include "PlayerControllerSystem.h"



class PhysicSystem : public System
{
private:
    std::unique_ptr<btBroadphaseInterface> mBroadphase;
    std::unique_ptr<btCollisionDispatcher> mDispathcer;
    std::unique_ptr<btConstraintSolver> mSolver;
    std::unique_ptr<btCollisionConfiguration> mCollisionConfig;
    std::unique_ptr<btDiscreteDynamicsWorld> mDynamicsWorld;
    std::unique_ptr<GLDebugDrawer> mDebugRenderer;


    //PlayerControllerSystem* mCharacterSystem;

public:
    PhysicSystem(entt::registry& registry) :
        System(registry) { }

    inline btDiscreteDynamicsWorld& GetDynamicsWorld() { return *mDynamicsWorld; }

    void OnStart()  final override;
    void OnUpdate() final override;
    void OnFinish() final override;
};