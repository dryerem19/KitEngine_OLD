#pragma once

#include "Core/KitUI.h"
#include "Core/IController.h"
#include "Core/Events/SelectGizmoEvent.h"
#include "Core/EditorCamera.h"

namespace LevelEditor
{
    class UITopBarTools : public KitUI
    {
    public:
        UITopBarTools() = default;
        UITopBarTools(IController* controller) : KitUI(controller) { }
        void Draw() override;

        ImGuizmo::OPERATION mode = ImGuizmo::OPERATION::TRANSLATE;
    };
}
