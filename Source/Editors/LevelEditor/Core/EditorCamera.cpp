#include "EditorCamera.h"

namespace LevelEditor
{
    EditorCamera::EditorCamera()
        : BaseCamera()
    {

    }

    void EditorCamera::OnUpdate()
    {
        if (Input::GetMouseButton(MouseButton::MouseButtonRight)) 
        {
            Input::SetInputMode(CursorMode::Cursor, CursorState::CursorDisabled);

            const glm::vec2 mousePosition = Input::mousePosition;
            glm::vec2 delta = (mousePosition - mOldMousePosition) * 0.003f;
            mOldMousePosition = mousePosition;
            CameraMove();
            CameraRotate(delta);
        }

        if(Input::GetMouseUp(MouseButton::MouseButtonRight)) {
            Input::SetInputMode(CursorMode::Cursor, CursorState::CursorNormal);
        }         

        BaseCamera::OnUpdate();
    }

    void EditorCamera::CameraMove()
    {
        if (Input::GetKey(KeyCode::W))
        {
            mPosition += cameraSpeed * GetForward();
        }
        
        if (Input::GetKey(KeyCode::S))
        {
            mPosition -= cameraSpeed * GetForward();
        }
        
        if (Input::GetKey(KeyCode::A))
        {
            mPosition -= GetRight() * cameraSpeed;
        }
        
        if (Input::GetKey(KeyCode::D))
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