#include <Window.h>

#include <iostream>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

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

using namespace KitEngine::Graphics;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, int key, int action, int mode);
void mouse_movement(GLFWwindow* window, double xpos, double ypos);
void do_movement();

glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
GLfloat yaw   = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
GLfloat pitch =   0.0f;
GLfloat lastX =  800  / 2.0;
GLfloat lastY =  600 / 2.0;
bool keys[1024];

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


    glfwSetKeyCallback(window.GetWindowPointer(), key_callback);
    glfwSetMouseButtonCallback(window.GetWindowPointer(), mouse_callback);
    glfwSetCursorPosCallback(window.GetWindowPointer(), mouse_movement);

    glfwSetInputMode(window.GetWindowPointer(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    KitEngine::Core::Log::Info("Самый лучший движок в мире!!");
    KitEngine::Core::Log::Warning("Привет, {} dsdsdsds {}!", "Женя", "Вася");
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

    Renderer renderer;

    glm::mat4 transform = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    while (window.Exec()) {
        window.Update();
        do_movement();


        /* Render here */
        renderer.Clear();

        // Camera
        view = glm::lookAt(cameraPos,cameraPos + cameraFront, cameraUp);
        projection = glm::perspective(45.0f, (GLfloat)props.Width / (GLfloat)props.Height, 0.1f, 100.0f);
        shader.SetUniformMatrix4fv("uView", 1, GL_FALSE, glm::value_ptr(view));
        shader.SetUniformMatrix4fv("uProjection", 1, GL_FALSE, glm::value_ptr(projection));

        transform = glm::rotate(transform, 0.02f, glm::vec3(0.0f, 0.0f, 1.0f));
        shader.SetUniformMatrix4fv("uTransform",1, GL_FALSE,
                                   glm::value_ptr(transform));


        renderer.Draw(vertexArray, indexBuffer, shader);

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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

void mouse_callback(GLFWwindow* window, int key, int action, int mode)
{

    if(action == GLFW_PRESS)
    {
        keys[key] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        keys[key] = false;
    }

}

void mouse_movement(GLFWwindow* window, double xpos, double ypos)
{
    if(keys[GLFW_MOUSE_BUTTON_LEFT])
    {


        GLfloat xoffset = xpos - lastX;
        GLfloat yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;


        GLfloat sensitivity = 0.05;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw   += xoffset;
        pitch += yoffset;

        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(front);

    }


}

void do_movement()
{
    // Camera controls
    GLfloat cameraSpeed = 0.30f;
    if (keys[GLFW_KEY_W])
    {
        cameraPos += cameraSpeed * cameraFront;

    }
    if (keys[GLFW_KEY_S])
    {
        cameraPos -= cameraSpeed * cameraFront;

    }
    if (keys[GLFW_KEY_A])
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    }
    if (keys[GLFW_KEY_D])
    {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }

}