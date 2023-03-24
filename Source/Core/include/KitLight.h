/**
 * @file KitLight.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "KitTransform.h"
#include "KitObject.h"

#include "PhysicSystem.h"


// enum class LightType
// {
//     None = 0,
//     DirectionalLight,
//     PointLight,
//     SpotLight  
// };

class KitLight : public KitObject
{
public:
    Render::KitTransform mTransform;
    KitLight(KitEngine::Physics::Physics& physics) : KitObject(KIT_OBJECT_LIGHT, physics)
    {
        SetName("light");

        mPhysicObject = new PhysicObject(new btBoxShape(btVector3(1.0f, 1.0f, 1.0f)), 0.0f);
        mPhysicObject->SetKitObject(this);
        //PhysicSystem::Instance().AddRigidBody(mPhysicObject->GetRigidBody());         

    }

    glm::vec4 mColor = glm::vec4(1.f, 1.f, 1.f, 1.f);
    float mAmbientStrength = 1.f;
    float mSpecularStrength = 0.5f;
};

KitLight* dnm_cast_light(KitObject* object);
