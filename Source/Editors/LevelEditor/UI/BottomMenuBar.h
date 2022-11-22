#pragma once
#include "Core/KitUI.h"
#include "Core/EditorCamera.h"

namespace LevelEditor
{
    class BottomMenuBar final : public KitUI
    {
    public:
        BottomMenuBar() = default;
        void Draw() override final;
    };
}