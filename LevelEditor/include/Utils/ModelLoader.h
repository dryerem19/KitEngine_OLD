//
// Created by dryerem19 on 11/2/22.
//

#ifndef LEVELEDITOR_MODELLOADER_H
#define LEVELEDITOR_MODELLOADER_H

#include <assimp/Importer.hpp>          // C++ importer interface
#include <assimp/scene.h>               // Output data structure
#include <assimp/postprocess.h>         // Postprocess flags

#include <glm/glm.hpp>                  // glm::vec3, glm::vec2

#include <vector>

#include <Graphics/MeshEntry.h>
#include <Graphics/Vertex.h>

namespace LevelEditor::Utils
{
    class ModelLoader
    {
    private:
        std::vector<unsigned int>                       mIndices;
        std::vector<KitEngine::Graphics::Vertex>        mVertices;
        std::vector<KitEngine::Graphics::MeshEntry>     mMeshEntryes;
        unsigned int                                    mNumVertices;
        unsigned int                                    mNumIndices;
    public:
        ModelLoader();
        ~ModelLoader() = default;

        bool Import                                                             (const std::string& filepath);

        inline std::vector<KitEngine::Graphics::Vertex>     GetVertices         ()        { return mVertices;    }
        inline std::vector<unsigned int>&                   GetIndices          ()        { return mIndices;     }
        inline std::vector<KitEngine::Graphics::MeshEntry>& GetMeshes           ()        { return mMeshEntryes; }
        [[nodiscard]] inline unsigned int                   GetCountOfVertices  () const  { return mNumVertices; }
        [[nodiscard]] inline unsigned int                   GetCountOfIndicies  () const  { return mNumIndices;  }

        void Clear                                                              ();

    private:
        void InitScene                  (const aiScene* pScene, const std::string& filepath);
        void CountVerticesAndIndices    (const aiScene* pScene                             );
        void ReserveSpace               (                                                  );
        void InitAllMeshes              (const aiScene* pScene                             );
        void InitMesh                   (const aiMesh*  pMesh                              );
    };
}

#endif //LEVELEDITOR_MODELLOADER_H
