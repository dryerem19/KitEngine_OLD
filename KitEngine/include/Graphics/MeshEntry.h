//
// Created by dryerem19 on 11/2/22.
//

#ifndef LEVELEDITOR_MESHENTRY_H
#define LEVELEDITOR_MESHENTRY_H

namespace KitEngine::Graphics
{
    class MeshEntry
    {
    public:
        unsigned int NumIndices         { 0 };
        unsigned int BaseVertex         { 0 };
        unsigned int BaseIndex          { 0 };
        unsigned int MaterialIndex      { 0 };
    };
}

#endif //LEVELEDITOR_MESHENTRY_H
