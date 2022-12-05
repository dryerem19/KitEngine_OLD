#pragma once
#include "GameObject.h"

#include "KitModelFile.h"

namespace Core
{
    class MeshVisualImporter
    {
    private:
        std::filesystem::path mFilepath;
        GameObject* m_pRootEntity { nullptr };

        std::string mModelName;
    public:
         MeshVisualImporter() = default;
         MeshVisualImporter( const std::filesystem::path& filepath )
            : mFilepath( filepath ) { }

        void LoadVisual( void );
        inline void LoadVisual( const std::filesystem::path& filepath )
        {
            mFilepath = filepath;
            this->LoadVisual();
        }
        inline GameObject* GetRootEntity() const
        {
            return m_pRootEntity;
        }
    private:
        void ProcessAssimpNode(const aiNode* pNode, const aiScene* pScene, KMFNode* pKmfNode);
        KMFMesh ProcessAssimpMesh( const aiMesh* pMesh, const aiScene* pScene );
        void ProcessAssimpMaterial( const aiMaterial* pMaterial, const std::string& directory, Render::KitMaterial* kitMaterial );
        std::shared_ptr<Render::KitTexture> LoadMaterialTextures(const aiMaterial* pMaterial, 
    aiTextureType type, const std::string& directory);
    };
}
