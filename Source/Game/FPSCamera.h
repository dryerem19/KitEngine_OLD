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
        //Input::SetInputMode(CursorMode::Cursor, CursorState::CursorDisabled);

        const glm::vec2 mousePosition = Input::mousePosition;
        glm::vec2 delta = (mousePosition - mOldMousePosition) * 0.003f;
        mOldMousePosition = mousePosition;

        Move();
        Rotate(delta);  

        BaseCamera::OnUpdate();        
    }

    void Move()
    {
        if (Input::GetKey(KeyCode::W))
        {
            mPosition += mMouseMoveSpeed * GetForward();
            std::cout << "W: \n";
        }
        
        if (Input::GetKey(KeyCode::S))
        {
            mPosition -= mMouseMoveSpeed * GetForward();
        }
        
        if (Input::GetKey(KeyCode::A))
        {
            mPosition -= GetRight() * mMouseMoveSpeed;
        }
        
        if (Input::GetKey(KeyCode::D))
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