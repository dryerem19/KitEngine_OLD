#include "RenderPch.h"
#include "SceneManager.h"

namespace Render
{
    SceneManager& SceneManager::Instance()
    {
        static SceneManager instance;
        return instance;
    }

    KitScene* SceneManager::CreateScene(const std::string& name)
    {
        mCurrentScene = new KitScene();
    }

    KitScene* SceneManager::GetCurrentScene() const
    {
        return mCurrentScene;
    }
}