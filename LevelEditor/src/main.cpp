#include <Window.h>

#include <iostream>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <Graphics/VertexBuffer.h>
#include <Graphics/IndexBuffer.h>
#include <Graphics/VertexArray.h>
#include <Graphics/Texture.h>
#include <Graphics/Shader.h>

#include <Core/Logger.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace KitEngine::Graphics;

int main(void)
{
    KitEngine::WindowProps props;
    props.Title = "KitEngine";
    props.WindowClass = "KitEngineWindowClass";
    props.Width = 800;
    props.Height = 600;

    KitEngine::Window window(props);
    if (!window.Initialize()) {
        return -1;
    }

    KitEngine::Core::Log::Info("Самый лучший движок в мире!!");
    KitEngine::Core::Log::Warning("Привет, {}!", "Женя");
    KitEngine::Core::Log::Critical("Хьюстон, у нас проблемы :(");

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("res/fonts/Roboto-Bold.ttf", 14, NULL,
                                 io.Fonts->GetGlyphRangesCyrillic());
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window.GetWindowPointer(), true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // how opengl sampler alpha pixels
    glEnable(GL_BLEND);
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    // Vertices
    float vertices[] = {
            // x, y, tu, tv
            -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 1.0f
    };

    // Indices
    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    VertexArray vertexArray;
    VertexBuffer vertexBuffer{vertices, 16 * sizeof(float)};
    VertexBufferLayout layout;
    layout.AddFloatElement(2);
    layout.AddFloatElement(2);
    vertexArray.AddBuffer(vertexBuffer, layout);

    IndexBuffer indexBuffer{indices, 6};

    KitEngine::Graphics::Shader shader("res/shaders/glsl/transform_test.glsl");
    shader.Enable();
    shader.SetUniform4f("uColor", 0.3, 0.8, 0.8f, 1.0f);

    KitEngine::Graphics::Texture texture("res/textures/no_texture.png");
    texture.Enable();
    shader.SetUniform1i("uTexture", 0);

    glm::mat4 transform = glm::mat4(1.0f);
    while (window.Exec()) {
        window.Update();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        transform = glm::rotate(transform, 0.02f, glm::vec3(0.0f, 0.0f, 1.0f));
        shader.SetUniformMatrix4fv("uTransform",1, GL_FALSE,
                                   glm::value_ptr(transform));
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Show demo window
        ImGui::Begin("Window");
        ImGui::Text("Как дела ?");
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.SwapBuffers();
    }

    return 0;
}