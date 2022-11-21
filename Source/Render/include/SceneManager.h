#pragma once
#include "KitScene.h"

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
    public:
        static SceneManager& Instance();
        KitScene* CreateScene(const std::string& name);
        KitScene* GetCurrentScene() const;
    };
}