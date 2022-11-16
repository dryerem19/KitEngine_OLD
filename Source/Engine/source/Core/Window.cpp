//
// Created by dryerem19 on 16.10.22.
//
#include "Core/Window.h"

KitEngine::WindowProps::WindowProps(std::string title, std::string  wndClass, int width, int height)
 : Title(std::move(title)), WindowClass(std::move(wndClass)), Width(width), Height(height) {
}


void KitEngine::Window::OnErrorHandling(const int codeError, const char* descriptionError) {
    Core::Log::Error("[GLFW] - [{}]: {}!", codeError, descriptionError);
}

KitEngine::Window::Window(const KitEngine::WindowProps &windowProps)
    : mProps(windowProps) {
}

KitEngine::Window::~Window() {

    /* Cleanup */
    if (m_pWindow) {
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
    }

}

void KitEngine::OnDebugOutput(GLenum source, 
                            GLenum type, 
                            unsigned int id, 
                            GLenum severity, 
                            GLsizei length, 
                            const char *message, 
                            const void *userParam)
{
    // ignore non-significant error/warning codes
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " <<  message << std::endl;

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
    } std::cout << std::endl;

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break; 
        case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
    } std::cout << std::endl;
    
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
    } std::cout << std::endl;
    std::cout << std::endl;
}

bool KitEngine::Window::Initialize() {

    glfwSetErrorCallback(OnErrorHandling);

    /* Initialize glfw */
    if (glfwInit()) {

        // Setup context
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);  
        

        /* Create the window */
        m_pWindow = glfwCreateWindow(mProps.Width,
                                     mProps.Height,
                                     mProps.Title.c_str(),
                                     nullptr, nullptr);


        if (!m_pWindow) {
            glfwTerminate();
            return false;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(m_pWindow);

        // ОТключить ограничение кдаров
        //glfwSwapInterval(0);

        /* Initialize glew */
        if (glewInit() != GLEW_OK) {
            return false;
        }

        int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
        {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
            glDebugMessageCallback(OnDebugOutput, nullptr);  
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);         
        }

        return true;
    }

    return false;

}

bool KitEngine::Window::Exec() {
    return !glfwWindowShouldClose(m_pWindow);
}

void KitEngine::Window::Update() {
    /* Poll for and process events */
    glfwPollEvents();

    int display_w, display_h;
    glfwGetFramebufferSize(m_pWindow, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
}

void KitEngine::Window::SwapBuffers() {
    /* Swap front and back buffers */
    glfwSwapBuffers(m_pWindow);
}

void KitEngine::Window::SetWindowTitle(const std::string &title) const {

    glfwSetWindowTitle(m_pWindow, title.c_str());

}







