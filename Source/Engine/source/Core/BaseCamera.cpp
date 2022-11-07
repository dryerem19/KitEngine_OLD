//
// Created by piokxix on 04.11.22.
//
#include <Core/BaseCamera.h>


void KitEngine::Core::BaseCamera::SetPerspective(float fovy, float aspect, float zNear, float zFar) {
    mProjection = glm::perspective(fovy, aspect, zNear, zFar);
}

void KitEngine::Core::BaseCamera::SetLookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up) {
    mView = glm::lookAt(eye,center,up);
}

float* KitEngine::Core::BaseCamera::GetView() {
    return glm::value_ptr(mView);
}

float* KitEngine::Core::BaseCamera::GetPerspective() {
    return glm::value_ptr(mProjection);
}
