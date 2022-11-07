//
// Created by dryerem19 on 11/6/22.
//

#ifndef LEVELEDITOR_KITTEXTURE_H
#define LEVELEDITOR_KITTEXTURE_H
#include "pch.h"

namespace kitModelLoader
{
    enum class kitTextureType
    {
        None        = aiTextureType_NONE        ,
        Diffuse     = aiTextureType_DIFFUSE     ,
        Specular    = aiTextureType_SPECULAR    ,
        Ambient     = aiTextureType_AMBIENT     ,
        Emissive    = aiTextureType_EMISSIVE    ,
        Height      = aiTextureType_HEIGHT      ,
        Normal      = aiTextureType_NORMALS     ,
        Shinines    = aiTextureType_SHININESS   ,
    };

    class kitTexture
    {
    public:
        kitTexture()                    = default;
        kitTexture(const kitTexture&)   = default;

        kitTextureType          TextureType = kitTextureType::None;
        std::filesystem::path   Path;

        kitTexture(kitTextureType type, std::filesystem::path path)
            : TextureType(type), Path(std::move(path)) { }
    };
}

#endif //LEVELEDITOR_KITTEXTURE_H
