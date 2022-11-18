//
// Created by piokxix on 04.11.22.
//

#ifndef LEVELEDITOR_BASECAMERA_H
#define LEVELEDITOR_BASECAMERA_H
#include "core.h"

namespace Core
{
    class BaseCamera
    {
    public:
        BaseCamera() = default;
        ~BaseCamera() = default;

        void SetPerspective(float fovy, float aspect, float zNear, float zFar);
        void SetLookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
        float* GetView();
        float * GetPerspective();
    private:
        glm::mat4 mTransform = glm::mat4(1.0f);
        glm::mat4 mView = glm::mat4(1.0f);
        glm::mat4 mProjection = glm::mat4(1.0f);
    };
}




#endif //LEVELEDITOR_BASECAMERA_H
