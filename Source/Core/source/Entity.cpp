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
        // glm::vec3 t = model->mAabb.mMax - model->mAabb.mMin;
        // btVector3 halfSize = {
        //     model->mAabb.mMin.x, model->mAabb.mMin.y, model->mAabb.mMin.z
        // };        

        //m_pShape = PhysicSystem::Instance().CreateBoxShape(halfSize);
        //m_pRigidBody->setCollisionShape(m_pShape);
    }
}


Entity::Entity(const std::string& name /* = Root */) : KitObject(KIT_OBJECT_ENTITY)
{
    const glm::vec3& position = transform.GetPosition();
    glm::quat rotation = glm::quat(transform.GetRotation());
    
    m_pShape = PhysicSystem::Instance().CreateBoxShape(btVector3(1.0f, 1.0f, 1.0f));
    m_pRigidBody = PhysicSystem::Instance().CreateRigidBody(0, btTransform(
        btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w),
        btVector3(position.x, position.y, position.z)
    ), m_pShape);

    transform.SetRigidBody(m_pRigidBody);
    m_pRigidBody->setUserPointer(this);
}

Entity::Entity(const std::shared_ptr<Model> &model) : KitObject(KIT_OBJECT_ENTITY)
{
    SetName(model->mName);

    const glm::vec3& position = transform.GetPosition();
    glm::quat rotation = glm::quat(transform.GetRotation());

    glm::vec3 t = model->mAabb.mMax - model->mAabb.mMin;
    btVector3 halfSize = {
        t.x, t.y, t.z
    };
    
    m_pShape = PhysicSystem::Instance().CreateBoxShape(btVector3(1.0f, 1.0f, 1.0f));
    m_pRigidBody = PhysicSystem::Instance().CreateRigidBody(0, btTransform(
        btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w),
        btVector3(position.x, position.y, position.z)
    ), m_pShape);


    // m_pRigidBody->getMotionState()->setWorldTransform(btTransform(
    //     btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w),
    //     btVector3(90, 150, 21)        
    // ));
    m_pRigidBody->setUserPointer(this);    
}
