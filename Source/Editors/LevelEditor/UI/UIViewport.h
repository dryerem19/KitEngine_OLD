#pragma once

#include "Core/KitUI.h"
#include <Core/EditorCamera.h>
#include "Core/Events/SelectGizmoEvent.h"
#include "GameLevel.h"

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
        
        Render::FrameBuffer* frameBuffer;
    };
}