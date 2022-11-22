#pragma once
#include "Core/KitUI.h"
#include "SceneManager.h"

namespace LevelEditor
{
    class Inspector final : public KitUI
    {
    public:
        Inspector() = default;
        void Draw() override final;
    private:
        void DrawTransformComponent(Render::KitTransform& transform);
    };
}