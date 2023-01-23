/**
 * @file PhysicObject.cpp
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief Physic Object
 * @version 0.1
 * @date 2023-01-18
 * 
 * @copyright Copyright Denis Eremenko (c) 2023
 * 
 */
#include "Physics/PhysicObject.h"

PhysicObject::PhysicObject(btCollisionShape *pShape, float mass, const btVector3 &initialPosition, const btQuaternion &initialRotation)
    : m_pShape(nullptr),
      m_pRigidBody(nullptr),
      m_pMotionState(nullptr),
      m_pKitObject(nullptr)
{
    btAssert((!pShape || pShape->getShapeType() != INVALID_SHAPE_PROXYTYPE));

    // store the shape for later usage
    m_pShape = pShape;

	mTransform.setIdentity();
	mTransform.setOrigin(initialPosition);
	mTransform.setRotation(initialRotation);

	// objects of infinite mass can't
	// move or rotate
    bool isDynamic = (mass != 0.0f);
    btVector3 localInertia(0, 0, 0);
    if (isDynamic) {
        pShape->calculateLocalInertia(mass, localInertia);
    }    

	// create the motion state from the initial transform
	m_pMotionState = new btDefaultMotionState(mTransform);   
    m_pMotionState->m_centerOfMassOffset.setOrigin(btVector3(0, (initialPosition.getY() * 0.5f) * -1.0f, 0)); 

	// create the rigid body construction
	// info using the mass, motion state
	// and shape    
    btRigidBody::btRigidBodyConstructionInfo cInfo(mass, m_pMotionState, pShape, localInertia);
    
    // create the rigid body
    m_pRigidBody = new btRigidBody(cInfo);
    m_pRigidBody->setUserPointer(this);

    mDirty = true;
}

const glm::mat4& PhysicObject::GetTransform()
{
    if (mDirty)
    {
        btScalar btTransform[16];
        mTransform.getOpenGLMatrix(&btTransform[0]);

        mOpenGLCollisionTransform = glm::make_mat4(btTransform);
        mOpenGLCollisionTransform *= glm::scale(glm::mat4(1.0f), GetScale());

        mDirty = false;
    }

    return mOpenGLCollisionTransform;
}
const glm::mat4& PhysicObject::GetRenderTransform()
{
    if (mDirty)
    {
        btTransform btTransform = m_pMotionState->m_graphicsWorldTrans * m_pMotionState->m_centerOfMassOffset;

        btScalar xform[16];
        btTransform.getOpenGLMatrix(&xform[0]);
        mOpenGLRenderTransform = glm::make_mat4(xform);
        mOpenGLRenderTransform *= glm::scale(glm::mat4(1.0f), GetScale());        
    }

    return mOpenGLRenderTransform;

}

void PhysicObject::Move(const btVector3 &offset)
{
    m_pRigidBody->translate(offset);
    mTransform = m_pRigidBody->getWorldTransform();
    m_pRigidBody->getMotionState()->setWorldTransform(mTransform);
    mDirty = true;
}

void PhysicObject::Move(const glm::vec3 &offset)
{
    Move(btVector3(offset.x, offset.y, offset.z));
}

void PhysicObject::SetPosition(const btVector3 &position)
{
    mTransform.setOrigin(position);
    m_pRigidBody->setWorldTransform(mTransform);
    m_pRigidBody->getMotionState()->setWorldTransform(mTransform);
    mDirty = true;
}

void PhysicObject::SetPosition(const glm::vec3 &position)
{
    SetPosition(btVector3(position.x, position.y, position.z));
}

void PhysicObject::SetRotation(const btQuaternion &rotation)
{
    mTransform.setRotation(rotation);
    m_pRigidBody->setWorldTransform(mTransform);
    m_pRigidBody->getMotionState()->setWorldTransform(mTransform);
    mDirty = true;
}

void PhysicObject::SetRotation(const glm::quat &rotation)
{
   SetRotation(btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w)); 
}

void PhysicObject::SetScale(const btVector3 &scale)
{
    m_pShape->setLocalScaling(scale);
    mDirty = true;
}

void PhysicObject::SetScale(const glm::vec3 &scale)
{
    SetScale(btVector3(scale.x, scale.y, scale.z));
}

glm::vec3 PhysicObject::GetPosition() const
{
    btVector3 origin = mTransform.getOrigin();
    return glm::vec3(origin.getX(), origin.getY(), origin.getZ());
}

glm::quat PhysicObject::GetRotation() const
{
    btQuaternion rotation = mTransform.getRotation();
    return glm::quat(rotation.getX(), rotation.getY(), rotation.getZ(), rotation.getW());
}

glm::vec3 PhysicObject::GetScale() const
{
    btVector3 scale = m_pShape->getLocalScaling();
    return glm::vec3(scale.getX(), scale.getY(), scale.getZ());
}

PhysicObject::~PhysicObject()
{
    if (m_pRigidBody)
    {
        delete m_pRigidBody;
        m_pRigidBody = nullptr;
    }

    if (m_pMotionState)
    {
        delete m_pMotionState;
        m_pMotionState = nullptr;
    }

    if (m_pShape)
    {
        delete m_pShape; 
        m_pShape = nullptr;
    }  
}
