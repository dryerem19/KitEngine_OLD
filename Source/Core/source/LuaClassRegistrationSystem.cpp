#include "pch.h"
#include "LuaClassRegistrationSystem.h"

#include "Entity.h"
#include "Components.h"

#define REGISTER_COMPONENT_TO_ENTITY(ComponentType) \
    .addFunction("AddComponent" #ComponentType, &Entity::AddComponent<ComponentType>) \
    .addFunction("ReplaceComponent" #ComponentType, &Entity::ReplaceComponent<ComponentType>) \
    .addFunction("GetComponent" #ComponentType, &Entity::GetComponent<ComponentType>) \
    .addFunction("HasComponent" #ComponentType, &Entity::HasComponent<ComponentType>) \
    .addFunction("RemoveComponent" #ComponentType, &Entity::RemoveComponent<ComponentType>)

void LuaClassRegistrationSystem::RegisterAllComponents(lua_State *L)
{
    
}
