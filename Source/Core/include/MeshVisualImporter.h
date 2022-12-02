#pragma once
#include "BaseEntity.h"

namespace Core
{
    class MeshVisualImporter
    {
    private:
        std::filesystem::path mFilepath;
        BaseEntity* m_pRootEntity { nullptr };
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
        inline BaseEntity* GetRootEntity() const
        {
            return m_pRootEntity;
        }
    private:
        void ProcessAssimpNode( const aiNode* pNode, const aiScene* pScene, BaseEntity* pRootEntity );
        Render::KitStaticMesh* ProcessAssimpMesh( const aiMesh* pMesh, const aiScene* pScene );
        void ProcessAssimpMaterial( const aiMaterial* pMaterial, const std::string& directory, Render::KitMaterial* kitMaterial );
        std::shared_ptr<Render::KitTexture> LoadMaterialTextures(const aiMaterial* pMaterial, 
    aiTextureType type, const std::string& directory);
    };
}
