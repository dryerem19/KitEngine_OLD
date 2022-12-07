#pragma once
#include "Core/KitUI.h"
#include "GameLevel.h"

namespace LevelEditor
{
    class Inspector final : public KitUI
    {
    public:
        Inspector() = default;
        void Draw() override final;
    private:
        void DrawMaterial();
        void DrawTransformComponent();
    };
}