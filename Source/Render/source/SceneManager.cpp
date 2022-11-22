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
        return mCurrentScene;
    }

    KitScene* SceneManager::GetCurrentScene() const
    {
        return mCurrentScene;
    }

    void SceneManager::SetSelectedObject(const KitObject& obj)
    {
        mSelectedObject = obj;
    }

    KitObject SceneManager::GetSelectedObject() const
    {
        return mSelectedObject;
    }
}