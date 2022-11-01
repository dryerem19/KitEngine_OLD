#include "Core/Window.h"
#include "Core/Application.h"

#include <iostream>

#include <Graphics/GlHelpers.h>
#include <Graphics/Renderer.h>

#include <Core/Logger.h>

using namespace KitEngine::Core;
using namespace KitEngine::Graphics;


int main(void)
{
    KitEngine::WindowProps props;
    props.Title = "KitEngine";
    props.WindowClass = "KitEngineWindowClass";
    props.Width = 800;
    props.Height = 600;

    Application& app = Application::Instance();
    app.Start(props);

//    // how opengl sampler alpha pixels
//    glEnable(GL_BLEND);
//    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
//
//    Renderer renderer;
//
//    glm::mat4 transform = glm::mat4(1.0f);
//    while (window.Exec()) {
//        window.Update();
//
//        /* Render here */
//        renderer.Clear();
//
//        transform = glm::rotate(transform, 0.02f, glm::vec3(0.0f, 0.0f, 1.0f));
//        shader.SetUniformMatrix4fv("uTransform",1, GL_FALSE,
//                                   glm::value_ptr(transform));
//
//
//        renderer.Draw(vertexArray, indexBuffer, shader);
//
//
//        window.SwapBuffers();
//    }

    return 0;
}