#include "RenderPch.h"
#include "KitScene.h"
#include "KitObject.h"

Render::KitObject Render::KitScene::CreateObject()
{
    entt::entity entity = mRegistry.create(); 
    auto obj = KitObject(entity, this);
    auto& tc = obj.AddComponent<KitTransform>();
    return obj;
}
