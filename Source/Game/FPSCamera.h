#pragma once
#include "BaseCamera.h"
#include "Input.h"

class FPSCamera : public Core::BaseCamera
{
private:
    GLfloat yaw   = -90.0f;
    GLfloat pitch =   0.0f;
    GLfloat lastX =  800  / 2.0;
    GLfloat lastY =  600 / 2.0;
public:
    void HandleInput()
    {
        SetLookAt(cameraPos,cameraPos + cameraFront, cameraUp);

        GLfloat cameraSpeed = 0.30f;
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

        Core::Input::SetInputMode(Core::CursorMode::Cursor, Core::CursorState::CursorDisabled);
        
        GLfloat xoffset = Core::Input::mousePosition.x - lastX;
        GLfloat yoffset = lastY - Core::Input::mousePosition.y;

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
};