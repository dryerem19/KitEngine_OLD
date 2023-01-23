/**
 * @file KitObject.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "Transform.h"
#include "Physics/PhysicObject.h"

#include "ResourceManager.h"

#define KIT_OBJECT_NONE     0
#define KIT_OBJECT_ENTITY   1
#define KIT_OBJECT_LIGHT    2
#define KIT_OBJECT_SOUND    3

class GameLevel;

class Entity;

class KitObject
{
private:
    PhysicObject* m_pPhysicObject = nullptr;
public:
    KitObject(uint32_t type) : mID(0), _type(type) {};
    //KitObject(uint32_t type, const std::string& name) : mID(0), _type(type), _name(name) {};
    Transform transform;
    virtual Entity* dnm_cast_entity()  { return nullptr;}
    uint32_t GetID() const { return mID; }

    uint32_t Type() const { return _type; }

    std::string& GetName()
    {
        return _name;
    }

    void SetName(const std::string& name)
    {
        _name = name;
    }


    void SetPosition(const glm::vec3& position);
    void SetRotation(const glm::vec3& rotation);
    void SetScale(const glm::vec3& scale);

    void SetVisualPath(const std::string& path);

    bool IsPhysicObject() const;

    virtual void OnPicked();

private:
    friend class GameLevel;
    uint32_t mID;
    uint32_t _type = KIT_OBJECT_NONE;
    std::string _name;
    

    void SetID(const uint32_t id) 
    {
        mID = id;
    };
};
