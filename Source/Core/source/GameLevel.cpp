#include "pch.h"
#include "Entity.h"
#include "GameLevel.h"

namespace Render
{
    GameLevel::GameLevel()
    {
        mCollisionConfig = std::make_unique<btDefaultCollisionConfiguration>();
        mDispathcer = std::make_unique<btCollisionDispatcher>(mCollisionConfig.get());
        mBroadphase = std::make_unique<btDbvtBroadphase>();
        mSolver = std::make_unique<btSequentialImpulseConstraintSolver>();
        mDynamicsWorld = std::make_unique<btDiscreteDynamicsWorld>(mDispathcer.get(), mBroadphase.get(), mSolver.get(), mCollisionConfig.get());
        mDynamicsWorld->setGravity(btVector3(0.f, -9.81f, 0.f));
    }

    void GameLevel::Serialize(const std::string& filepath)
    {
        
    }

    void GameLevel::Deserialize(const std::string& filepath)
    {

    }

    Entity* GameLevel::Create(const std::string& name)
    {
        // Entity* pObj { nullptr };

        // if (mRegistryNames.find(name) != mRegistryNames.end())
        // {
        //     mRegistryNames[name]++;
        //     std::string new_name = name + "_" + std::to_string(mRegistryNames[name]);
        //     mRegistryNames.insert({new_name, mRegistryNames[name]}); 

        //     mObjects.insert({new_name, std::make_unique<Entity>()});
        //     pObj = mObjects[new_name].get();
        //     pObj->SetName(new_name);
        // }
        // else
        // {
        //     mObjects.insert({name, std::make_unique<Entity>()});
        //     mRegistryNames.insert({name, 0});
        //     pObj = mObjects[name].get();
        //     pObj->SetName(name);
        // }

        // return pObj;
    }

    GameLevel& GameLevel::Get()
    {
        static GameLevel instance;
        return instance;
    }
}