#pragma once

#include <BulletDynamics/btBulletDynamicsCommon.h>


class GameObject;

// GameObject* Create(const std::string& name);

// GameObject* ObjectList::Create(const std::string& name)
// {
//     mObjects.insert({name, std::make_unique<GameObject>()});
//     return mObjects.at(name).get();
// }

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
        std::unordered_map<std::string, GameObject*> mObjects;
        GameObject* m_pSelectedEntity { nullptr };     
    public:

        static GameLevel& Get();
        
        void Add(GameObject* pGameObject);

        void Update();

        void Draw(Render::Shader* pShader, const float* view_matrix, float* proj_matrix);

        void Spawn(GameObject* pEntity);

        inline void AddRigidBody(btRigidBody* pRigidBody) { mBodies.push_back(pRigidBody); }

        inline void SetSelectedEntity(GameObject* pSelectedEntity)
        {
            mObjects.begin();
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
            return mObjects.find(name) != mObjects.end() ? mObjects[name] : nullptr;
        }        
        
        inline std::unordered_map<std::string, GameObject*>::iterator begin() noexcept
        {
            return mObjects.begin();
        }

        inline std::unordered_map<std::string, GameObject*>::iterator end() noexcept
        {
            return mObjects.end();
        }  

        inline std::unordered_map<std::string, GameObject*>::const_iterator cbegin() const noexcept
        {
            return mObjects.cbegin();
        }

        inline std::unordered_map<std::string, GameObject*>::const_iterator cend() const noexcept
        {
            return mObjects.cend();
        }                
    };
}