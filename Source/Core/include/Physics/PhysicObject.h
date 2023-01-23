/**
 * @file PhysicObject.h
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief Physic Object
 * @version 0.1
 * @date 2023-01-18
 * 
 * @copyright Copyright Denis Eremenko (c) 2023
 * 
 */
#pragma once
#include <BulletDynamics/btBulletDynamicsCommon.h>
#include <glm/glm.hpp>

class KitObject;

class PhysicObject
{
private:
    btCollisionShape* m_pShape;
    btRigidBody* m_pRigidBody;
    btDefaultMotionState* m_pMotionState;
    btTransform mTransform;
    glm::mat4 mOpenGLCollisionTransform;
    glm::mat4 mOpenGLRenderTransform;
    KitObject* m_pKitObject;
    bool mDirty;
public:
    PhysicObject(btCollisionShape* pShape, float mass, const btVector3& initialPosition = btVector3(0, 0, 0), 
        const btQuaternion& initialRotation = btQuaternion(0, 0, 0, 1));
    inline btCollisionShape* GetShape() { return m_pShape; }  
    inline btRigidBody* GetRigidBody() { return m_pRigidBody; }      
    inline btDefaultMotionState* GetMotionState() { return m_pMotionState; }

    /**
     * @brief Возвращает трансформацию физического тела
     * Положение физического тела может не совпадать с положением визуала из-за смещённого центра масс
     * Используйте GetRenderTransform(), чтобы получить трансформацию визуала
     * @return const glm::mat4& трансформация физического тела
     */
    const glm::mat4& GetTransform();

    /**
     * @brief Возвращает трансформацию визуала
     * Домножает трансформацию тела на смещение центра масс, используйте этот метод, 
     * чтобы нарисовать визуал внутри физического тела
     * @return const glm::mat4& трансформация визуала
     */
    const glm::mat4& GetRenderTransform();

    inline void SetKitObject(KitObject* pKitObject) { m_pKitObject = pKitObject; }
    inline KitObject* GetKitObject() { return m_pKitObject; }
    inline bool HasKitObject() const { return m_pKitObject != nullptr ? true : false; }
    void Move(const btVector3& offset);
    void Move(const glm::vec3& offset);
    void SetPosition(const btVector3& position);
    void SetPosition(const glm::vec3& position);
    void SetRotation(const btQuaternion& rotation);
    void SetRotation(const glm::quat& rotation);
    void SetScale(const btVector3& scale);
    void SetScale(const glm::vec3& scale);
    glm::vec3 GetPosition() const;
    glm::quat GetRotation() const;
    glm::vec3 GetScale() const;
    ~PhysicObject();
};