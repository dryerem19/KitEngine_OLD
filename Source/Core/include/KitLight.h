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

enum class LightType
{
    None = 0,
    DirectionalLight,
    PointLight,
    SpotLight  
};

class KitLight : public KitObject
{
public:
    Render::KitTransform mTransform;
    
};