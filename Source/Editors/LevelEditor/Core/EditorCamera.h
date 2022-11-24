#pragma once

#include <BaseCamera.h>
#include <Input.h>

namespace LevelEditor
{
    class EditorCamera : public Core::BaseCamera
    {
    private:
        EditorCamera() = default;
        ~EditorCamera() = default;
        EditorCamera(const EditorCamera&) = delete;
        EditorCamera& operator=(EditorCamera&) = delete;

        GLfloat yaw   = -90.0f;
        GLfloat pitch =   0.0f;
        GLfloat lastX =  800  / 2.0;
        GLfloat lastY =  600 / 2.0;

        bool isCheckMouse = true;

    public:
        inline static float cameraSpeed = 0.30f;

        static EditorCamera& Instance()
        {
            static EditorCamera instance;
            return instance;
        }

        void Update();
    };
}
