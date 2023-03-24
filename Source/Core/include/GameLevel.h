#pragma once
#include "Entity.h"

#include "Interfaces/IDeserialization.h"
#include "Interfaces/ISerialization.h"
#include "Skybox.h"
#include "KitLight.h"

#include "SoundBuffer.h"

#include <BulletDynamics/btBulletDynamicsCommon.h>


#include "Physics.h"


class GameLevel : public ISerialization, public IDeserialization
{
private:
    GameLevel();
    GameLevel(const GameLevel&) = delete;
    GameLevel& operator=(GameLevel&) = delete;
    ~GameLevel() = default;
private:
    std::unordered_map<std::string, std::unique_ptr<Entity>> mObjects;
    std::unordered_map<std::string, uint32_t> mRegistryNames;
    KitObject* mSelectedObject = nullptr; 
    SkyBox mSkyBox;


    KitEngine::Physics::Physics mPhysics;



    entt::registry mRegistry;



    std::unique_ptr<btBroadphaseInterface> mBroadphase;
    std::unique_ptr<btCollisionDispatcher> mDispathcer;
    std::unique_ptr<btConstraintSolver> mSolver;
    std::unique_ptr<btCollisionConfiguration> mCollisionConfig;
    std::unique_ptr<btDiscreteDynamicsWorld> mDynamicsWorld;
    std::unique_ptr<GLDebugDrawer> mPhysicsDebugRenderer;




public:
    std::vector<std::unique_ptr<KitLight>> _lights;
    //std::vector<std::shared_ptr<Entity>> mEntities;
    std::vector<std::unique_ptr<Entity>> _objects; 

    std::vector<std::unique_ptr<SoundBuffer>> _soundsources; 

    static GameLevel& Get();

    void Initialize();

    void Clear();

    void Serialize(const std::string& filepath) override final;
    void Deserialize(const std::string& filepath) override final;


    void Update();

    void InitSkybox(const std::string& filepath);

    SkyBox& GetSkybox() { return mSkyBox; }

    KitLight* CreateLigth();

    void DeleteLight();

    Entity* CreateEntity();

    SoundBuffer* CreateSound();

    inline void SetSelectedObject(KitObject* object)
    {
        mSelectedObject = object;
    }

    inline KitObject* GetSelectedObject() const
    {
        return mSelectedObject;
    }
};