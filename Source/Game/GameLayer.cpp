#include "GameLayer.h"

void GameLayer::OnStart()
{
    auto pWindow = Core::Application::Instance().GetWindow().get();
    camera.SetPerspective(45.0f, pWindow->GetWidth() / pWindow->GetHeight(), 0.1f, 100.0f);
    Render::GameLevel::Get().Deserialize("test.level");
}

void GameLayer::EventHandler(const Core::Event& event)
{
    const Core::EventType& type = event.GetType();
    if (type == Core::EventType::FrameBufferResizeEvent)
    {
        auto& e = (Core::FrameBufferResizeEvent&)event;
        camera.SetPerspective(45.0f, (float)e.GetWidth() / e.GetHeight(), 0.1f, 100.0f);
    }

    std::cout << event.ToString() << std::endl;
}

void GameLayer::OnUpdate()
{
    camera.HandleInput();
}

void GameLayer::OnRender(double dt)
{
    RenderSystem::Instance().Render(camera);
}