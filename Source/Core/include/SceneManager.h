#pragma once

#include <BulletDynamics/btBulletDynamicsCommon.h>

#include "BaseEntity.h"
namespace Render
{
    class World : public Core::BaseEntity
    {
    private:
        World();
        World(const World&) = delete;
        World& operator=(World&) = delete;
        ~World() = default;
    private:
        std::unique_ptr<btDynamicsWorld> mDynamicsWorld;
        std::unique_ptr<btDispatcher> mDispathcer;
        std::unique_ptr<btCollisionConfiguration> mCollisionConfig;
        std::unique_ptr<btBroadphaseInterface> mBroadphase;
        std::unique_ptr<btConstraintSolver> mSolver;
        std::vector<btRigidBody*> mBodies;
    private:
        Core::BaseEntity* m_pSelectedEntity { nullptr };
    public:
        static World& Get();

        void Spawn(Core::BaseEntity* pEntity);

        inline void AddRigidBody(btRigidBody* pRigidBody) { mBodies.push_back(pRigidBody); }

        inline void SetSelectedEntity(Core::BaseEntity* pSelectedEntity)
        {
            m_pSelectedEntity = pSelectedEntity;
        }

        inline Core::BaseEntity* GetSelectedEntity() const
        {
            return m_pSelectedEntity;
        }
    };
}