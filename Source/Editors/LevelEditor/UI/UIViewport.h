#pragma once

#include "Core/KitUI.h"
#include <Core/EditorCamera.h>
#include "Core/Events/SelectGizmoEvent.h"
#include "Entity.h"
#include "GameLevel.h"

#include "KitCore.h"

namespace LevelEditor
{
    class UIViewport : public KitUI
    {
    private:
        GizmoOperation mOperation;

        int mWidth;
        int mHeight;
        float mCameraMouseDistance = 10;

        bool mIsFirstDelivery = true;
        Entity* pDeliveryEntity = nullptr;
        float mMoveSpeed = 0.2f;

        glm::vec2 mOldMouseOffset;
        glm::vec3 mMousePickRay;        

    public:
        UIViewport() = default;
        UIViewport(IController* controller) : KitUI(controller) { }
        void Draw() override;
        void DrawGizmo();
        void SetGizmoOperation(GizmoOperation operation) { mOperation = operation; }
        
        Render::FrameBuffer* frameBuffer;
    };
}