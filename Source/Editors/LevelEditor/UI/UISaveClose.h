#pragma once

#include "Core/KitUI.h"

namespace LevelEditor
{
    class UISaveClose : public KitUI
    {
    public:
        UISaveClose() = default;
        void Draw() override;

        bool mIsCheckClose = false;
    };
} // namespace LevelEditor
