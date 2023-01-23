#pragma once
#include "BaseCamera.h"
#include "Input.h"

class FPSCamera : public BaseCamera
{
private:
    glm::vec2 mOldMousePosition;
    const float mRotationSpeed = 0.75;
    const float mMouseMoveSpeed = 2;
public:

    void OnUpdate() override final
    {
        Core::Input::SetInputMode(Core::CursorMode::Cursor, Core::CursorState::CursorDisabled);

        const glm::vec2 mousePosition = Core::Input::mousePosition;
        glm::vec2 delta = (mousePosition - mOldMousePosition) * 0.003f;
        mOldMousePosition = mousePosition;

        Move();
        Rotate(delta);  

        BaseCamera::OnUpdate();        
    }

    void Move()
    {
        if (Core::Input::GetKey(Core::KeyCode::W))
        {
            mPosition += mMouseMoveSpeed * GetForward();
        }
        
        if (Core::Input::GetKey(Core::KeyCode::S))
        {
            mPosition -= mMouseMoveSpeed * GetForward();
        }
        
        if (Core::Input::GetKey(Core::KeyCode::A))
        {
            mPosition -= GetRight() * mMouseMoveSpeed;
        }
        
        if (Core::Input::GetKey(Core::KeyCode::D))
        {
            mPosition += GetRight() * mMouseMoveSpeed;
        }
    }

    void Rotate(const glm::vec2& delta)
    {
        float yawSign = GetUp().y < 0 ? -1.0f : 1.0f;
		mYaw += yawSign * delta.x * mRotationSpeed;
		mPitch += delta.y * mRotationSpeed; 
    }
};