//
// Created by piokxix on 01.11.22.
//
#include <Core/Input.h>

glm::vec2 KitEngine::Core::Input::mousePosition = glm::vec2(0,0);
glm::vec2 KitEngine::Core::Input::mouseScrollDelta = glm::vec2(0,0);


GLFWwindow* KitEngine::Core::Input::m_pWindow = nullptr;

bool KitEngine::Core::Input::mIsInit = false;

int KitEngine::Core::Input::mKey = -1;
int KitEngine::Core::Input::mMouseButton = -1;

int KitEngine::Core::Input::mKeyAction = GLFW_RELEASE;
int KitEngine::Core::Input::mMouseAction = GLFW_RELEASE;

void KitEngine::Core::Input::Initialize(GLFWwindow *pWindow) {

    if(!mIsInit)
    {
        m_pWindow = pWindow;
        glfwSetKeyCallback              (pWindow, OnKeyCallback);
        glfwSetMouseButtonCallback      (pWindow, OnMouseButtonCallback);
        glfwSetCursorPosCallback        (pWindow, OnCursorPositionCallback);
        glfwSetScrollCallback           (pWindow, OnScrollCallback);
        mIsInit = true;
    }

}

void KitEngine::Core::Input::OnKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {

    mKey = key;
    mKeyAction = action;

}

void KitEngine::Core::Input::OnMouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {

    mMouseButton = button;
    mMouseAction = action;

}

void KitEngine::Core::Input::OnCursorPositionCallback(GLFWwindow *window, double xpos, double ypos) {

    mousePosition.x = (float)xpos;
    mousePosition.y = (float)ypos;

}

void KitEngine::Core::Input::OnScrollCallback(GLFWwindow *window, double xoffset, double yoffset) {

    mouseScrollDelta.x = (float)xoffset;
    mouseScrollDelta.y = (float)yoffset;

}

bool KitEngine::Core::Input::GetKey(KitEngine::Core::KeyCode keyCode) {

    return static_cast<KeyCode>(mKey) == keyCode;

}

bool KitEngine::Core::Input::GetKeyDown(KitEngine::Core::KeyCode keyCode) {

    return mKeyAction == GLFW_PRESS && static_cast<KeyCode>(mKey) == keyCode;

}

bool KitEngine::Core::Input::GetKeyUp(KitEngine::Core::KeyCode keyCode) {

    return mKeyAction == GLFW_RELEASE && static_cast<KeyCode>(mKey) == keyCode;

}

bool KitEngine::Core::Input::GetMouseButton(KitEngine::Core::MouseButton mouseButton) {

    return static_cast<MouseButton>(mMouseButton) == mouseButton;

}

bool KitEngine::Core::Input::GetMouseDown(KitEngine::Core::MouseButton mouseButton) {

    return mMouseAction == GLFW_PRESS && static_cast<MouseButton>(mMouseButton) == mouseButton;

}

bool KitEngine::Core::Input::GetMouseUp(KitEngine::Core::MouseButton mouseButton) {

    return mMouseAction == GLFW_RELEASE && static_cast<MouseButton>(mMouseButton) == mouseButton;

}

void KitEngine::Core::Input::SetInputMode(KitEngine::Core::CursorMode mode, KitEngine::Core::CursorState state) {

    glfwSetInputMode(m_pWindow, static_cast<int>(mode), static_cast<int>(state));

}

void KitEngine::Core::Input::SetCursorPos(glm::vec2 pos) {

    glfwSetCursorPos(m_pWindow, pos.x, pos.y);

}


