/**
 * @file Scene.h
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief Scene interface
 * @version 0.1
 * @date 2023-01-29
 * 
 * @copyright Copyright Denis Eremenko (c) 2023
 * 
 */
#pragma once
#include "Components.h"
#include "RenderSystem.h"

#include "PhysicSystem.h"
#include "PhysicDebugSystem.h"

#include "Model.h"

#include "ISystem.h"

class Entity;

class Scene
{
private:
    entt::registry mRegistry;
    std::vector<std::unique_ptr<ISystem>> mSystems;
public:
    Scene();
    Entity CreateEntity(const std::string& name = std::string());

    template<typename SystemType, typename... Args>
    void RegistrySystem(Args&&... args)
    {
        if (!HasSystem<SystemType>())
        {
            mSystems.emplace_back(std::make_unique<SystemType>(std::forward<Args>(args)...));
        }
    }

    template<typename SystemType>
    bool HasSystem()
    {
        for (auto& system : mSystems)
        {
            if (typeid(system.get()) == typeid(SystemType))
            {
                return true;
            }
        }

        return false;
    }

    void OnViewportResize(float width, float height);

    inline void StartSimulatePhysic() { mPhysicSystem.OnStart(); };

    virtual void OnStart();
    virtual void OnUpdate();
    virtual void OnFinish();
private:
    std::vector<entt::entity> mEntities;
    RenderSystem mRenderSystem;
    PhysicSystem mPhysicSystem;
    PhysicDebugSystem mPhysicDebugSystem;
    friend class Entity;
};