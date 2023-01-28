/**
 * @file Physics.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "pch.h"
#include "Physics.h"

KitEngine::Physics::PhysicObject::PhysicObject(const glm::vec3 &position, btDiscreteDynamicsWorld &world, Type type)
    : mWorld(world),
      mType(type)
{

}

KitEngine::Physics::PhysicObject::~PhysicObject()
{
    if (mBody)
    {
        mWorld.removeRigidBody(mBody.get());
    }
}

glm::vec3 KitEngine::Physics::PhysicObject::GetPosition() const
{
    const btVector3& position = mBody->getWorldTransform().getOrigin();
    return { position.x(), position.y(), position.z() };
}

void KitEngine::Physics::PhysicObject::SetPosition(const glm::vec3& position)
{
    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(btVector3(position.x, position.y, position.z));
    mBody->setWorldTransform(std::move(transform));
}

void KitEngine::Physics::PhysicObject::SetLinearVelocity(const glm::vec3 &velocity)
{
    mBody->setLinearVelocity({ velocity.x, velocity.y, velocity.z });
}

glm::vec3 KitEngine::Physics::PhysicObject::GetLinearVelocity() const
{
    const btVector3& velocity = mBody->getLinearVelocity();
    return { velocity.x(), velocity.y(), velocity.z() };
}

void KitEngine::Physics::PhysicObject::SetAngularVelocity(const glm::vec3 &velocity)
{
    mBody->setAngularVelocity({ velocity.x, velocity.y, velocity.z });
}

glm::vec3 KitEngine::Physics::PhysicObject::GetAngularVelocity() const
{
    const btVector3& velocity = mBody->getAngularVelocity();
    return { velocity.x(), velocity.y(), velocity.z() };
}

void KitEngine::Physics::PhysicObject::SetAngularFactor(const glm::vec3 &factor)
{
    mBody->setAngularFactor( { factor.x, factor.y, factor.z } );
}

glm::vec3 KitEngine::Physics::PhysicObject::GetAngularFactor() const
{
    const btVector3& factor = mBody->getAngularFactor();
    return { factor.x(), factor.y(), factor.z() };
}

void KitEngine::Physics::PhysicObject::SetDamping(float linear, float angular)
{
    mBody->setDamping(linear, angular);
}

void KitEngine::Physics::PhysicObject::SetImpulse(const glm::vec3 &force, const glm::vec3 &position)
{
    mBody->applyImpulse({ force.x, force.y, force.z }, { position.x, position.y, position.z });
}

void KitEngine::Physics::PhysicObject::Activate()
{
    mBody->activate(true);
}

void KitEngine::Physics::PhysicObject::SetTransform(const glm::mat4 &transform)
{
    btTransform t;
    t.setFromOpenGLMatrix(glm::value_ptr(transform));
    mBody->setWorldTransform(std::move(t));
}

glm::mat4 KitEngine::Physics::PhysicObject::GetTransform()
{
    btTransform transform = mBody->getWorldTransform();
    float m[16];
    transform.getOpenGLMatrix(m);
    return glm::make_mat4x4(m);
}

void KitEngine::Physics::PhysicObject::CreateRigidBody(const glm::vec3 &position, btCollisionShape *pShape, bool isGhost)
{
    btAssert((!pShape || pShape->getShapeType() != INVALID_SHAPE_PROXYTYPE));

    btScalar mass = 100.0f;
    btVector3 localInertia(0.0f, 0.0f, 0.0f);
    if (mType == Type::STATIC) {
        mass = 0.0f;
    } else {
        pShape->calculateLocalInertia(mass, localInertia);
    }

    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(btVector3(position.x, position.y, position.z));

    btDefaultMotionState* pMotionState = new btDefaultMotionState(transform);
    btRigidBody::btRigidBodyConstructionInfo cInfo(mass, pMotionState, pShape, localInertia);
    mBody = std::make_unique<btRigidBody>(cInfo);
    if (isGhost) {
        mBody->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
    }
    mWorld.addRigidBody(mBody.get());
}

void KitEngine::Physics::Physics::Initialize()
{
    // Set up the collision configuration and dispatcher
    mCollisionConfig  = std::make_unique<btDefaultCollisionConfiguration>();
    mDispathcer       = std::make_unique<btCollisionDispatcher>(mCollisionConfig.get());

    // Build the broadphase
    mBroadphase       = std::make_unique<btDbvtBroadphase>();

    // The actual physics solver
    mSolver           = std::make_unique<btSequentialImpulseConstraintSolver>();

    // The world
    mDynamicsWorld    = std::make_unique<btDiscreteDynamicsWorld>(
                                    mDispathcer.get(), mBroadphase.get(),
                                    mSolver.get(), mCollisionConfig.get());

    mDynamicsWorld->setGravity(btVector3(0.f, -10.0f, 0.f));
    mDebugRenderer = std::make_unique<GLDebugDrawer>();

    mDynamicsWorld->setDebugDrawer(mDebugRenderer.get());
    //mDynamicsWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawAabb);
}

void KitEngine::Physics::Physics::Update(float dt)
{
    mDynamicsWorld->stepSimulation(dt, 10);
}

std::unique_ptr<KitEngine::Physics::BoxCollider> KitEngine::Physics::Physics::CreateBoxCollider(const glm::vec3 &position, 
    const glm::vec3 &size, PhysicObject::Type type, bool isGhost)
{
   return std::make_unique<BoxCollider>(position, size, *mDynamicsWorld, type, isGhost);
}

void KitEngine::Physics::Physics::DebugRender()
{
    mDynamicsWorld->debugDrawWorld();
}

KitEngine::Physics::BoxCollider::BoxCollider(const glm::vec3 &position, const glm::vec3 &size, btDiscreteDynamicsWorld &world, Type type, bool isGhost)
    : PhysicObject(position, world, type)
{
    mShape = std::make_unique<btBoxShape>(btVector3(size.x / 2.0f, size.y / 2.0f, size.z / 2.0f));
    CreateRigidBody(position, mShape.get(), isGhost);
}

KitEngine::Physics::BoxCollider::~BoxCollider()
{
}

KitEngine::Physics::CapsuleCollider::CapsuleCollider(const glm::vec3 &position, float radius, float height, btDiscreteDynamicsWorld &world, Type type, bool isGhost)
    : PhysicObject(position, world, type)
{
    mShape = std::make_unique<btCapsuleShape>(radius, height);
    CreateRigidBody(position, mShape.get(), isGhost);
}
