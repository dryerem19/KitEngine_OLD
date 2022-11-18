//
// Created by dryerem19 on 16.10.22.
//

#pragma once
#include "core.h"
#include "Logger.h"

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

        static void OnErrorCallback(int codeError, const char* descriptionError);        

        void Init();

    public:
        explicit Window(const WindowProps& windowProps);
        ~Window();
        bool Exec();
        void Update();
        void SwapBuffers();

        void SetWindowTitle(const std::string& title);

        __forceinline uint32_t GetWidth() const { return mWidth; }
        __forceinline uint32_t GetHeight() const { return mHeight; }
        __forceinline std::string GetTitle() const { return mTitle; }
        __forceinline GLFWwindow* GetWindowPointer() const { return m_pWindow; }
    };
}