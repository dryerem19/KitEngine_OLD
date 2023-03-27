#include "GameLayer.h"

#include "ResourceManager.h"

void GameLayer::OnStart()
{
    // Entity mainCamera = mScene.CreateEntity();
    // auto& cameraComponent = mainCamera.AddComponent<CameraComponent>();

    // Создаём главного игрока 
    Entity player = mScene.CreateEntity();
    player.AddComponent<CameraComponent>();
    player.AddComponent<PlayerComponent>();

    // Регистриуем систему управления игроком
    mScene.RegistrySystem<PlayerControllerSystem>();

    Entity dirLigth = mScene.CreateEntity();
    dirLigth.AddComponent<LightComponent>();

    Entity entity = mScene.CreateEntity();
    entity.AddComponent<ModelComponent>(Core::ResourceManager::Instance().GetModel("../../Resources/models/nanosuit/nanosuit.obj"));
    
    auto& rigidbody = entity.AddComponent<RigidbodyComponent>();
    rigidbody.mMass = 200;
    entity.AddComponent<BoxColliderComponent>(glm::vec3(1, 1, 1));
    
    Entity ground = mScene.CreateEntity();
    ground.AddComponent<ModelComponent>(Core::ResourceManager::Instance().GetModel("../../Resources/models/plane.obj"));
    ground.AddComponent<RigidbodyComponent>();
    ground.AddComponent<BoxColliderComponent>(glm::vec3(10, 1, 10));
    ground.GetTransform().SetPosition({ 0, -50, 0 });
    ground.GetTransform().SetScale({ 1, 1, 1 });

    mScene.OnStart();
    
    //auto pWindow = Core::Application::Instance().GetWindow().get();
    //camera.SetViewportSize(pWindow->GetWidth(), pWindow->GetHeight());

    // Entity* pGround = GameLevel::Get().CreateEntity();
    // pGround->SetModel(Core::ResourceManager::Instance().GetModel("data/plane/plane.kmf"));

    // GameLevel::Get().Initialize();
    // GameLevel::Get().Deserialize("test.level");
}

void GameLayer::EventHandler(const Core::Event& event)
{
    const Core::EventType& type = event.GetType();
    if (type == Core::EventType::FrameBufferResizeEvent)
    {
        auto& e = (Core::FrameBufferResizeEvent&)event;
        //camera.SetViewportSize(e.GetWidth(), e.GetHeight());
        mScene.OnViewportResize(e.GetWidth(), e.GetHeight());
    }

    std::cout << event.ToString() << std::endl;
}

void GameLayer::OnUpdate()
{
    //camera.OnUpdate();
   
}

void GameLayer::OnRender(double dt)
{
    // RenderSystem::Instance().Render(camera);
    // GameLevel::Get().Update();

     mScene.OnUpdate();
}