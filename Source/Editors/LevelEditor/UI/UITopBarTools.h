#pragma once

#include "KitUI.h"

namespace UI
{
    class UITopBarTools : public KitUI
    {
    public:
        UITopBarTools() = default;
        void Draw() override;

        ImGuizmo::OPERATION mode = ImGuizmo::OPERATION::TRANSLATE;
    };
}
