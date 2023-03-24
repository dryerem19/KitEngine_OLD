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
    // YAML::Emitter out;
    // out << YAML::BeginMap;
    // out << YAML::Key << "Entity";
    // out << YAML::Value << YAML::BeginSeq;

    // for (auto& object : _objects)
    // {
    //     out << YAML::BeginMap;
    //     out << YAML::Key << "position";
    //     out << YAML::Flow;
    //     out << YAML::BeginSeq;
    //     out << object->GetPosition().x;
    //     out << object->GetPosition().y;
    //     out << object->GetPosition().z;
    //     out << YAML::EndSeq;

    //     out << YAML::Key << "rotation";
    //     out << YAML::Flow;
    //     out << YAML::BeginSeq;
    //     out << object->GetRotation().x;
    //     out << object->GetRotation().y;
    //     out << object->GetRotation().z;
    //     out << YAML::EndSeq;    

    //     out << YAML::Key << "scale";
    //     out << YAML::Flow;
    //     out << YAML::BeginSeq;
    //     out << object->GetScale().x;
    //     out << object->GetScale().y;
    //     out << object->GetScale().z;
    //     out << YAML::EndSeq;    

    //     out << YAML::Key << "library";
    //     out << YAML::Value << object->GetModel()->mFilepath;
    //     out << YAML::EndMap;
        
    // }

    // out << YAML::EndSeq;
    // out << YAML::Key << "Skybox";
    // out << YAML::Value << mSkyBox.GetPath();
    // out << YAML::EndMap;
    // std::ofstream fout(std::filesystem::path(filepath).concat(".level").string());
    // fout << out.c_str();
}

void GameLevel::Deserialize(const std::string& filepath)
{
    // Clear();

    // YAML::Node level = YAML::LoadFile(filepath);
    // for (auto&& entity : level["Entity"])
    // {
    //     auto ent = CreateEntity();
    //     ent->SetPosition(entity["position"][0].as<float>(),
    //         entity["position"][1].as<float>(), entity["position"][2].as<float>());
    //     ent->SetRotation(entity["rotation"][0].as<float>(),
    //         entity["rotation"][1].as<float>(), entity["rotation"][2].as<float>());
    //     ent->SetScale(entity["scale"][0].as<float>(),
    //         entity["scale"][1].as<float>(), entity["scale"][2].as<float>());
    //     ent->SetModel(Core::ResourceManager::Instance().GetModel(entity["library"].as<std::string>()));
    //     //ent->SetName(ent->GetModel()->mName);
    // }

    // std::string skybox_path = level["Skybox"].as<std::string>();
    // if (std::filesystem::exists(skybox_path)) {
    //     mSkyBox.Deserialize(level["Skybox"].as<std::string>());
    // }
}

void GameLevel::Update()
{
    // mPhysics.Update(1 / 60);
    // mPhysics.DebugRender();

    // for (auto& entity : _objects)
    // {
    //     entity->Update();
    // }

    mDynamicsWorld->stepSimulation(1 /60, 10);
    mDynamicsWorld->debugDrawWorld();
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
    // _objects.emplace_back(std::make_unique<Entity>(*mDynamicsWorld.get()));
    // return _objects.back().get();
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

void GameLevel::Initialize()
{
    // Set up the collision configuration and dispatcher
    mCollisionConfig  = std::make_unique<btDefaultCollisionConfiguration>();
    mDispathcer       = std::make_unique<btCollisionDispatcher>(mCollisionConfig.get());

    // Build the broadphase
    mBroadphase       = std::make_unique<btDbvtBroadphase>();

    // The actual physics solver
    mSolver           = std::make_unique<btSequentialImpulseConstraintSolver>();

    // The world
    mDynamicsWorld    = std::make_unique<btDiscreteDynamicsWorld>(mDispathcer.get(), mBroadphase.get(), mSolver.get(), mCollisionConfig.get());
    mDynamicsWorld->setGravity(btVector3(0.f, -10.0f, 0.f));

    mPhysicsDebugRenderer = std::make_unique<GLDebugDrawer>();
    mDynamicsWorld->setDebugDrawer(mPhysicsDebugRenderer.get());
    mDynamicsWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_MAX_DEBUG_DRAW_MODE);
}

void GameLevel::Clear()
{
    _objects.clear();
}
