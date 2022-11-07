//
// Created by dryerem19 on 11/6/22.
//

#ifndef LEVELEDITOR_MESHENTRY_H
#define LEVELEDITOR_MESHENTRY_H
#include "pch.h"

namespace kitModelLoader
{
    class MeshEntry
    {
    public:
        uint32_t NumIndices         { 0 };
        uint32_t BaseVertex         { 0 };
        uint32_t BaseIndex          { 0 };
        uint32_t MaterialIndex      { 0 };
    };
}

#endif //LEVELEDITOR_MESHENTRY_H
