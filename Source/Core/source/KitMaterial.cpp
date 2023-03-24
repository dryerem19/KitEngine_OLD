#include "pch.h"
#include "KitMaterial.h"
#include "ResourceManager.h"

namespace Render
{
    KitMaterial::KitMaterial()
    {
        mShader = Core::ResourceManager::Instance().GetShader("../../Resources/shaders/glsl/default.shader");
    }

    KitMaterial::KitMaterial(const std::string& filepath)
    {
        KitMaterialFile file;
        file.Deserialize(filepath);

        mName = file.name;
        
        if (std::filesystem::exists(file.diffuse_texture_path)) 
        {
            mMainDiffuseTexture = Core::ResourceManager::Instance().GetTexture(file.diffuse_texture_path);
        }
        
        mShader = Core::ResourceManager::Instance().GetShader(file.shader_path);
    }

    void KitMaterial::Serialize(const std::string& filepath)
    {
        std::filesystem::path material_path(filepath);
        if (!std::filesystem::exists(material_path.remove_filename()))
        {
            std::filesystem::create_directories(material_path);
        }

        YAML::Emitter out;
        out << YAML::BeginMap;
        out << YAML::Key << "Name" << YAML::Value << mName;
        out << YAML::Key << "Diffuse" << YAML::Value << mMainDiffuseTexture->GetPath();
        out << YAML::EndMap;

        std::ofstream fout(filepath);
        fout << out.c_str();
    }

    void KitMaterial::Deserialize(const std::string& filepath)
    {

    }

    void KitMaterial::SetTexture(const std::string &blockName, const std::shared_ptr<KitTexture> &texture)
    {

    }

    void KitMaterial::Bind()
    {
        if (!mShader) {
            return;
        }

        mShader->Bind();
        mShader->SetFloat("u_material.shininess", mShininess);

        if (mDiffuseTex) {
            mShader->SetInt("u_material.diffuse", 0);
            mDiffuseTex->Bind(0);
        }
        if (mSpecularTex) {
            mShader->SetInt("u_material.specular", 1);
            mSpecularTex->Bind(1);
        }
    }

    void KitMaterial::Unbind()
    {
        if (!mShader) {
            return;
        }

        mShader->UnBind();
        
        if (mDiffuseTex) {
            mDiffuseTex->Unbind();
        }
    }
}