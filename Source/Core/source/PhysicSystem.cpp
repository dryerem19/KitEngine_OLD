/**
 * @file PhysicSystem.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "pch.h"
#include "PhysicSystem.h"

void PhysicSystem::OnStart()
{
    // Set up the collision configuration and dispatcher
    mCollisionConfig  = std::make_unique<btDefaultCollisionConfiguration>();
    mDispathcer       = std::make_unique<btCollisionDispatcher>(mCollisionConfig.get());

    // Build the broadphase
    mBroadphase       = std::make_unique<btDbvtBroadphase>();

    // Create physic solver
    mSolver           = std::make_unique<btSequentialImpulseConstraintSolver>();

    // Create the physic world
    mDynamicsWorld    = std::make_unique<btDiscreteDynamicsWorld>(mDispathcer.get(), mBroadphase.get(), mSolver.get(), mCollisionConfig.get());
    mDynamicsWorld->setGravity(btVector3(0.f, -10.0f, 0.f));

    // Create physic objects
    auto view = mRegistry.view<RigidbodyComponent, TransformComponent>();
    for (auto entity : view)
    {
        auto &transform = view.get<TransformComponent>(entity);
        auto &rigidbody = view.get<RigidbodyComponent>(entity);

        const auto& pos = transform.GetPosition();
        const auto& rot = glm::quat(transform.GetRotation());

        // Setup initial transformation
        btTransform rbTransform;
        rbTransform.setIdentity();
        rbTransform.setOrigin({ pos.x, pos.y, pos.z });
        rbTransform.setRotation({ rot.x, rot.y, rot.z, rot.w });

        btCollisionShape *pShape = new btEmptyShape();

        // Create the box shape
        if (mRegistry.any_of<BoxColliderComponent>(entity)) {
            const auto& collider = mRegistry.get<BoxColliderComponent>(entity);
            pShape = new btBoxShape(btVector3(collider.mSize.x, collider.mSize.y, collider.mSize.z));
        } 

        // Calculate inertia
        btVector3 localInertia(0.0f, 0.0f, 0.0f);
        if (rigidbody.mMass != 0.0f) {
            pShape->calculateLocalInertia(rigidbody.mMass, localInertia); 
        }

        // Build rigidbody information
        btDefaultMotionState* pMotionState = new btDefaultMotionState(rbTransform);
        btRigidBody::btRigidBodyConstructionInfo cInfo(rigidbody.mMass, pMotionState, pShape, localInertia);
        
        // Create bullet rigidbody object
        rigidbody.mRigidBody = std::make_unique<btRigidBody>(cInfo);

        // Add rigidbody to physic world
        mDynamicsWorld->addRigidBody(rigidbody.mRigidBody.get());

        //mCharacterSystem = new PlayerControllerSystem(*(mDynamicsWorld.get()));
    }
}

void PhysicSystem::OnUpdate()
{
    mDynamicsWorld->stepSimulation(1.0f / 60.0f, 10);
    //mCharacterSystem->update(mRegistry, 1 / 60);
    
    auto view = mRegistry.view<RigidbodyComponent, TransformComponent>();
    for (auto entity : view)
    {
        auto &transform = view.get<TransformComponent>(entity);
        auto &rigidbody = view.get<RigidbodyComponent>(entity);

        btTransform trans;
        rigidbody.mRigidBody->getMotionState()->getWorldTransform(trans);

        glm::mat4 matrix;
        trans.getOpenGLMatrix(glm::value_ptr(matrix));
        transform.SetMatrix(matrix);
    }
}

void PhysicSystem::OnFinish()
{
}
