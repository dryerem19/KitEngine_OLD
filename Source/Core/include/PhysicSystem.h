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
#include "Physics/GLDebugDrawer.h"

btVector3 TobtVector3(const glm::vec3& vec);

class PhysicSystem
{
private:
    PhysicSystem();
    PhysicSystem(const PhysicSystem&) = delete;
    PhysicSystem& operator=(const PhysicSystem&) = delete;
    ~PhysicSystem();
private:
    btBroadphaseInterface* m_pBroadphase;
    btCollisionDispatcher* m_pDispathcer;
    btConstraintSolver* m_pSolver;
    btCollisionConfiguration* m_pCollisionConfig;
    btDiscreteDynamicsWorld* m_pDynamicsWorld;
    GLDebugDrawer* m_pDebugDrawer;
public:
    static PhysicSystem& Instance();
    btDiscreteDynamicsWorld* GetDynamicsWorld();
    void Update(float deltaTime);
    btBoxShape* CreateBoxShape(const btVector3& halfExtents);
    btRigidBody* CreateRigidBody(const float& mass, const btTransform& transform, btCollisionShape* pShape);
    btRigidBody* GetPickBody(const glm::vec3& origin, const glm::vec3& end);

    /**
     * @brief Нарисовать физический мир в режиме отладки
     * Вызывайте после того, как был нарисован основной мир
     */
    void DebugDrawWorld() const;
    
    GLDebugDrawer* GetDebugDrawer() const;

    /**
     * @brief Изменить режим отладки
     */
    void SetDebugMode(int mode);
};