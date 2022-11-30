#pragma once
#include "KitTexture.h"
#include "Shader.h"

namespace Render
{
    class KitMaterial
    {
    private:
        //std::shared_ptr<Shader> mShader;
    public:
        std::string mName;
        std::vector<std::shared_ptr<KitTexture>> diffuseTextures;

        // inline void UseMaterial() const
        // {
        //     mShader.get()->Enable();

        //     mShader->SetUniform1i("uTextureDiffuse", 0);
        //     if(!diffuseTextures.empty()) {
        //         diffuseTextures[0]->Bind();
        //     }            
        // }

        // inline void UnuseMaterial() const
        // {
        //     mShader.get()->Disable();
        // }

        // inline void SetShaderFromFile(const std::string& filepath)
        // {
        //     assert(filepath.empty());

        //     mShader = std::make_shared<Shader>(filepath);
        // }

        // inline std::shared_ptr<Shader> GetShader() const
        // {
        //     return mShader;
        // }
    };
}