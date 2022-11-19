#include <Window.h>
#include <Application.h>

#include "Tests/TestLayer.h"
#include "ImGuiLayer.h"


int main(void)
{

    Core::WindowProps props;
    props.Title = "KitEngine";
    props.Width = 800;
    props.Height = 600;

    Core::Application& app = Core::Application::Instance();
    app.Initialize(props);
    app.PushOverlayLayer(new LevelEditor::ImGuiLayer());
    app.PushLayer(new LevelEditor::Tests::TestLayer());
    app.Start();
    
}
