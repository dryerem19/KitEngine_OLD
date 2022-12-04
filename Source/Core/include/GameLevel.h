#pragma once

#include <BulletDynamics/btBulletDynamicsCommon.h>

#include "BaseEntity.h"


namespace Render
{
    class GameLevel : public Core::BaseEntity
    {
    private:
        GameLevel();
        GameLevel(const GameLevel&) = delete;
        GameLevel& operator=(GameLevel&) = delete;
        ~GameLevel() = default;
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
        static GameLevel& Get();

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