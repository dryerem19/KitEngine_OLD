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

        glm::vec3 pivot_pos(center_pivot[3]);
        glm::vec3 extents { aabb_size.x * 0.5f, aabb_size.y * 0.5f, aabb_size.z * 0.5f };
        m_pShape = PhysicSystem::Instance().CreateBoxShape(btVector3(extents.x, extents.y, extents.z));
        m_pRigidBody = PhysicSystem::Instance().CreateRigidBody(0, btTransform(
            btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w),
            btVector3(pivot_pos.x, pivot_pos.y, pivot_pos.z)),
            m_pShape);        

        m_pRigidBody->setCollisionShape(m_pShape);
        transform.SetRigidBody(m_pRigidBody);
    }
}


Entity::Entity(const std::string& name /* = Root */) : KitObject(KIT_OBJECT_ENTITY)
{
    mTransform.setIdentity();
    mTransform.setOrigin(btVector3(0.f, 0.f, 0.f));
}

Entity::Entity(const std::shared_ptr<Model> &model) : KitObject(KIT_OBJECT_ENTITY)
{
  
}
