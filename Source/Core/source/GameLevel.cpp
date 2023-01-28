#include "pch.h"
#include "Entity.h"
#include "GameLevel.h"

#include "ResourceManager.h"

GameLevel::GameLevel()
{
    mPhysics.Initialize();
}

void GameLevel::Serialize(const std::string& filepath)
{
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "Entity";
    out << YAML::Value << YAML::BeginSeq;

    for (auto& object : _objects)
    {
        if(object->Type() == KIT_OBJECT_ENTITY)
        {
            auto& tr = object->transform;

            out << YAML::BeginMap;
            out << YAML::Key << "position";
            out << YAML::Flow;
            out << YAML::BeginSeq;
            out << tr.GetPosition().x;
            out << tr.GetPosition().y;
            out << tr.GetPosition().z;
            out << YAML::EndSeq;

            out << YAML::Key << "rotation";
            out << YAML::Flow;
            out << YAML::BeginSeq;
            out << tr.GetRotation().x;
            out << tr.GetRotation().y;
            out << tr.GetRotation().z;
            out << YAML::EndSeq;    

            out << YAML::Key << "scale";
            out << YAML::Flow;
            out << YAML::BeginSeq;
            out << tr.GetScale().x;
            out << tr.GetScale().y;
            out << tr.GetScale().z;
            out << YAML::EndSeq;    

            out << YAML::Key << "library";
            out << YAML::Value << object->dnm_cast_entity()->GetModel()->mFilepath;
            out << YAML::EndMap;
        }
        
    }

    out << YAML::EndSeq;
    out << YAML::Key << "Skybox";
    out << YAML::Value << mSkyBox.GetPath();
    out << YAML::EndMap;
    std::ofstream fout(std::filesystem::path(filepath).concat(".level").string());
    fout << out.c_str();
}

void GameLevel::Deserialize(const std::string& filepath)
{
    Clear();

    YAML::Node level = YAML::LoadFile(filepath);
    for (auto&& entity : level["Entity"])
    {
        auto ent = CreateEntity();
        ent->transform.SetPosition(entity["position"][0].as<float>(),
            entity["position"][1].as<float>(), entity["position"][2].as<float>());
        ent->transform.SetRotation(entity["rotation"][0].as<float>(),
            entity["rotation"][1].as<float>(), entity["rotation"][2].as<float>());
        ent->transform.SetScale(entity["scale"][0].as<float>(),
            entity["scale"][1].as<float>(), entity["scale"][2].as<float>());
        ent->SetModel(Core::ResourceManager::Instance().GetModel(entity["library"].as<std::string>()));
        ent->SetName(ent->GetModel()->mName);
    }

    std::string skybox_path = level["Skybox"].as<std::string>();
    if (std::filesystem::exists(skybox_path)) {
        mSkyBox.Deserialize(level["Skybox"].as<std::string>());
    }
}

void GameLevel::Update()
{

    for (auto obj : _objects)
    {
        
    }

    mPhysics.Update(1 / 60);
    mPhysics.DebugRender();
}

void GameLevel::InitSkybox(const std::string &filepath)
{
    mSkyBox.Deserialize(filepath);
}

KitLight* GameLevel::CreateLigth()
{
    _lights.emplace_back(std::make_unique<KitLight>(mPhysics));
    _lights.back()->SetID(_lights.size() - 1);
    return _lights.back().get();
}

void GameLevel::DeleteLight()
{
    
}

Entity* GameLevel::CreateEntity()
{
    _objects.emplace_back(std::make_unique<Entity>(mPhysics));
    _objects.back()->SetID(_objects.size() - 1);
    return _objects.back().get()->dnm_cast_entity();
}

SoundBuffer *GameLevel::CreateSound()
{
    _soundsources.emplace_back(std::make_unique<SoundBuffer>(mPhysics));
    _soundsources.back()->SetID(_objects.size() - 1);
    return _soundsources.back().get();
}

GameLevel& GameLevel::Get()
{
    static GameLevel instance;
    return instance;
}

void GameLevel::Clear()
{
    _objects.clear();
}
