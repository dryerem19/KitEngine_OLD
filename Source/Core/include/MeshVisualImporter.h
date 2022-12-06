#pragma once
#include "GameObject.h"

#include "KitModelFile.h"
#include "KitMaterialFile.h"

namespace Core
{
    class MeshVisualImporter
    {
    public:
        std::vector<std::string> mMaterialFilepathCache;

        std::filesystem::path mFilepath;
        GameObject* m_pRootEntity { nullptr };

        std::string mModelSaveDirectory;
        std::string mMaterialSavelDirectory;
        std::string mTextureSaveDirectory;

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
        std::string ProcessAssimpMaterial( const aiMaterial* pMaterial, const std::string& directory);
    };
}
