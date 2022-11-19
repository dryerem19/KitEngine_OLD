//
// Created by dryerem19 on 16.10.22.
//
#include "Window.h"

namespace Core
{
    WindowProps::WindowProps(std::string  title, std::string wndClass, int width, int height)
    {
        this->Title = title;
        this->WindowClass = wndClass;
        this->Width = width;
        this->Height = height;
    }

    Window::Window(const WindowProps& props)
    {
        this->mWidth  = props.Width;
        this->mHeight = props.Height;
        this->mTitle  = props.Title;

        this->Init();
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();  
    }

    void Window::Init()
    {
        glfwSetErrorCallback(OnErrorCallback);

        if (!glfwInit()) 
        {
            // TODO: assert
            exit(1);
        }

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);      
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);    
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        m_pWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), nullptr, nullptr);

        if (!m_pWindow)
        {
            // TODO: assert
            glfwTerminate();
            exit(1); 
        }  

        glfwMakeContextCurrent(m_pWindow);
        glfwSetWindowUserPointer(m_pWindow, this);
        glfwSetWindowSizeCallback(m_pWindow, OnResizeCallback);       
        glfwSetFramebufferSizeCallback(m_pWindow, OnFrameBufferResizeCallback);
    }

    bool Window::Exec()
    {
        return !glfwWindowShouldClose(m_pWindow);
    }

    void Window::Update()
    {
        glfwPollEvents();    
    }

    void Window::SwapBuffers()
    {
        glfwSwapBuffers(m_pWindow);
    }

    void Window::SetWindowTitle(const std::string &title)
    {
        glfwSetWindowTitle(m_pWindow, mTitle.c_str());
        this->mTitle = title;
    }

    void Window::OnErrorCallback(int codeError, const char* descriptionError)
    {
        Log::Error("[GLFW] - [{}]: {}!", codeError, descriptionError);
    }

    void Window::OnResizeCallback(GLFWwindow* window, int width, int height)
    {
        auto& handle   = *(Window*)glfwGetWindowUserPointer(window);
        handle.mWidth  = width;
        handle.mHeight = height;

        if (handle.eventHandlerCallback)
        {
            WindowResizeEvent event(width, height);
            handle.eventHandlerCallback(event);
        }
    }

    void Window::OnFrameBufferResizeCallback(GLFWwindow* window, int width, int height)
    {
        auto& handle   = *(Window*)glfwGetWindowUserPointer(window);

        if (handle.eventHandlerCallback)
        {
            FrameBufferResizeEvent event(width, height);
            handle.eventHandlerCallback(event);
        }        
    }
}







