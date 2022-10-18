//
// Created by dryerem19 on 16.10.22.
//
#include "Window.h"

KitEngine::WindowProps::WindowProps(const std::string &title, const std::string& wndClass, int width, int height)
 : Title(title), WindowClass(wndClass), Width(width), Height(height) {
}

KitEngine::Window::Window(const KitEngine::WindowProps &windowProps)
    : mProps(windowProps) {
}

bool KitEngine::Window::Initialize() {

    /* Initialize glfw */
    if (glfwInit()) {

        /* Create the window */
        m_pWindow = glfwCreateWindow(mProps.Width,
                                     mProps.Height,
                                     mProps.Title.c_str(),
                                     nullptr, nullptr);

        if (!m_pWindow)
        {
            glfwTerminate();
            return false;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(m_pWindow);

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

KitEngine::Window::~Window() {
    /* Cleanup */
    if (m_pWindow) {
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
    }
}

