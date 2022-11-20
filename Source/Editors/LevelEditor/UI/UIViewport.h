#pragma once

#include "Core/KitUI.h"
#include "UITopBarTools.h"
#include "UISceneTree.h"
#include <Core/EditorCamera.h>
#include "Core/Events/SelectGizmoEvent.h"


namespace LevelEditor
{
    class UIViewport : public KitUI
    {
    private:
        GizmoOperation mOperation;
    public:
        UIViewport() = default;
        UIViewport(IController* controller) : KitUI(controller) { }
        void Draw() override;
        void DrawGizmo();
        void SetGizmoOperation(GizmoOperation operation) { mOperation = operation; }

        UITopBarTools* uiTopBarTools;
        UISceneTree*   uiSceneTree;
        Render::FrameBuffer* frameBuffer;
    };
}