#include "EditorCamera.h"

namespace LevelEditor
{
    EditorCamera::EditorCamera()
        : BaseCamera()
    {

    }

    void EditorCamera::OnUpdate()
    {
        if (Core::Input::GetMouseButton(Core::MouseButton::MouseButtonRight)) 
        {
            Core::Input::SetInputMode(Core::CursorMode::Cursor, Core::CursorState::CursorDisabled);

            const glm::vec2 mousePosition = Core::Input::mousePosition;
            glm::vec2 delta = (mousePosition - mOldMousePosition) * 0.003f;
            mOldMousePosition = mousePosition;
            CameraMove();
            CameraRotate(delta);
        }

        if(Core::Input::GetMouseUp(Core::MouseButton::MouseButtonRight)) {
            Core::Input::SetInputMode(Core::CursorMode::Cursor, Core::CursorState::CursorNormal);
        }         

        BaseCamera::OnUpdate();
    }

    void EditorCamera::CameraMove()
    {
        if (Core::Input::GetKey(Core::KeyCode::W))
        {
            mPosition += cameraSpeed * GetForward();
        }
        
        if (Core::Input::GetKey(Core::KeyCode::S))
        {
            mPosition -= cameraSpeed * GetForward();
        }
        
        if (Core::Input::GetKey(Core::KeyCode::A))
        {
            mPosition -= GetRight() * cameraSpeed;
        }
        
        if (Core::Input::GetKey(Core::KeyCode::D))
        {
            mPosition += GetRight() * cameraSpeed;
        } 
    }

    void EditorCamera::CameraRotate(const glm::vec2& delta)
    {
        float yawSign = GetUp().y < 0 ? -1.0f : 1.0f;
		mYaw += yawSign * delta.x * mRotationSpeed;
		mPitch += delta.y * mRotationSpeed;        
    }
}