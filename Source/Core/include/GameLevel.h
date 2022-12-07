#pragma once

#include <BulletDynamics/btBulletDynamicsCommon.h>


class GameObject;

namespace Render
{
    class GameLevel
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
        std::unordered_map<std::string, std::unique_ptr<GameObject>> mObjects;
        std::unordered_map<std::string, uint32_t> mRegistryNames;
        GameObject* m_pSelectedEntity { nullptr };     
    public:

        static GameLevel& Get();
        
        GameObject* Create(const std::string& name);

        void Update();

        void Draw(const float* view_matrix, float* proj_matrix);

        void Spawn(GameObject* pEntity);

        inline void AddRigidBody(btRigidBody* pRigidBody) { mBodies.push_back(pRigidBody); }

        inline void SetSelectedEntity(GameObject* pSelectedEntity)
        {
            m_pSelectedEntity = pSelectedEntity;
        }

        inline GameObject* GetSelectedEntity() const
        {
            return m_pSelectedEntity;
        }

        /**
         * @brief Поиск объекта по его имени
         * 
         * @param name имя объекта
         * @return GameObject* 
         */
        inline GameObject* FindObjectByName(const std::string& name)
        {
            return mObjects.find(name) != mObjects.end() ? mObjects[name].get() : nullptr;
        }        
        
        inline std::unordered_map<std::string, std::unique_ptr<GameObject>>::iterator begin() noexcept
        {
            return mObjects.begin();
        }

        inline std::unordered_map<std::string, std::unique_ptr<GameObject>>::iterator end() noexcept
        {
            return mObjects.end();
        }  

        inline std::unordered_map<std::string, std::unique_ptr<GameObject>>::const_iterator cbegin() const noexcept
        {
            return mObjects.cbegin();
        }

        inline std::unordered_map<std::string, std::unique_ptr<GameObject>>::const_iterator cend() const noexcept
        {
            return mObjects.cend();
        }                
    };
}