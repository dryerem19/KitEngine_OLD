//
// Created by dryerem19 on 16.10.22.
//

#pragma once
#include "Logger.h"
#include "Events/WindowResizeEvent.h"
#include "Events/FrameBufferResizeEvent.h"
#include "Events/WindowCloseEvent.h"

namespace Core
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
        uint32_t mWidth;
        uint32_t mHeight;
        std::string mTitle;
        GLFWwindow* m_pWindow = nullptr;
        std::function<void(Event&)> eventHandlerCallback;

        static void OnErrorCallback(int codeError, const char* descriptionError);        
        static void OnResizeCallback(GLFWwindow* window, int width, int height);
        static void OnFrameBufferResizeCallback(GLFWwindow* window, int width, int height);
        static void OnWindowCloseCallback(GLFWwindow* window);
    public:
        explicit Window(const WindowProps& windowProps);
        ~Window();
        void Init();
        bool Exec();
        void Update();
        void SwapBuffers();

        void SetWindowTitle(const std::string& title);
    
        void SetEventHandlerCallback(const std::function<void(Event&)>& fn) { eventHandlerCallback = fn; }

        inline uint32_t GetWidth() const { return mWidth; }
        inline uint32_t GetHeight() const { return mHeight; }
        inline std::string GetTitle() const { return mTitle; }
        inline GLFWwindow* GetWindowPointer() const { return m_pWindow; }
    };
}