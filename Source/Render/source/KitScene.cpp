#include "RenderPch.h"
#include "KitScene.h"
#include "KitObject.h"
#include "KitTransform.h"

Render::KitObject Render::KitScene::CreateObject()
{
    entt::entity entity = mRegistry.create();
    KitObject obj(entity, this);
    obj.AddComponent<KitTransform>();
    return obj;
}
