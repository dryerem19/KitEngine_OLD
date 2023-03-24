#include "pch.h"
#include "Entity.h"

Entity::Entity(entt::entity entityId, Scene *pScene)
    : mEntityId(entityId), m_pScene(pScene)
{
}
