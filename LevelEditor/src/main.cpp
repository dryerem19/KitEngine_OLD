#include <Core/Window.h>
#include <Core/Application.h>

#include "Tests/TestLayer.h"

int main()
{
    KitEngine::WindowProps props;
    props.Title = "KitEngine";
    props.WindowClass = "KitEngineWindowClass";
    props.Width = 800;
    props.Height = 600;

    using namespace KitEngine::Core;

    Application& app = Application::Instance();
    app.Initialize(props);
    app.PushLayer(new LevelEditor::Tests::TestLayer());
    app.Start();

}
