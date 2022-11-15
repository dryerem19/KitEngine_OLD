#pragma once
#include "KitTexture.h"

namespace Render
{
    class KitMaterial
    {
    public:
        std::string mName;
        std::vector<KitTexture> diffuseTextures;
    };
}