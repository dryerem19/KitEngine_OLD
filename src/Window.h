//
// Created by dryerem19 on 16.10.22.
//

#ifndef KITENGINE_WINDOW_H
#define KITENGINE_WINDOW_H
#include "GLFW/glfw3.h"

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

#endif //KITENGINE_WINDOW_H
