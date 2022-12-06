#include "pch.h"
#include "KitMaterial.h"

namespace Render
{
    KitMaterial::KitMaterial()
    {
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