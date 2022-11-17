#include "RenderPch.h"
#include "KitScene.h"
#include "KitObject.h"

Render::KitObject Render::KitScene::CreateObject()
{
    entt::entity entity = mRegistry.create(); 
    return KitObject(entity, this);
}
