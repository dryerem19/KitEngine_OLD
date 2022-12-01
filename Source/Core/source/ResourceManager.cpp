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

        mTextures.insert({filepath, std::make_shared<Render::Texture>(filepath)});
    }
}