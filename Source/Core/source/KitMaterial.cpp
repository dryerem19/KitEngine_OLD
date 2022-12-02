#include "pch.h"
#include "KitMaterial.h"

namespace Render
{
    KitMaterial::KitMaterial()
    {
        mShader = Core::ResourceManager::Instance().GetShader("../../Resources/shaders/glsl/transform_test.glsl");
    }
}