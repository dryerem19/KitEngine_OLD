/**
 * @file Physics.h
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief Physics world implementation
 * @version 0.1
 * @date 2023-01-26
 * 
 * @copyright Copyright Denis Eremenko (c) 2023
 * 
 */
#pragma once
#include "Physics/GLDebugDrawer.h"

namespace KitEngine
{
    namespace Physics
    {
        class PhysicObject
        {
        public:
            enum class Type
            {
                STATIC, 
                DYNAMIC,
                KINEMATIC
            };
            glm::vec3 GetPosition() const;
            void SetPosition(const glm::vec3& position);
            void SetLinearVelocity(const glm::vec3& velocity);
            glm::vec3 GetLinearVelocity() const;
            void SetAngularVelocity(const glm::vec3& velocity);
            glm::vec3 GetAngularVelocity() const;
            void SetAngularFactor(const glm::vec3& factor);
            glm::vec3 GetAngularFactor() const;
            void SetDamping(float linear, float angular);
            inline float GetLinearDamping() const {return mBody->getLinearDamping(); }
            void SetImpulse(const glm::vec3& force, const glm::vec3& position);
            void Activate();
            void SetTransform(const glm::mat4& transform);
            glm::mat4 GetTransform();
        protected:
            PhysicObject(const glm::vec3& position, btDiscreteDynamicsWorld& world, Type type);
            ~PhysicObject();
            void CreateRigidBody(const glm::vec3& position, btCollisionShape* pShape, bool isGhost);

            btDiscreteDynamicsWorld& mWorld;
            std::unique_ptr<btRigidBody> mBody;
            std::unique_ptr<btCollisionShape> mShape;
            Type mType;
        };

        class BoxCollider : public PhysicObject
        {
        public:
            BoxCollider(const glm::vec3& position, const glm::vec3& size, 
                btDiscreteDynamicsWorld& world, Type type, bool isGhost);
            ~BoxCollider();
        };

        class CapsuleCollider : public PhysicObject
        {
        public:
            CapsuleCollider(const glm::vec3& position, float radius, float height,
                btDiscreteDynamicsWorld& world, Type type, bool isGhost);
            ~CapsuleCollider() = default;
        };

        class Physics
        {
        private:
            std::unique_ptr<btBroadphaseInterface> mBroadphase;
            std::unique_ptr<btCollisionDispatcher> mDispathcer;
            std::unique_ptr<btConstraintSolver> mSolver;
            std::unique_ptr<btCollisionConfiguration> mCollisionConfig;
            std::unique_ptr<btDiscreteDynamicsWorld> mDynamicsWorld;
            std::unique_ptr<GLDebugDrawer> mDebugRenderer;
        public:
            Physics() = default;
            void Initialize();
            void Update(float dt);
            std::unique_ptr<BoxCollider> CreateBoxCollider(const glm::vec3& position, const glm::vec3& size, 
                PhysicObject::Type type = PhysicObject::Type::STATIC, bool isGhost = false);
            void DebugRender();
        };

        class DebugRenderer : public btIDebugDraw
        {

        };
    }
}