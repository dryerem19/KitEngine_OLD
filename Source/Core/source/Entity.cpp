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
        //transform.SetPosition(model->mAabb.mCenter);
        mModel = model;

        const glm::vec3& position = transform.GetPosition();
        glm::quat rotation = glm::quat(glm::radians(transform.GetRotation()));

        const bool useQuantizedAABB = true;
        const bool buildBhv = true;

        
        // m_pShape = new btBvhTriangleMeshShape(mModel->pTempMesh, useQuantizedAABB, buildBhv);

        // m_pShape->setLocalScaling(btVector3(1, 2, 1));
        // m_pRigidBody = PhysicSystem::Instance().CreateRigidBody(0, btTransform(
        //     btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w),
        //     btVector3(position.x, position.y, position.z)),
        //     m_pShape);


        glm::vec3 aabb_size = model->mAabb.mMax - model->mAabb.mMin;

        glm::vec3 aabb_center = 0.5f * (model->mAabb.mMin + model->mAabb.mMax);
        
        glm::mat4 center_pivot = glm::translate(glm::mat4(1.0f), aabb_center) * glm::scale(glm::mat4(1.0f), aabb_size);
        transform.SetPivotPosition(center_pivot[3]);

        glm::vec3 pivot_pos(center_pivot[3]);

        glm::vec3 extents { aabb_size.x * 0.5f, aabb_size.y * 0.5f, aabb_size.z * 0.5f };
        //glm::vec3 half_extents { extents.x / 2, extents.y / 2, extents.z / 2};
        //glm::vec3 model_half_extents = { half_extents.x / 2, half_extents.y / 2, half_extents.z / 2};;

        m_pShape = PhysicSystem::Instance().CreateBoxShape(btVector3(extents.x, extents.y, extents.z));
        //transform.SetRigidBody(m_pRigidBody);

        // m_pShape = PhysicSystem::Instance().CreateBoxShape(btVector3(model->mAabb.mExtents.x * 2, model->mAabb.mExtents.y * 2, model->mAabb.mExtents.z * 2));

        m_pRigidBody = PhysicSystem::Instance().CreateRigidBody(0, btTransform(
            btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w),
            btVector3(pivot_pos.x, pivot_pos.y, pivot_pos.z)),
            m_pShape);        


        m_pRigidBody->setCollisionShape(m_pShape);

        // glm::vec3 g = glm::vec4(model->mAabb.mExtents, 1.0f) * transform.GetModelMatrix();

        // glm::vec3 t = model->mAabb.mMax - model->mAabb.mMin;
        // btVector3 halfSize = {
        //     model->mAabb.mMin.x, model->mAabb.mMin.y, model->mAabb.mMin.z
        // };        
        
        // transform.SetGeometricCenter(model->mAabb.mCenter);

        // m_pRigidBody->setCenterOfMassTransform(btTransform(
        //     btQuaternion(0, 0, 0),
        //     btVector3(0, 5, 0)
        // ));
        // transform.SetPosition(glm::vec3(0, 2, 0));
        // m_pShape = PhysicSystem::Instance().CreateBoxShape(btVector3(2, 5, 2));
        // m_pRigidBody->setCollisionShape(m_pShape);
    }
}


Entity::Entity(const std::string& name /* = Root */) : KitObject(KIT_OBJECT_ENTITY)
{
    // const glm::vec3& position = transform.GetPosition();
    // glm::quat rotation = glm::quat(transform.GetRotation());
    
    // m_pShape = PhysicSystem::Instance().CreateBoxShape(btVector3(1.0f, 2.0f, 1.0f));
    // m_pRigidBody = PhysicSystem::Instance().CreateRigidBody(0, btTransform(
    //     btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w),
    //     btVector3(position.x, position.y, position.z)
    // ), m_pShape);

    // transform.SetRigidBody(m_pRigidBody);
    // m_pRigidBody->setUserPointer(this);


    mTransform.setIdentity();
    mTransform.setOrigin(btVector3(0.f, 0.f, 0.f));
}

Entity::Entity(const std::shared_ptr<Model> &model) : KitObject(KIT_OBJECT_ENTITY)
{
    // SetName(model->mName);

    // const glm::vec3& position = transform.GetPosition();
    // glm::quat rotation = glm::quat(transform.GetRotation());

    // glm::vec3 t = model->mAabb.mMax - model->mAabb.mMin;
    // btVector3 halfSize = {
    //     t.x, t.y, t.z
    // };
    
    // m_pShape = PhysicSystem::Instance().CreateBoxShape(btVector3(1.0f, 1.0f, 1.0f));
    // m_pRigidBody = PhysicSystem::Instance().CreateRigidBody(0, btTransform(
    //     btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w),
    //     btVector3(position.x, 5, position.z)
    // ), m_pShape);


    // // m_pRigidBody->getMotionState()->setWorldTransform(btTransform(
    // //     btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w),
    // //     btVector3(90, 150, 21)        
    // // ));
    // m_pRigidBody->setUserPointer(this);    
}
