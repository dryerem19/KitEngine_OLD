//
// Created by dryerem19 on 16.10.22.
//

#pragma once
#include "KitEnginePch.h"

namespace KitEngine
{
    class WindowProps
    {
    public:

        std::string Title;
        std::string WindowClass;
        int Width;
        int Height;

        WindowProps() = default;
        WindowProps(const std::string& title,
                    const std::string& wndClass, int width, int height);
        WindowProps(const WindowProps&) = default;

    };

    class Window
    {
    private:
        WindowProps mProps;
        GLFWwindow* m_pWindow;
    public:
        Window(const WindowProps& windowProps);
        ~Window();
        bool Initialize();
        bool Exec();
        void Update();
        void SwapBuffers();
        GLFWwindow* GetWindowPointer() const { return m_pWindow; }
    };
}