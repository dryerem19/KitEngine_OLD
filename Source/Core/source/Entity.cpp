#include "pch.h"
#include "GameLevel.h"
#include "Entity.h"


void Entity::Spawn()
{
    Render::GameLevel::Get().mEntities.push_back(shared_from_this());
}


void Entity::SetModel(std::shared_ptr<Model> model)
{
    if (model)
    {
        mModel = model;
    }
}


Entity::Entity(const std::string& name /* = Root */)
{
    mId++;
}
