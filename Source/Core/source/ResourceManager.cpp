#include "pch.h"
#include "ResourceManager.h"

namespace Core
{
    void ResourceManager::LoadShader( const std::string& filepath )
    {
        assert(!filepath.empty() && "Filepath must not be empty!");
        
        mShaders.insert({filepath, std::make_shared<Render::Shader>(filepath)});
    }

    void ResourceManager::LoadTexture( const std::string& filepath )
    {
        assert(!filepath.empty() && "Filepath must not be empty!");

        mTextures.insert({filepath, std::make_shared<Render::KitTexture>(filepath, Render::KitTextureType::Diffuse)});
    }

    // std::shared_ptr<Render::Texture> ResourceManager::GetCubemap(const std::string& tx1, const std::string& tx2, 
    //                                                              const std::string& tx3, const std::string& tx4,
    //                                                              const std::string& tx5, const std::string& tx6)
    // {
        
    // }

    std::shared_ptr<Render::KitMaterial> ResourceManager::GetMaterial( const std::string& filepath )
    {
        assert(!filepath.empty() && "Filepath must not be empty!");

        if(mMaterials.find(filepath) != mMaterials.end())
        {
            return mMaterials[filepath];
        }
        
        mMaterials.insert({filepath, std::make_shared<Render::KitMaterial>(filepath)});
        return mMaterials[filepath];
    }
}