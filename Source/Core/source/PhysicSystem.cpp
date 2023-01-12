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

btVector3 TobtVector3(const glm::vec3 &vec)
{
    return btVector3(vec.x, vec.y, vec.z);
}

PhysicSystem::PhysicSystem()
    : m_pBroadphase(nullptr),
      m_pDispathcer(nullptr),
      m_pSolver(nullptr),
      m_pCollisionConfig(nullptr),
      m_pDynamicsWorld(nullptr),
      m_pDebugDrawer(nullptr)
{
    // Set up the collision configuration and dispatcher
    m_pCollisionConfig  = new btDefaultCollisionConfiguration();
    m_pDispathcer       = new btCollisionDispatcher(m_pCollisionConfig);

    // Build the broadphase
    m_pBroadphase       = new btDbvtBroadphase();

    // The actual physics solver
    m_pSolver           = new btSequentialImpulseConstraintSolver();

    // The world
    m_pDynamicsWorld    = new btDiscreteDynamicsWorld(m_pDispathcer, m_pBroadphase, m_pSolver, m_pCollisionConfig);
    m_pDynamicsWorld->setGravity(btVector3(0.f, -10.0f, 0.f));

    // Create the debug drawer
    m_pDebugDrawer      = new GLDebugDrawer();

    // Set the initial debug level
    m_pDebugDrawer->setDebugMode(btIDebugDraw::DBG_DrawAabb);

    // Add the debug drawer to the world
    m_pDynamicsWorld->setDebugDrawer(m_pDebugDrawer);
}

PhysicSystem::~PhysicSystem()
{
    if (m_pDynamicsWorld) {
        int i = 0;
        for (i = m_pDynamicsWorld->getNumConstraints() - 1; i >= 0; i--) {
            m_pDynamicsWorld->removeConstraint(m_pDynamicsWorld->getConstraint(i));
        }

        for (i = m_pDynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--) {
            btCollisionObject* pCollisionObject = m_pDynamicsWorld->getCollisionObjectArray()[i];
            btRigidBody* pRigidBody = btRigidBody::upcast(pCollisionObject);
            if (pRigidBody && pRigidBody->getMotionState()) {
                delete pRigidBody->getMotionState();
            }
            m_pDynamicsWorld->removeCollisionObject(pCollisionObject);
            delete pCollisionObject;
        }
    }

    delete m_pDynamicsWorld;
    m_pDynamicsWorld = nullptr;

    delete m_pSolver;
    m_pSolver = nullptr;

    delete m_pBroadphase;
    m_pBroadphase = nullptr;

    delete m_pCollisionConfig;
    m_pCollisionConfig = nullptr;
}

PhysicSystem &PhysicSystem::Instance()
{
    static PhysicSystem instance;
    return instance;
}

btDiscreteDynamicsWorld *PhysicSystem::GetDynamicsWorld()
{
    return m_pDynamicsWorld;
}

void PhysicSystem::Update(float deltaTime)
{
    m_pDynamicsWorld->stepSimulation(deltaTime, 5);
}

btBoxShape *PhysicSystem::CreateBoxShape(const btVector3 &halfExtents)
{
    btBoxShape* pBox = new btBoxShape(halfExtents);
    return pBox;
}

btRigidBody* PhysicSystem::CreateRigidBody(const float& mass, const btTransform& transform, 
                         btCollisionShape* pShape)
{
    btAssert((!pShape || pShape->getShapeType() != INVALID_SHAPE_PROXYTYPE));

    bool isDynamic = (mass != 0.0f);
    btVector3 localInertia(0, 0, 0);
    if (isDynamic) {
        pShape->calculateLocalInertia(mass, localInertia);
    }

    btDefaultMotionState* pMotionState = new btDefaultMotionState(transform);
    btRigidBody::btRigidBodyConstructionInfo cInfo(mass, pMotionState, pShape, localInertia);
    btRigidBody* pRigidBody = new btRigidBody(cInfo);
    m_pDynamicsWorld->addRigidBody(pRigidBody);
    return pRigidBody;
}

btRigidBody* PhysicSystem::GetPickBody(const glm::vec3 &origin, const glm::vec3 &end)
{
    if (!m_pDynamicsWorld) {
        return nullptr;
    }

    btCollisionWorld::ClosestRayResultCallback rayCallback(btVector3(origin.x, origin.y, origin.z), 
        btVector3(end.x, end.y, end.z)
    );
    
    m_pDynamicsWorld->rayTest(
        btVector3(origin.x, origin.y, origin.z),
        btVector3(end.x, end.y, end.z),
        rayCallback);

    if (rayCallback.hasHit()) {
        btVector3 pickPos = rayCallback.m_hitPointWorld;
        btRigidBody* pRigidBody = (btRigidBody*)btRigidBody::upcast(rayCallback.m_collisionObject);
        return pRigidBody;
    }

    return nullptr;
}

void PhysicSystem::DebugDrawWorld() const
{
    if (!m_pDebugDrawer) {
        return;
    }

    m_pDynamicsWorld->debugDrawWorld();
}

GLDebugDrawer* PhysicSystem::GetDebugDrawer() const
{
    return m_pDebugDrawer;
}

void PhysicSystem::SetDebugMode(int mode)
{
    if (!m_pDebugDrawer) {
        return;
    }

    m_pDebugDrawer->setDebugMode(mode);
}
