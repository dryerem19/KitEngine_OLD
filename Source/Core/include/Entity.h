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

    btCollisionShape* m_pShape;
    btRigidBody* m_pRigidBody; 


    btTransform mTransform;

public:
    /**
     * @brief Конструктор узла
     * 
     * @param name имя узла
     */
    Entity(const std::string& name = "Root");

    Entity(const std::shared_ptr<Model>& model);


    void SetModel(std::shared_ptr<Model> model);

    std::shared_ptr<Model> GetModel() const { return mModel; }

    Entity* dnm_cast_entity() override
    {
        return dynamic_cast<Entity*>(this);
    }

    void Spawn();
};