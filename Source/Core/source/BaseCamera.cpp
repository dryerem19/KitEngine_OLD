//
// Created by piokxix on 04.11.22.
//
#include "BaseCamera.h"


void Core::BaseCamera::SetPerspective(float fovy, float aspect, float zNear, float zFar) {
    mProjection = glm::perspective(fovy, aspect, zNear, zFar);
}

void Core::BaseCamera::SetLookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up) {
    mView = glm::lookAt(eye,center,up);
}

float* Core::BaseCamera::GetView() {
    return glm::value_ptr(mView);
}

float* Core::BaseCamera::GetPerspective() {
    return glm::value_ptr(mProjection);
}
