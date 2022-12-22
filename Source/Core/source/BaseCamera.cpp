//
// Created by piokxix on 04.11.22.
//
#include "pch.h"
#include "BaseCamera.h"


void Core::BaseCamera::SetPerspective(float fovy, float aspect, float zNear, float zFar) 
{
    mFovy = fovy;
    mAspect = aspect;
    mZNear = zNear;
    mZFar = zFar;
    mProjection = glm::perspective(fovy, aspect, zNear, zFar);
}

void Core::BaseCamera::SetLookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up) {
    mView = glm::lookAt(eye,center,up);
}

const float* Core::BaseCamera::GetView() const {
    return glm::value_ptr(mView);
}

const float* Core::BaseCamera::GetPerspective() const {
    return glm::value_ptr(mProjection);
}

void Core::BaseCamera::UpdateAspect(const float &aspect)
{
    mAspect = aspect;
    SetPerspective(mFovy, mAspect, mZNear, mZFar);
}
