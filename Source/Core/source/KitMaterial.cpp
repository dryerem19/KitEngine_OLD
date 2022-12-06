#include "pch.h"
#include "KitMaterial.h"
#include "ResourceManager.h"

namespace Render
{
    KitMaterial::KitMaterial()
    {
        mShader = Core::ResourceManager::Instance().GetShader("../../Resources/shaders/glsl/transform_test.glsl");
    }

    KitMaterial::KitMaterial(const std::string& filepath)
    {
        KitMaterialFile file;
        file.Deserialize(filepath);
        mName = file.name;
        mMainDiffuseTexture = Core::ResourceManager::Instance().GetTexture(file.diffuse_texture_path);
        mShader = Core::ResourceManager::Instance().GetShader("../../Resources/shaders/glsl/transform_test.glsl");
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
}