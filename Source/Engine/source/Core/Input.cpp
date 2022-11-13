//
// Created by piokxix on 01.11.22.
//
#include <Core/Input.h>

//glm::vec2 KitEngine::Core::Input::mousePosition = glm::vec2(0,0);
//glm::vec2 KitEngine::Core::Input::mouseScrollDelta = glm::vec2(0,0);


GLFWwindow* KitEngine::Core::Input::m_pWindow = nullptr;

bool KitEngine::Core::Input::mIsInit = false;

int KitEngine::Core::Input::mKey = -1;
int KitEngine::Core::Input::mMouseButton = -1;

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

    memcpy(mPreviousStateKeyboard, mCurrentStateKeyboard, 1024);

    if(action == GLFW_PRESS)
    {
        mCurrentStateKeyboard[key] = true;
    }
    else if(action == GLFW_RELEASE)
    {
        mCurrentStateKeyboard[key] = false;
    }

}

void KitEngine::Core::Input::OnMouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {

    memcpy(mPreviousStateMouse, mCurrentStateMouse, 8);

    if(action == GLFW_PRESS)
    {
        mCurrentStateMouse[button] = true;
    }
    else if(action == GLFW_RELEASE)
    {
        mCurrentStateMouse[button] = false;
    }

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

    int key = static_cast<int>(keyCode);
    return mCurrentStateKeyboard[key];

}

bool KitEngine::Core::Input::GetKeyDown(KitEngine::Core::KeyCode keyCode) {

    int key = static_cast<int>(keyCode);
    return mCurrentStateKeyboard[key] && !mPreviousStateKeyboard[key];

}

bool KitEngine::Core::Input::GetKeyUp(KitEngine::Core::KeyCode keyCode) {

    int key = static_cast<int>(keyCode);
    return mPreviousStateKeyboard[key] && !mCurrentStateKeyboard[key];

}

bool KitEngine::Core::Input::GetMouseButton(KitEngine::Core::MouseButton mouseButton) {

    int mouse = static_cast<int>(mouseButton);
    return mCurrentStateMouse[mouse];

}

bool KitEngine::Core::Input::GetMouseDown(KitEngine::Core::MouseButton mouseButton) {

    int mouse = static_cast<int>(mouseButton);
    return mCurrentStateMouse[mouse] && !mPreviousStateMouse[mouse];

}

bool KitEngine::Core::Input::GetMouseUp(KitEngine::Core::MouseButton mouseButton) {

    int mouse = static_cast<int>(mouseButton);
    return mPreviousStateMouse[mouse] && !mCurrentStateMouse[mouse];

}

void KitEngine::Core::Input::SetInputMode(KitEngine::Core::CursorMode mode, KitEngine::Core::CursorState state) {

    glfwSetInputMode(m_pWindow, static_cast<int>(mode), static_cast<int>(state));

}

void KitEngine::Core::Input::SetCursorPos(glm::vec2 pos) {

    glfwSetCursorPos(m_pWindow, pos.x, pos.y);

}


