#include "UI/UILayer.h"
#include "Core/ImGuiLayer.h"
#include "Core/KitUI.h"

int main(void)
{
    Core::WindowProps props;
    props.Title = "KitEngine";
    props.Width = 800;
    props.Height = 600;

    Core::Application& app = Core::Application::Instance();
    app.Initialize(props);
    app.PushOverlayLayer(new LevelEditor::ImGuiLayer());
    app.PushLayer(new LevelEditor::UILayer());
    app.Start();
}
