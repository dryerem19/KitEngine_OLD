//
// Created by piokxix on 01.11.22.
//

#ifndef KITENGINE_INPUT_H
#define KITENGINE_INPUT_H

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace KitEngine::Core
{
    enum class KeyCode
    {
        Space           = GLFW_KEY_SPACE,
        BackQuote       = GLFW_KEY_APOSTROPHE,
        Comma           = GLFW_KEY_COMMA,
        Minus           = GLFW_KEY_MINUS,
        Dot             = GLFW_KEY_PERIOD,
        Slash           = GLFW_KEY_SLASH,
        KeyPad0         = GLFW_KEY_0,
        KeyPad1         = GLFW_KEY_1,
        KeyPad2         = GLFW_KEY_2,
        KeyPad3         = GLFW_KEY_3,
        KeyPad4         = GLFW_KEY_4,
        KeyPad5         = GLFW_KEY_5,
        KeyPad6         = GLFW_KEY_6,
        KeyPad7         = GLFW_KEY_7,
        KeyPad8         = GLFW_KEY_8,
        KeyPad9         = GLFW_KEY_9,
        Semicolon       = GLFW_KEY_SEMICOLON,
        Equal           = GLFW_KEY_EQUAL,
        A               = GLFW_KEY_A,
        B               = GLFW_KEY_B,
        C               = GLFW_KEY_C,
        D               = GLFW_KEY_D,
        E               = GLFW_KEY_E,
        F               = GLFW_KEY_F,
        G               = GLFW_KEY_G,
        H               = GLFW_KEY_H,
        I               = GLFW_KEY_I,
        J               = GLFW_KEY_J,
        K               = GLFW_KEY_K,
        L               = GLFW_KEY_L,
        M               = GLFW_KEY_M,
        N               = GLFW_KEY_N,
        O               = GLFW_KEY_O,
        P               = GLFW_KEY_P,
        Q               = GLFW_KEY_Q,
        R               = GLFW_KEY_R,
        S               = GLFW_KEY_S,
        T               = GLFW_KEY_T,
        U               = GLFW_KEY_U,
        V               = GLFW_KEY_V,
        W               = GLFW_KEY_W,
        X               = GLFW_KEY_X,
        Y               = GLFW_KEY_Y,
        Z               = GLFW_KEY_Z,
        LeftBracket     = GLFW_KEY_LEFT_BRACKET,
        BackSlash       = GLFW_KEY_BACKSLASH,
        RightBracket    = GLFW_KEY_RIGHT_BRACKET,
        Escape          = GLFW_KEY_ESCAPE,
        Enter           = GLFW_KEY_ENTER,
        Tab             = GLFW_KEY_TAB,
        BackSpace       = GLFW_KEY_BACKSPACE,
        Insert          = GLFW_KEY_INSERT,
        Delete          = GLFW_KEY_DELETE,
        RightArrow      = GLFW_KEY_RIGHT,
        LeftArrow       = GLFW_KEY_LEFT,
        DownArrow       = GLFW_KEY_DOWN,
        UpArrow         = GLFW_KEY_UP,
        PageUp          = GLFW_KEY_PAGE_UP,
        PageDown        = GLFW_KEY_PAGE_DOWN,
        Home            = GLFW_KEY_HOME,
        End             = GLFW_KEY_END,
        CapsLock        = GLFW_KEY_CAPS_LOCK,
        ScrollLock      = GLFW_KEY_SCROLL_LOCK,
        NumLock         = GLFW_KEY_NUM_LOCK,
        PrintScreen     = GLFW_KEY_PRINT_SCREEN,
        Pause           = GLFW_KEY_PAUSE,
        F1              = GLFW_KEY_F1,
        F2              = GLFW_KEY_F2,
        F3              = GLFW_KEY_F3,
        F4              = GLFW_KEY_F4,
        F5              = GLFW_KEY_F5,
        F6              = GLFW_KEY_F6,
        F7              = GLFW_KEY_F7,
        F8              = GLFW_KEY_F8,
        F9              = GLFW_KEY_F9,
        F10             = GLFW_KEY_F10,
        F11             = GLFW_KEY_F11,
        F12             = GLFW_KEY_F12,
        F13             = GLFW_KEY_F13,
        F14             = GLFW_KEY_F14,
        F15             = GLFW_KEY_F15,
        F16             = GLFW_KEY_F16,
        F17             = GLFW_KEY_F17,
        F18             = GLFW_KEY_F18,
        F19             = GLFW_KEY_F19,
        F20             = GLFW_KEY_F20,
        F21             = GLFW_KEY_F21,
        F22             = GLFW_KEY_F22,
        F23             = GLFW_KEY_F23,
        F24             = GLFW_KEY_F24,
        F25             = GLFW_KEY_F25,
        Numlock0        = GLFW_KEY_KP_0,
        Numlock1        = GLFW_KEY_KP_1,
        Numlock2        = GLFW_KEY_KP_2,
        Numlock3        = GLFW_KEY_KP_3,
        Numlock4        = GLFW_KEY_KP_4,
        Numlock5        = GLFW_KEY_KP_5,
        Numlock6        = GLFW_KEY_KP_6,
        Numlock7        = GLFW_KEY_KP_7,
        Numlock8        = GLFW_KEY_KP_8,
        Numlock9        = GLFW_KEY_KP_9,
        NumlockDecimal  = GLFW_KEY_KP_DECIMAL,
        NumlockDivide   = GLFW_KEY_KP_DIVIDE,
        NumlockMultiply = GLFW_KEY_KP_MULTIPLY,
        NumlockSubtract = GLFW_KEY_KP_SUBTRACT,
        NumlockAdd      = GLFW_KEY_KP_ADD,
        NumlockEnter    = GLFW_KEY_KP_ENTER,
        NumlockEqual    = GLFW_KEY_KP_EQUAL,
        LeftShift       = GLFW_KEY_LEFT_SHIFT,
        LeftCtrl        = GLFW_KEY_LEFT_CONTROL,
        LeftAlt         = GLFW_KEY_LEFT_ALT,
        LeftSuper       = GLFW_KEY_LEFT_SUPER,
        RightShift      = GLFW_KEY_RIGHT_SHIFT,
        RightCtrl       = GLFW_KEY_RIGHT_CONTROL,
        RightAlt        = GLFW_KEY_RIGHT_ALT,
        RightSuper      = GLFW_KEY_RIGHT_SUPER,
        Menu            = GLFW_KEY_MENU
    };

    enum class MouseButton
    {
        MouseButtonLeft     = GLFW_MOUSE_BUTTON_1,
        MouseButtonRight    = GLFW_MOUSE_BUTTON_2,
        MouseButtonMiddle   = GLFW_MOUSE_BUTTON_3,
        MouseButton3        = GLFW_MOUSE_BUTTON_4,
        MouseButton4        = GLFW_MOUSE_BUTTON_5,
        MouseButton5        = GLFW_MOUSE_BUTTON_6,
        MouseButton6        = GLFW_MOUSE_BUTTON_7,
        MouseButton7        = GLFW_MOUSE_BUTTON_8
    };
    enum class CursorMode
    {
        Cursor              = GLFW_CURSOR
    };
    enum class CursorState
    {
        CursorNormal        = GLFW_CURSOR_NORMAL,
        CursorHidden        = GLFW_CURSOR_HIDDEN,
        CursorDisabled      = GLFW_CURSOR_DISABLED
    };

    class Input
    {
    public:
        static glm::vec2 mousePosition;
        static glm::vec2 mouseScrollDelta;

        static void Initialize(GLFWwindow* pWindow);
        static bool GetKey(KeyCode keyCode);
        static bool GetKeyDown(KeyCode keyCode);
        static bool GetKeyUp(KeyCode keyCode);
        static bool GetMouseButton(MouseButton mouseButton);
        static bool GetMouseDown(MouseButton mouseButton);
        static bool GetMouseUp(MouseButton mouseButton);
        static void SetInputMode(CursorMode mode, CursorState state);
        static void SetCursorPos(glm::vec2 pos);


    private:
        Input() = default;
        ~Input() = default;

        static GLFWwindow* m_pWindow;

        static bool mIsInit;

        static int mKey;
        static int mMouseButton;

        static int mKeyAction;
        static int mMouseAction;

        static void OnKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void OnMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void OnCursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
        static void OnScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    };
}




#endif //KITENGINE_INPUT_H
