#include "pch.h"
#include "KitMaterialFile.h"

void KitMaterialFile::Serialize(const std::string& filepath)
{
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "Name" << YAML::Value << name;
    out << YAML::Key << "diffuse_texture_path" << YAML::Value << diffuse_texture_path;        
    out << YAML::EndMap;

    std::ofstream fout(filepath);
    fout << out.c_str();
}

void KitMaterialFile::Deserialize(const std::string& filepath)
{

}