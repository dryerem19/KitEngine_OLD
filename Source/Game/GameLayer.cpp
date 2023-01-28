#include "GameLayer.h"

#include "ResourceManager.h"

void GameLayer::OnStart()
{
    auto pWindow = Core::Application::Instance().GetWindow().get();
    camera.SetViewportSize(pWindow->GetWidth(), pWindow->GetHeight());

    // Entity* pGround = GameLevel::Get().CreateEntity();
    // pGround->SetModel(Core::ResourceManager::Instance().GetModel("data/plane/plane.kmf"));

    GameLevel::Get().Deserialize("test.level");
}

void GameLayer::EventHandler(const Core::Event& event)
{
    const Core::EventType& type = event.GetType();
    if (type == Core::EventType::FrameBufferResizeEvent)
    {
        auto& e = (Core::FrameBufferResizeEvent&)event;
        camera.SetViewportSize(e.GetWidth(), e.GetHeight());
    }

    std::cout << event.ToString() << std::endl;
}

void GameLayer::OnUpdate()
{
    camera.OnUpdate();
    GameLevel::Get().Update();
}

void GameLayer::OnRender(double dt)
{
    RenderSystem::Instance().Render(camera);
}