/**
 * @file Entity.h
 * @author Denis Eremenko (mamayma@dgmail.com)
 * @brief Базовая логика игровой сущности
 * @version 0.1
 * @date 2022-11-30
 * 
 * @copyright Copyright Denis Eremenko(c) 2022
 * 
 */
#pragma once
#include "Scene.h"

class Entity
{
private:
    entt::entity mEntityId { entt::null };
    Scene* m_pScene { nullptr };
public:
    Entity() = default;
    Entity(entt::entity entityId, Scene* pScene);
    Entity(const Entity& right) = default;

    template<typename T, typename... Args>
    T& AddComponent(Args&&... args)
    {
        assert(m_pScene != nullptr && "The scene does not exist");
        assert(mEntityId != entt::null && "Null entity");
        assert(!HasComponent<T>() && "Entity already have component");
        return m_pScene->mRegistry.emplace<T>(mEntityId, std::forward<Args>(args)...);
    }

    template<typename T, typename... Args>
    T& ReplaceComponent(Args&&... args)
    {
        assert(m_pScene != nullptr && "The scene does not exist");
        assert(mEntityId != entt::null && "Null entity");
        return m_pScene->mRegistry.emplace_or_replace<T>(mEntityId, std::forward<Args>(args)...);
    }

    template<typename T>
    T& GetComponent()
    {
        assert(m_pScene != nullptr && "The scene does not exist");
        assert(mEntityId != entt::null && "Null entity");
        assert(HasComponent<T>() && "Entity does not have component");
        return m_pScene->mRegistry.get<T>(mEntityId);
    }

    template<typename T>
    bool HasComponent()
    {
        assert(m_pScene != nullptr && "The scene does not exist");
        assert(mEntityId != entt::null && "Null entity");
        return m_pScene->mRegistry.any_of<T>(mEntityId);
    }

    template<typename T>
    void RemoveComponent()
    {
        assert(m_pScene != nullptr && "The scene does not exist");
        assert(mEntityId != entt::null && "Null entity");
        assert(HasComponent<T>() && "Entity does not have component");
        return m_pScene->mRegistry.remove<T>(mEntityId);
    }

    Scene* GetScene() const { return m_pScene; }

    TransformComponent& GetTransform() { return GetComponent<TransformComponent>(); }

    operator bool() const { return mEntityId != entt::null; }
    operator entt::entity() const { return mEntityId; }
    operator unsigned int() const { return (unsigned int)mEntityId; }

    bool operator==(const Entity& right) const 
    {
        return mEntityId == right.mEntityId && m_pScene == right.m_pScene;
    }

    bool operator!=(const Entity& right) const 
    {
        return !(*this == right);
    }
};