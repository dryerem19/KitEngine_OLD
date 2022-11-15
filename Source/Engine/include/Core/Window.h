//
// Created by dryerem19 on 16.10.22.
//

#pragma once
#include "core.h"
#include "Core/Logger.h"

namespace KitEngine
{
    class WindowProps
    {
    public:

        std::string Title;
        std::string WindowClass;
        int Width{};
        int Height{};

        WindowProps() = default;
        WindowProps(std::string  title,
                    std::string  wndClass, int width, int height);
        WindowProps(const WindowProps&) = default;

    };

    class Window
    {
    private:
        WindowProps mProps;
        GLFWwindow* m_pWindow = nullptr;
        static void OnErrorHandling(int codeError, const char* descriptionError);

    public:
        explicit Window(const WindowProps& windowProps);
        ~Window();
        bool Initialize();
        bool Exec();
        void Update();
        void SwapBuffers();

        void SetWindowTitle(const std::string& title) const;
        const inline WindowProps& GetProps() { return mProps; }
        [[nodiscard]] inline GLFWwindow* GetWindowPointer() const { return m_pWindow; }
    };

    void OnDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, 
                    const char *message, 
                    const void *userParam);
}