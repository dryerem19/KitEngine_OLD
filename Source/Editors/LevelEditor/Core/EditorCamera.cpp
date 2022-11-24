#include "EditorCamera.h"

namespace LevelEditor
{
    void EditorCamera::Update()
    {
        SetLookAt(cameraPos,cameraPos + cameraFront, cameraUp);

        //GLfloat cameraSpeed = 0.30f;
        if (Core::Input::GetKey(Core::KeyCode::W))
        {
            cameraPos += cameraSpeed * cameraFront;
        }
        if (Core::Input::GetKey(Core::KeyCode::S))
        {
            cameraPos -= cameraSpeed * cameraFront;
        }
        if (Core::Input::GetKey(Core::KeyCode::A))
        {
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        }
        if (Core::Input::GetKey(Core::KeyCode::D))
        {
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        }

        if(Core::Input::GetMouseButton(Core::MouseButton::MouseButtonRight))
        {
            Core::Input::SetInputMode(Core::CursorMode::Cursor, Core::CursorState::CursorDisabled);
            
            GLfloat xoffset = Core::Input::mousePosition.x - lastX;
            GLfloat yoffset = lastY - Core::Input::mousePosition.y;

            // Установка курсора на последнее подложение камеры
            if(isCheckMouse)
            {
                Core::Input::SetCursorPos(lastX, lastY);
                isCheckMouse = false;
            }

            lastX = Core::Input::mousePosition.x;
            lastY = Core::Input::mousePosition.y;
            
            GLfloat sensitivity = 0.05;
            xoffset *= sensitivity;
            yoffset *= sensitivity;

            yaw   += xoffset;
            pitch += yoffset;

            if(pitch > 89.0f)
                pitch = 89.0f;
            if(pitch < -89.0f)
                pitch = -89.0f;

            glm::vec3 front;
            front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            front.y = sin(glm::radians(pitch));
            front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
            cameraFront = glm::normalize(front);

        }
        if(Core::Input::GetMouseUp(Core::MouseButton::MouseButtonRight))
        {
            Core::Input::SetInputMode(Core::CursorMode::Cursor, Core::CursorState::CursorNormal);
            isCheckMouse = true;
            // Установка последних координт камеры на позицию мыши
            Core::Input::mousePosition.x = lastX;
            Core::Input::mousePosition.y = lastY;
        }
    }
}