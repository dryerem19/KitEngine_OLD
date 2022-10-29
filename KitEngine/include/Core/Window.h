//
// Created by dryerem19 on 16.10.22.
//

#pragma once
#include "KitEnginePch.h"
#include "Core/Logger.h"

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
        static void OnErrorHandling(int codeError, const char* descriptionError);

    public:
        Window(const WindowProps& windowProps);
        ~Window();
        bool Initialize();
        bool Exec();
        void Update();
        void SwapBuffers();

        void SetWindowTitle(const std::string& title) const;
        const inline WindowProps& GetProps() { return mProps; }
        GLFWwindow* GetWindowPointer() const { return m_pWindow; }
    };
}