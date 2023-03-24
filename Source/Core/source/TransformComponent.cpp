/**
 * @file TransformComponent.cpp
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief Transform implementation
 * @version 0.1
 * @date 2023-01-30
 * 
 * @copyright Copyright Denis Eremenko (c) 2023
 * 
 */
#include "pch.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent(const glm::vec3 &position)
    : mPosition(position)
{
}

TransformComponent::TransformComponent(const glm::vec3 &position, const glm::vec3 &rotation)
    : mPosition(position), mRotation(rotation)
{
}

TransformComponent::TransformComponent(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale)
    : mPosition(position), mRotation(rotation), mScale(scale)
{
}


void TransformComponent::SetPosition(const glm::vec3 &position)
{
    glm::vec3 dp = position - mPosition;
    
    mPosition = position;
    mChangedMarker = true;
}

void TransformComponent::SetRotation(const glm::vec3 &rotation)
{
    mRotation = rotation;
    mChangedMarker = true;
}

void TransformComponent::SetScale(const glm::vec3 &scale)
{
    mScale = scale;
    mChangedMarker = true;
}

void TransformComponent::SetPivot(const glm::vec3 &pivot)
{
    mChangedMarker = true;
}

void TransformComponent::SetMatrix(const glm::mat4 &matrix)
{
    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 position;

    glm::vec3 skew;
    glm::vec4 persp;
    glm::decompose(matrix, scale, rotation, position, skew, persp);

    SetPosition(position);
    SetRotation(glm::degrees(glm::eulerAngles(rotation)));
    SetScale(scale);
}

glm::mat4 TransformComponent::GetMatrix()
{
    // if (mChangedMarker)
    // {
    //     mChangedMarker = false;

    //     glm::mat4 position = glm::translate(glm::mat4(1.0f), mPosition);
    //     glm::mat4 rotation = glm::translate(glm::mat4(1.0f), mPivot) * glm::toMat4(glm::quat(glm::radians(mRotation)))
    //         * glm::translate(glm::mat4(1.0f), -mPivot);
    //     glm::mat4 scale = glm::scale(glm::mat4(1.0f), mScale);

    //     mMatrix = position * rotation * scale;
    // }

    // glm::mat4 position = glm::translate(glm::mat4(1.0f), mPosition);
    // glm::mat4 rotation = glm::translate(glm::mat4(1.0f), mPivot) * glm::toMat4(glm::quat(glm::radians(mRotation)))
    //     * glm::translate(glm::mat4(1.0f), -mPivot);
    // glm::mat4 scale = glm::scale(glm::mat4(1.0f), mScale);

    // mMatrix = position * rotation * scale;    

    glm::mat4 position = glm::translate(glm::mat4(1.0f), mPosition);
    glm::mat4 rotation = glm::toMat4(glm::quat(glm::radians(mRotation)));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), mScale);

    mMatrix = position * rotation * scale;

    return mMatrix;
}

const std::string &TransformComponent::GetDebugInfo()
{
    if (mChangedMarker)
    {
        std::stringstream ss;
        ss << "[POSITION] - {x: " << mPosition.x << ", y: " << mPosition.y << ", z: " << mPosition.z << " }\n"
           << "[ROTATION] - {x: " << mRotation.x << ", y: " << mRotation.y << ", z: " << mRotation.z << " }\n"
           << "[SCALE]    - {x: " << mScale.x    << ", y: " << mScale.y    << ", z: " << mScale.z << " }\n";
        mDebugInfo = ss.str();
    }

    return mDebugInfo;
}
