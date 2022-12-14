/**
 * @file Transform.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "pch.h"
#include "Transform.h"

void Transform::SetPosition(const glm::vec3& p)
{
    mTranslation.x = p.x;
    mTranslation.y = p.y;
    mTranslation.z = p.z;
    mDirty = true;
}

void Transform::SetPosition(const float& x, const float& y, const float& z)
{
    mTranslation.x = x;
    mTranslation.y = y;
    mTranslation.z = z;
    mDirty = true;
}

void Transform::SetRotation(const glm::vec3& r)
{
    mRotation.x = r.x;
    mRotation.y = r.y;
    mRotation.z = r.z;
    mDirty = true;
}

void Transform::SetRotation(const float& x, const float& y, const float& z)
{
    mRotation.x = x;
    mRotation.y = y;
    mRotation.z = z;
    mDirty = true;
}

void Transform::SetScale(const glm::vec3& s)
{
    mScale.x = s.x;
    mScale.y = s.y;
    mScale.z = s.z;
    mDirty = true;
}

void Transform::SetScale(const float& x, const float& y, const float& z)
{
    mScale.x = x;
    mScale.y = y;
    mScale.z = z;
    mDirty = true;
}

const glm::vec3& Transform::GetPosition() const
{
    return mTranslation;
}

const glm::vec3& Transform::GetRotation() const
{
    return mRotation;
}

const glm::vec3& Transform::GetScale() const
{
    return mScale;
}

const float* Transform::GetModelMatrix()
{
    if (mDirty)
    {
        glm::mat4 rotation = glm::toMat4(glm::quat(mRotation));
        
        mModelMatrix = glm::translate(glm::mat4(1.0f), mTranslation)
            * rotation
            * glm::scale(glm::mat4(1.0f), mScale);
    }

    mDirty = false;
    return glm::value_ptr(mModelMatrix);
}

std::string Transform::DebugString() const
{
    std::stringstream ss;
    ss << "[TRANSFORM INFO]\n" 
       << "[POSITION] - {x: " << mTranslation.x << ", y: " << mTranslation.y << ", z: " << mTranslation.z << " }"
       << "[ROTATION] - {x: " << mRotation.x << ", y: " << mRotation.y << ", z: " << mRotation.z << " }"
       << "[SCALED]   - {x: " << mScale.x << ", y: " << mScale.y << ", z: " << mScale.z << " }\n";
    return ss.str();
}

bool Transform::IsDirty() const
{
    return mDirty;
}