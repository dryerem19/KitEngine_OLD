/**
 * @file MaterialComponent.h
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief Material component interface
 * @version 0.1
 * @date 2023-01-31
 * 
 * @copyright Copyright Denis Eremenko (c) 2023
 * 
 */
#pragma once
#include "KitMaterial.h"

struct MaterialComponent
{
    std::shared_ptr<Render::KitMaterial> mMaterial;
};