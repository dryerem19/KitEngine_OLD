#include "pch.h"
#include "GameLevel.h"
#include "Entity.h"


void Entity::Spawn()
{
    Render::GameLevel::Get().mEntities.push_back(shared_from_this());

    btCollisionShape* colShape = new btSphereShape(btScalar(1.));
    Render::GameLevel::Get().collisionShapes.push_back(colShape);

    /// Create Dynamic Objects
    btTransform startTransform;
    startTransform.setIdentity();

    btScalar mass(90.f);

    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
        colShape->calculateLocalInertia(mass, localInertia);

    startTransform.setOrigin(btVector3(2, 20, 0));
    mTransform.SetPosition(2, 20, 0);

    //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
    body = new btRigidBody(rbInfo);

    Render::GameLevel::Get().mDynamicsWorld->addRigidBody(body);    
}

void Entity::Update()
{
    // glm::mat4 phys_transform;
    // body->getWorldTransform().getOpenGLMatrix(glm::value_ptr(phys_transform));

    // const auto& m_2 = mTransform.GetModelMatrix();
    // mTransform.SetModelMatrix(m_2)

    //mTransform.SetPosition(glm::vec3(transform.getOrigin().getX(), transform.getOrigin().getY(), transform.getOrigin().getZ()));
}

void Entity::SetModel(std::shared_ptr<Model> model)
{
    if (model)
    {
        mModel = model;
    }
}


Entity::Entity(const std::string& name /* = Root */)
{
    mId++;
}
