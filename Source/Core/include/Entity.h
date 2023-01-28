/**
 * @file Entity.h
 * @author dryerem19 (mamayma@dgmail.com)
 * @brief Базовая логика игровой сущности
 * @version 0.1
 * @date 2022-11-30
 * 
 * @copyright Copyright dryerem19 (c) 2022
 * 
 */
#pragma once
#include "Model.h"
#include "KitObject.h"

#include "PhysicSystem.h"

/**
 * @brief Базовая игровая сущность
 */
class Entity : public std::enable_shared_from_this<Entity>, public KitObject
{
protected:
    
    /* Грязный флаг, отвечает за то, была ли изменена сущность */
    bool mIsDirty = true;    

    std::shared_ptr<Model> mModel;


    std::unique_ptr<KitEngine::Physics::BoxCollider> mPhysic;

private:
    glm::vec3 mPosition, mRotation, mScaled;
    glm::mat4 mTransformMatrix;
    bool mTransformChanged;
    std::unique_ptr<btRigidBody> mRigidBody;

public:
    Entity(KitEngine::Physics::Physics& physics);

    void Update();
    void SetTransform(const glm::mat4& transform, bool updateRigidbody = true);
    const glm::mat4& GetTransform();
    void SetPosition(const glm::vec3& position);
    void SetRotation(const glm::vec3& rotation);
    void SetScale(const glm::vec3& scale);


    void SetModel(std::shared_ptr<Model> model);

    std::shared_ptr<Model> GetModel() const { return mModel; }

    Entity* dnm_cast_entity() override
    {
        return dynamic_cast<Entity*>(this);
    }

    void Spawn();
};