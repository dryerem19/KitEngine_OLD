//
// Created by piokxix on 01.11.22.
//
#include "pch.h"
#include "Input.h"

GLFWwindow* Core::Input::m_pWindow = nullptr;

bool Core::Input::mIsInit = false;

int Core::Input::mKey = -1;
int Core::Input::mMouseButton = -1;

void Core::Input::Initialize(GLFWwindow *pWindow) {

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

void Core::Input::OnKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {

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

void Core::Input::OnMouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {

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

void Core::Input::OnCursorPositionCallback(GLFWwindow *window, double xpos, double ypos) {

    mousePosition.x = (float)xpos;
    mousePosition.y = (float)ypos;

}

void Core::Input::OnScrollCallback(GLFWwindow *window, double xoffset, double yoffset) {

    mouseScrollDelta.x = (float)xoffset;
    mouseScrollDelta.y = (float)yoffset;

}

bool Core::Input::GetKey(Core::KeyCode keyCode) {

    int key = static_cast<int>(keyCode);
    return mCurrentStateKeyboard[key];

}

bool Core::Input::GetKeyDown(Core::KeyCode keyCode) {

    int key = static_cast<int>(keyCode);
    return mCurrentStateKeyboard[key] && !mPreviousStateKeyboard[key];

}

bool Core::Input::GetKeyUp(Core::KeyCode keyCode) {

    int key = static_cast<int>(keyCode);
    return mPreviousStateKeyboard[key] && !mCurrentStateKeyboard[key];

}

bool Core::Input::GetMouseButton(Core::MouseButton mouseButton) {

    int mouse = static_cast<int>(mouseButton);
    return mCurrentStateMouse[mouse];

}

bool Core::Input::GetMouseDown(Core::MouseButton mouseButton) {

    int mouse = static_cast<int>(mouseButton);
    return mCurrentStateMouse[mouse] && !mPreviousStateMouse[mouse];

}

bool Core::Input::GetMouseUp(Core::MouseButton mouseButton) {

    int mouse = static_cast<int>(mouseButton);
    return mPreviousStateMouse[mouse] && !mCurrentStateMouse[mouse];

}

void Core::Input::SetInputMode(Core::CursorMode mode, Core::CursorState state) {

    glfwSetInputMode(m_pWindow, static_cast<int>(mode), static_cast<int>(state));

}

void Core::Input::SetCursorPos(double x, double y) {

    glfwSetCursorPos(m_pWindow, x, y);

}


