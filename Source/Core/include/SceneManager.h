#pragma once
#include "KitScene.h"
#include "KitObject.h"

namespace Render
{
    class SceneManager
    {
    private:
        SceneManager() = default;
        SceneManager(const SceneManager&) = delete;
        SceneManager& operator=(SceneManager&) = delete;
        ~SceneManager() = default;

        KitScene* mCurrentScene;
        KitObject mSelectedObject;
    public:
        static SceneManager& Instance();
        KitScene* CreateScene(const std::string& name);
        KitScene* GetCurrentScene() const;
        void SetSelectedObject(const KitObject& obj);
        KitObject GetSelectedObject() const;
    };
}