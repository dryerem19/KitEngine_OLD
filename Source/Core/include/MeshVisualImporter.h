/**
 * @file MeshVisualImporter.h
 * @author Eugeniy Dubasov (dubasov.eugeni@yandex.ru)
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-27
 * 
 * @copyright Copyright Eugeniy Dubasov (c) 2022
 * @copyright Copyright Denis Eremenko (c) 2022
 * 
 */
#pragma once
#include "KitModelFile.h"
#include "KitMaterialFile.h"
#include "KitCore.h"

namespace Core
{
    class MeshVisualImporter
    {
    public:
        std::vector<std::string> mMaterialFilepathCache;

        std::filesystem::path mFilepath;
        

        std::string mModelSaveDirectory;
        std::string mMaterialSavelDirectory;
        std::string mTextureSaveDirectory;
        std::string mModelName;

        std::string mTextureDirectory;

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
        
    private:
        void ParseMeshes(const aiScene* pScene, KitModelFile& kmf);
        std::string ProcessAssimpMaterial( const aiMaterial* pMaterial, const std::string& directory);
    };
}
