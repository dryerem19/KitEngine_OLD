//
// Created by dryerem19 on 11/6/22.
//

#ifndef LEVELEDITOR_VERTEX_H
#define LEVELEDITOR_VERTEX_H

namespace kitModelLoader
{
    class Vertex
    {
    public:
        aiVector3D mPos;
        aiVector3D mNor;
        aiVector2D mTex;

        Vertex(aiVector3D pos, aiVector3D nor, aiVector2D tex)
            : mPos(pos), mNor(nor), mTex(tex) {}
    };
}

#endif //LEVELEDITOR_VERTEX_H
