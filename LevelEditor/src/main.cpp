#include "Core/Window.h"

#include <iostream>

#include <Graphics/GlHelpers.h>
#include <Graphics/VertexBuffer.h>
#include <Graphics/IndexBuffer.h>
#include <Graphics/VertexArray.h>
#include <Graphics/Texture.h>
#include <Graphics/Shader.h>
#include <Graphics/Renderer.h>

#include <Core/Logger.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace KitEngine::Core;
using namespace KitEngine::Graphics;

#include "LevelEditorApplication.h"
using namespace LevelEditor;

int main(void)
{
    KitEngine::WindowProps props;
    props.Title = "KitEngine";
    props.WindowClass = "KitEngineWindowClass";
    props.Width = 800;
    props.Height = 600;

    auto app = std::make_unique<LevelEditorApplication>();
    app->Start(props);

//    // how opengl sampler alpha pixels
//    glEnable(GL_BLEND);
//    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
//
//    VertexArray vertexArray;
//    VertexBuffer vertexBuffer{vertices, 16 * sizeof(float)};
//    VertexBufferLayout layout;
//    layout.AddFloatElement(2);
//    layout.AddFloatElement(2);
//    vertexArray.AddBuffer(vertexBuffer, layout);
//
//    IndexBuffer indexBuffer{indices, 6};
//
//    KitEngine::Graphics::Shader shader("res/shaders/glsl/transform_test.glsl");
//    shader.Enable();
//    shader.SetUniform4f("uColor", 0.3, 0.8, 0.8f, 1.0f);
//
//    KitEngine::Graphics::Texture texture("res/textures/no_texture.png");
//    texture.Enable();
//    shader.SetUniform1i("uTexture", 0);
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