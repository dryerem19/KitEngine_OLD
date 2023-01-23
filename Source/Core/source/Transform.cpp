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
    // glm::vec3 deltaPosition = p - mTranslation;
    // mPivotPosition += deltaPosition;   

    // UpdatePivot();

    mTranslation.x = p.x;
    mTranslation.y = p.y;
    mTranslation.z = p.z;
    mDirty = true;

    // UpdateRigidBody();
}

void Transform::SetPosition(const float& x, const float& y, const float& z)
{
    glm::vec3 deltaPosition = glm::vec3(x, y, z) - mTranslation;
    mPivotPosition += deltaPosition;  

    // UpdatePivot();

    mTranslation.x = x;
    mTranslation.y = y;
    mTranslation.z = z;
    mDirty = true;

    // UpdateRigidBody();
}

void Transform::SetRotation(const glm::vec3& r)
{
    mRotation.x = r.x;
    mRotation.y = r.y;
    mRotation.z = r.z;
    mDirty = true;
    // UpdatePivot();
    // UpdateRigidBody();
}

void Transform::SetRotation(const float& x, const float& y, const float& z)
{
    mRotation.x = x;
    mRotation.y = y;
    mRotation.z = z;
    mDirty = true;
    // UpdatePivot();
    // UpdateRigidBody();
}

void Transform::SetScale(const glm::vec3& s)
{
    mScale.x = s.x;
    mScale.y = s.y;
    mScale.z = s.z;
    mDirty = true;

    //UpdateRigidBodyScale();
}

void Transform::SetScale(const float& x, const float& y, const float& z)
{
    mScale.x = x;
    mScale.y = y;
    mScale.z = z;
    mDirty = true;

    //UpdateRigidBodyScale();
}

void Transform::SetTransform(const glm::mat4 &transform)
{
    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 position;

    glm::vec3 skew;
    glm::vec4 persp;
    glm::decompose(transform, scale, rotation, position, skew, persp);

    SetPosition(position);
    SetRotation(glm::degrees(glm::eulerAngles(rotation)));
    SetScale(scale);
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
        mDirty = false;        
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), mTranslation);
        glm::mat4 rotationMatrix = glm::toMat4(glm::quat(mRotation));
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), mScale);
        //mModelMatrix = translationMatrix * scaleMatrix * rotationMatrix;

        glm::mat4 centerMatrix = glm::translate(glm::mat4(1.0f), mPivotPosition);
        mModelMatrix = translationMatrix * scaleMatrix * rotationMatrix;

        // glm::mat4 pivotTranslationMatrix = glm::translate(glm::mat4(1.0f), mPivotPosition);
        // glm::mat4 objectRotationMatrix = pivotTranslationMatrix * glm::toMat4(glm::quat(mRotation)) * glm::inverse(pivotTranslationMatrix);
        // glm::mat4 objectTranslationMatrix = glm::translate(glm::mat4(1.0f), mTranslation);
        // glm::mat4 objectScaleMatrix = glm::scale(glm::mat4(1.0f), mScale);

        // mModelMatrix = objectTranslationMatrix * objectScaleMatrix * objectRotationMatrix;
    }
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

// void Transform::UpdateRigidBody()
// {
//     if (!m_pRigidBody) {
//         return;
//     }

//     const glm::quat rotation = glm::quat(mRotation);

//     btTransform transform;
//     transform.setIdentity();
//     transform.setFromOpenGLMatrix(glm::value_ptr(mPivotMatrix));


//     // transform.setIdentity();
//     // transform.setOrigin(btVector3(mPivotPosition.x, mPivotPosition.y, mPivotPosition.z));
//     // transform.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w));
    
//     m_pRigidBody->setWorldTransform(transform);
//     m_pRigidBody->getMotionState()->setWorldTransform(transform);
// }

// void Transform::UpdateRigidBodyScale()
// {
//     if (!m_pRigidBody) {
//         return;
//     }
//     m_pRigidBody->getCollisionShape()->setLocalScaling(btVector3(mScale.x, mScale.y, mScale.z));    
// }

// void Transform::UpdatePivot()
// {
//     glm::mat4 pivotTranslationMatrix = glm::translate(glm::mat4(1.0f), mPivotPosition);
//     glm::mat4 pivotRotationMatrix = pivotTranslationMatrix * glm::toMat4(glm::quat(mRotation)) * glm::inverse(pivotTranslationMatrix);
//     mPivotMatrix = pivotTranslationMatrix * pivotRotationMatrix;
// }
