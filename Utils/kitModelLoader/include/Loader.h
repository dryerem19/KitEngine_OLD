//
// Created by dryerem19 on 11/5/22.
//

#ifndef LEVELEDITOR_LOADER_H
#define LEVELEDITOR_LOADER_H

struct aiScene;
struct aiMesh;

namespace kitModelLoader
{
    class Loader
    {
    public:
        std::vector<uint32_t>   mIndices;
        std::vector<MeshEntry>  mMeshes;
        std::vector<Vertex>     mVertices;

        Loader  ( ) = default;
        ~Loader ( ) = default;

        void Import (const std::string& filepath);
        void Clear  ( );

    private:
        void InitScene                  (const aiScene* pScene, const std::string& filepath);
        void CountVerticesAndIndices    (const aiScene* pScene, uint32_t& verticesCount, uint32_t& indicesCount);
        void ReserveSpace               (uint32_t& verticesCount, uint32_t& indicesCount);
        void InitAllMeshes              (const aiScene* pScene);
        void InitMesh                   (const aiMesh*  pMesh);
    };
}

#endif //LEVELEDITOR_LOADER_H
