#include <Window.h>

#include <iostream>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

static unsigned int CompileShader(const std::string& shader, unsigned int type)
{
    // Create shader
    unsigned int id = glCreateShader(type);

    // Compile shader
    const char* source = shader.c_str();
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    // Check if error
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (GL_FALSE == result) {

        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        char* message = (char*) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "pixel")
            << "shader!" << std::endl;
        std::cout << message << std::endl;

        /* Cleanup */
        glDeleteShader(id);

        return -1;
    }

    return id;
}

static int CreateShader(const std::string& vertexShader, const std::string& pixelShader)
{
    // Compile shaders
    unsigned int idProgram      = glCreateProgram();
    unsigned int idVertexShader = CompileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int idPixelShader  = CompileShader(pixelShader,GL_FRAGMENT_SHADER);

    // Link shaders
    glAttachShader(idProgram, idVertexShader);
    glAttachShader(idProgram, idPixelShader);

    glLinkProgram(idProgram);
    glValidateProgram(idProgram);

    // Cleanup
    glDeleteShader(idVertexShader);
    glDeleteShader(idPixelShader);

    return idProgram;
}

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
    //io.Fonts->AddFontFromFileTTF("../fonts/Roboto-Bold.ttf", 14, NULL, io.Fonts->GetGlyphRangesCyrillic());
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window.GetWindowPointer(), true);
    ImGui_ImplOpenGL3_Init("#version 130");

    float pos[6] = {
            -0.5f, -0.5f,
            0.0f, 0.5f,
            0.5f, -0.5f
    };

    unsigned int buffer = 0;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), pos, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    std::string vertexShader =
            "#version 410 core\n"
            "\n"
            "layout(location = 0) in vec4 position;"
            "\n"
            "void main()\n"
            "{\n"
            "   gl_Position = position;\n"
            "}\n";

    std::string pixelShader =
            "#version 410 core\n"
            "\n"
            "layout(location = 0) out vec4 color;"
            "\n"
            "void main()\n"
            "{\n"
            "   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
            "}\n";

    unsigned int shaderId = CreateShader(vertexShader, pixelShader);
    glUseProgram(shaderId);

    while (window.Exec()) {
        window.Update();

        /* Render here */
        //glClearColor(1,1,1,1);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

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