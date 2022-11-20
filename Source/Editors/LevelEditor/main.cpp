#include "UI/UILayer.h"
#include "ImGuiLayer.h"
#include "UI/KitUI.h"

int main(void)
{
    Core::WindowProps props;
    props.Title = "KitEngine";
    props.Width = 800;
    props.Height = 600;

    Core::Application& app = Core::Application::Instance();
    app.Initialize(props);
    app.PushOverlayLayer(new UI::ImGuiLayer());
    app.PushLayer(new UI::UILayer());
    app.Start();
}
