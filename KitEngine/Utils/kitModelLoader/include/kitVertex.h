//
// Created by dryerem19 on 11/7/22.
//

#ifndef LEVELEDITOR_KITVERTEX_H
#define LEVELEDITOR_KITVERTEX_H
#include "pch.h"

namespace kitModelLoader
{
    class kitVertex
    {
    public:
        aiVector3D mPos;
        aiVector3D mNor;
        aiVector2D mTex;

        kitVertex(aiVector3D pos, aiVector3D nor, aiVector2D tex)
                : mPos(pos), mNor(nor), mTex(tex) {}
    };
}

#endif //LEVELEDITOR_KITVERTEX_H
