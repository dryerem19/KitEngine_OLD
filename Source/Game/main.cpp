//
// Created by dryerem19 on 11/7/22.
//
#include "Application.h"
#include "Window.h"

#include "GameLayer.h"

int main()
{
    Core::WindowProps props;
    props.Title = "Game";
    props.Width = 800;
    props.Height = 600;

    Core::Application& app = Core::Application::Instance();
    app.Initialize(props);
    app.PushLayer(new GameLayer());
    app.Start();
}