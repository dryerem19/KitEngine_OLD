//
// Created by dryerem19 on 11/6/22.
//

#ifndef LEVELEDITOR_KITMATERIAL_H
#define LEVELEDITOR_KITMATERIAL_H

#include "kitTexture.h"
#include <vector>
#include <string>
#include <assimp/types.h>

namespace kitModelLoader
{
    class kitMaterial
    {
    public:
        kitMaterial        () = default;
        kitMaterial        (const kitMaterial&) = default;

        std::vector<kitTexture> mTextures;

        std::string Name        { };
        aiColor3D Ambient       { };
        aiColor3D Diffuse       { };
        aiColor3D Specular      { };
        aiColor3D Sharpness     { };
        aiColor3D Emmissie      { };
        aiColor3D Transparent   { };

    };
}

#endif //LEVELEDITOR_KITMATERIAL_H
