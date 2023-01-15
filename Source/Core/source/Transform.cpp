/**
 * @file Transform.cpp
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief Object transformation
 * @version 0.1
 * @date 2022-12-09
 * 
 * @copyright Copyright Denis Eremenko (c) 2022
 * 
 */
#include "pch.h"
#include "Transform.h"

Transform::Transform()
    : m_pRigidBody(nullptr)
{

}

void Transform::SetPosition(const glm::vec3 &p)
{
    mTranslation.x = p.x;
    mTranslation.y = p.y;
    mTranslation.z = p.z;
    mDirty = true;

    UpdateRigidBodyPosition();
}

void Transform::SetPosition(const float& x, const float& y, const float& z)
{
    mTranslation.x = x;
    mTranslation.y = y;
    mTranslation.z = z;
    mDirty = true;

    UpdateRigidBodyPosition();
}

void Transform::SetRotation(const glm::vec3& r)
{
    mRotation.x = r.x;
    mRotation.y = r.y;
    mRotation.z = r.z;
    mDirty = true;

    UpdateRigidBodyRotation();
}

void Transform::SetRotation(const float& x, const float& y, const float& z)
{
    mRotation.x = x;
    mRotation.y = y;
    mRotation.z = z;
    mDirty = true;

    UpdateRigidBodyRotation();
}

void Transform::SetScale(const glm::vec3& s)
{
    mScale.x = s.x;
    mScale.y = s.y;
    mScale.z = s.z;
    mDirty = true;

    UpdateRigidBodyScale();
}

void Transform::SetScale(const float& x, const float& y, const float& z)
{
    mScale.x = x;
    mScale.y = y;
    mScale.z = z;
    mDirty = true;

    UpdateRigidBodyScale();
}

void Transform::SetRigidBody(btRigidBody *pRigidBody)
{
    m_pRigidBody = pRigidBody;
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

const glm::mat4& Transform::GetModelMatrix()
{
    if (mDirty)
    {        
        mModelMatrix = glm::translate(glm::mat4(1.0f), mTranslation)
            * glm::toMat4(glm::quat(mRotation))
            * glm::scale(glm::mat4(1.0f), mScale);
    }

    mDirty = false;
    return mModelMatrix;
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

void Transform::UpdateRigidBodyPosition()
{
    if (!m_pRigidBody) {
        return;
    }

    const btTransform& rigidBodyTransform = m_pRigidBody->getWorldTransform();
    m_pRigidBody->setWorldTransform(btTransform(
        rigidBodyTransform.getRotation(),
        btVector3(mTranslation.x, mTranslation.y, mTranslation.z)
    ));
}

void Transform::UpdateRigidBodyRotation()
{
    if (!m_pRigidBody) {
        return;
    }

    const glm::quat q = glm::quat(mRotation);
    const btTransform& rigidBodyTransform = m_pRigidBody->getWorldTransform();
    m_pRigidBody->setWorldTransform(btTransform(
        btQuaternion(q.x, q.y, q.z, q.w),
        rigidBodyTransform.getOrigin()
    ));    
}

void Transform::UpdateRigidBodyScale()
{
    if (!m_pRigidBody) {
        return;
    }

    m_pRigidBody->getCollisionShape()->setLocalScaling(btVector3(mScale.x, mScale.y, mScale.z));    
}
