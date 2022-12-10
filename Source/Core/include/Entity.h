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
#include "Transform.h"

#include <BulletDynamics/btBulletDynamicsCommon.h>

#include "Physics/RigidBody.h"

namespace Render
{
    class GameLevel;
}

/**
 * @brief Базовая игровая сущность
 */
class Entity : public std::enable_shared_from_this<Entity>
{
private:
    inline static uint32_t mId = 0;

protected:
    
    /* Грязный флаг, отвечает за то, была ли изменена сущность */
    bool mIsDirty = true;    

    std::shared_ptr<Model> mModel;

    Transform mTransform;

    btRigidBody* body;

public:
    /**
     * @brief Конструктор узла
     * 
     * @param name имя узла
     */
    Entity(const std::string& name = "Root");


    void SetModel(std::shared_ptr<Model> model);

    std::shared_ptr<Model> GetModel() const { return mModel; }

    inline uint32_t GetId() const { return mId; }

    inline Entity* GetSelf()
    {
        return this;
    }

    void Spawn();
    void Update();

    Transform& GetTransform()
    {
        return mTransform;
    }
};