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
    }
}


Entity::Entity(const std::string& name /* = Root */) : KitObject(KIT_OBJECT_ENTITY)
{
    const glm::vec3& position = transform.GetPosition();
    glm::quat rotation = glm::quat(transform.GetRotation());
    
    btCollisionShape* pShape = PhysicSystem::Instance().CreateBoxShape(btVector3(1.0f, 1.0f, 1.0f));
    btRigidBody* pRigidBody = PhysicSystem::Instance().CreateRigidBody(0, btTransform(
        btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w),
        btVector3(position.x, position.y, position.z)
    ), pShape);
    pRigidBody->setUserPointer(this);
}
