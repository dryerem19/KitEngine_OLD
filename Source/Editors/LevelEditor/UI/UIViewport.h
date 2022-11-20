#pragma once

#include "KitUI.h"
#include "UITopBarTools.h"
#include "UISceneTree.h"
#include <Core/EditorCamera.h>

using namespace LevelEditor;

namespace UI
{
    class UIViewport : public KitUI
    {
    public:
        UIViewport() = default;
        void Draw() override;
        void DrawGizmo();

        UITopBarTools* uiTopBarTools;
        UISceneTree*   uiSceneTree;
        Render::FrameBuffer* frameBuffer;
    };
}