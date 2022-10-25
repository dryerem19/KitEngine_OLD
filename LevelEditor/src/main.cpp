#include <Window.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

#include <cassert>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <Graphics/VertexBuffer.h>
#include <Graphics/IndexBuffer.h>
#include <Graphics/Texture.h>
#include <Graphics/Shader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("res/fonts/Roboto-Bold.ttf", 14, NULL, io.Fonts->GetGlyphRangesCyrillic());
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window.GetWindowPointer(), true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // how opengl sampler alpha pixels
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

    unsigned int vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    KitEngine::Graphics::VertexBuffer vertexBuffer{vertices, 4 * 4 * sizeof(float)};

    // Атрибут 0 соответствует координатам текстуры
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    KitEngine::Graphics::IndexBuffer indexBuffer{indices, 6};

    //std::string working_directory = std::filesystem::current_path();


    KitEngine::Graphics::Shader shader("res/shaders/glsl/transform_test.glsl");

    //KitEngine::Graphics::Shader shader("res/shaders/glsl/texture.shader");

    std::string str = "dsdsd";
    shader.Enable();
    shader.SetUniform4f("uColor", 0.3, 0.8, 0.8f, 1.0f);

    KitEngine::Graphics::Texture texture("res/textures/no_texture.png");
    texture.Enable();
    shader.SetUniform1i("uTexture", 0);

    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    float incrementR = 0.09f;
    float incrementG = 0.07f;
    float incrementB = 0.02f;

    //glfwSwapInterval(1);

    glm::mat4 transform = glm::mat4(1.0f);
    while (window.Exec()) {
        window.Update();

        /* Render here */
        //glClearColor(1,1,1,1);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw only vertices
        //glDrawArrays(GL_TRIANGLES, 0, 6);


        // Send r-value color to uniform variable in shader
        shader.SetUniform4f("uColor", r, g, b, 1.0f);


        transform = glm::rotate(transform, 0.02f, glm::vec3(0.0f, 0.0f, 1.0f));

        shader.SetUniformMatrix4fv("uTransform",1, GL_FALSE, glm::value_ptr(transform));

        // Draw indexed primitive
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        if (r > 1.0f) {
            incrementR = -0.02f;
        }
        else if (r < 0.0f){
            incrementR = 0.06f;
        }
        if (g > 1.0f) {
            incrementG = -0.05f;
        }
        else if (g < 0.0f){
            incrementG = 0.02f;
        }
        if (b > 1.0f) {
            incrementB = -0.05f;
        }
        else if (b < 0.0f){
            incrementB = 0.05f;
        }


        r += incrementR;
        g += incrementG;
        b += incrementB;


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

    glDisableVertexAttribArray(0);
    glDeleteVertexArrays(1, &vao);

    return 0;
}