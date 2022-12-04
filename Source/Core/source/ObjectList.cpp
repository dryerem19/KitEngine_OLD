#include "pch.h"
#include "GameObject.h"
#include "ObjectList.h"

GameObject* ObjectList::Create(const std::string& name)
{
    mObjects.insert({name, std::make_unique<GameObject>()});
    return mObjects.at(name).get();
}