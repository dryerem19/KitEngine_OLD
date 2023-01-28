#include "pch.h"
#include "Entity.h"


void Entity::Spawn()
{
    //GameLevel::Get().mEntities.push_back(shared_from_this());
}


void Entity::SetModel(std::shared_ptr<Model> model)
{
    if (model)
    {
        mModel = model;

        const glm::vec3& position = transform.GetPosition();
        glm::quat rotation = glm::quat(glm::radians(transform.GetRotation()));

        glm::vec3 aabb_size = model->mAabb.mMax - model->mAabb.mMin;
        glm::vec3 aabb_center = 0.5f * (model->mAabb.mMin + model->mAabb.mMax);
        glm::mat4 center_pivot = glm::translate(glm::mat4(1.0f), aabb_center) * glm::scale(glm::mat4(1.0f), aabb_size);
        transform.SetPivotPosition(center_pivot[3]);

        transform.SetCenter(center_pivot[3]);

        glm::vec3 pivot_pos(center_pivot[3]);
         glm::vec3  extents { aabb_size.x * 0.5f, aabb_size.y * 0.5f, aabb_size.z * 0.5f };
        // m_pShape = PhysicSystem::Instance().CreateBoxShape(btVector3(extents.x, extents.y, extents.z));
        
        // m_pRigidBody = PhysicSystem::Instance().CreateRigidBody(0, btTransform(
        //     btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w),
        //     btVector3(pivot_pos.x, pivot_pos.y, pivot_pos.z)),
        //     m_pShape);        

        // m_pRigidBody->setCollisionShape(m_pShape);
        // transform.SetRigidBody(m_pRigidBody);

        mPhysic = mPhysics.CreateBoxCollider(aabb_center, aabb_size);

        //transform.SetPosition(center_pivot[3]);
        // mPhysicObject = new PhysicObject(new btBoxShape(extents), 0.0f, btVector3(pivot_pos.x, pivot_pos.y, pivot_pos.z));
        // //mPhysicObject = new PhysicObject(new btBvhTriangleMeshShape(model->pTempMesh, true, true), 0.0f, btVector3(pivot_pos.x, pivot_pos.y, pivot_pos.z));
        // mPhysicObject->SetKitObject(this);
        // PhysicSystem::Instance().AddRigidBody(mPhysicObject->GetRigidBody()); 
    }
}


Entity::Entity(KitEngine::Physics::Physics& physics) : KitObject(KIT_OBJECT_ENTITY, physics)
{

}

void Entity::Update()
{
    if (mRigidBody)
    {
        btTransform transform;
        mRigidBody->getMotionState()->getWorldTransform(transform);

        glm::mat4 matrix;
        transform.getOpenGLMatrix(glm::value_ptr(matrix));
        SetTransform(matrix, false);
    }
}

void Entity::SetTransform(const glm::mat4 &transform, bool updateRigidbody)
{
    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 position;

    glm::vec3 skew;
    glm::vec4 persp;
    glm::decompose(transform, scale, rotation, position, skew, persp);

    if (updateRigidbody)
    {
        SetPosition(position);
        SetRotation(glm::degrees(glm::eulerAngles(rotation)));
        SetScale(scale);
        return;
    }

    mPosition = position;
    mRotation = rotation;
    mScaled = scale;
    mTransformChanged = true;
}

const glm::mat4 &Entity::GetTransform() const
{
    if (mTransformChanged)
    {
        mTransformChanged = false;

        glm::mat4 position = glm::translate(glm::mat4(1.0f), mPosition);
        glm::mat4 rotation = glm::toMat4(glm::quat(glm::radians(mRotation)));
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), mScaled);

        mTransformMatrix = position * rotation * scale;
    }

    return mTransformChanged;
}

void Entity::SetPosition(const glm::vec3 &position)
{
    mPosition = position;
    if (mRigidBody) {
        btTransform transform = mRigidBody->getWorldTransform();
        transform.setOrigin(btVector3{ position.x, position.y, position.z });
        mRigidBody->setWorldTransform(std::move(transform));
        mRigidBody->getMotionState()->setWorldTransform(std::move(transform));
    }

    mTransformChanged = true;
}

void Entity::SetRotation(const glm::vec3 &rotation)
{
    mRotation = rotation;
    if (mRigidBody) {
        glm::quat q(rotation);
        btTransform transform = mRigidBody->getWorldTransform();
        transform.setRotation(btQuaternion{ q.x, q.y, q.z });
        mRigidBody->setWorldTransform(std::move(transform));
        mRigidBody->getMotionState()->setWorldTransform(std::move(transform));
    }

    mTransformChanged = true;
}

void Entity::SetScale(const glm::vec3 &scale)
{
    mScaled = scale;
    if (mRigidBody) {
        btCollisionShape* pShape = mRigidBody->getCollisionShape();
        if (pShape) {
            pShape->setLocalScaling(btVector3{ scale.x, scale.y, scale.z });
        }
    }

    mTransformChanged = true;
}
