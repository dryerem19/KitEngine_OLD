#include "pch.h"
#include "Entity.h"
#include "GameLevel.h"

#include "ResourceManager.h"

GameLevel::GameLevel()
{
    mCollisionConfig = std::make_unique<btDefaultCollisionConfiguration>();
    mDispathcer = std::make_unique<btCollisionDispatcher>(mCollisionConfig.get());
    mBroadphase = std::make_unique<btDbvtBroadphase>();
    mSolver = std::make_unique<btSequentialImpulseConstraintSolver>();
    mDynamicsWorld = std::make_unique<btDiscreteDynamicsWorld>(mDispathcer.get(), mBroadphase.get(), mSolver.get(), mCollisionConfig.get());
    mDynamicsWorld->setGravity(btVector3(0.f, -9.81f, 0.f));
}

void GameLevel::Serialize(const std::string& filepath)
{
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "Entity";
    out << YAML::Value << YAML::BeginSeq;

    for (auto& entity : mEntities)
    {
        auto& tr = entity->GetTransform();

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
        out << YAML::Value << entity->GetModel()->mFilepath;
        out << YAML::EndMap;
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
        auto ent = std::make_shared<Entity>();
        ent->GetTransform().SetPosition(entity["position"][0].as<float>(),
            entity["position"][1].as<float>(), entity["position"][2].as<float>());
        ent->GetTransform().SetRotation(entity["rotation"][0].as<float>(),
            entity["rotation"][1].as<float>(), entity["rotation"][2].as<float>());
        ent->GetTransform().SetScale(entity["scale"][0].as<float>(),
            entity["scale"][1].as<float>(), entity["scale"][2].as<float>());
        ent->SetModel(Core::ResourceManager::Instance().GetModel(entity["library"].as<std::string>()));
        mEntities.emplace_back(ent);
    }

    mSkyBox.Deserialize(level["Skybox"].as<std::string>());
}

void GameLevel::InitSkybox(const std::string& filepath)
{
    mSkyBox.Deserialize(filepath);
}

KitLight& GameLevel::CreateLigth()
{
    mKitLights.emplace_back();
    mKitLights.back().SetID(mKitLights.size() - 1);
    return mKitLights.back();
}

void GameLevel::DeleteLight()
{
    
}

void GameLevel::Clear()
{
    mEntities.clear();
}

Entity* GameLevel::Create(const std::string& name)
{
    // Entity* pObj { nullptr };

    // if (mRegistryNames.find(name) != mRegistryNames.end())
    // {
    //     mRegistryNames[name]++;
    //     std::string new_name = name + "_" + std::to_string(mRegistryNames[name]);
    //     mRegistryNames.insert({new_name, mRegistryNames[name]}); 

    //     mObjects.insert({new_name, std::make_unique<Entity>()});
    //     pObj = mObjects[new_name].get();
    //     pObj->SetName(new_name);
    // }
    // else
    // {
    //     mObjects.insert({name, std::make_unique<Entity>()});
    //     mRegistryNames.insert({name, 0});
    //     pObj = mObjects[name].get();
    //     pObj->SetName(name);
    // }

    // return pObj;
}

GameLevel& GameLevel::Get()
{
    static GameLevel instance;
    return instance;
}