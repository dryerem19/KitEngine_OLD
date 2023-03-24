//
// Created by piokxix on 01.11.22.
//
#include "pch.h"
#include "Input.h"

GLFWwindow* Input::m_pWindow = nullptr;

bool Input::mIsInit = false;

int Input::mKey = -1;
int Input::mMouseButton = -1;

void Input::Initialize(GLFWwindow *pWindow) {

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

void Input::OnKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {

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

void Input::OnMouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {

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

void Input::OnCursorPositionCallback(GLFWwindow *window, double xpos, double ypos) {
    
    mouseDelta.x = mousePosition.x - xpos;
    mouseDelta.y = mousePosition.y - ypos;

    mousePosition.x = (float)xpos;
    mousePosition.y = (float)ypos;

}

void Input::OnScrollCallback(GLFWwindow *window, double xoffset, double yoffset) {

    mouseScrollDelta.x = (float)xoffset;
    mouseScrollDelta.y = (float)yoffset;

}

bool Input::GetKey(KeyCode keyCode) {

    int key = static_cast<int>(keyCode);
    return mCurrentStateKeyboard[key];

}

bool Input::IsKeyDown(KeyCode keyCode) {

    int key = static_cast<int>(keyCode);
    return mCurrentStateKeyboard[key] && !mPreviousStateKeyboard[key];

}

bool Input::GetKeyUp(KeyCode keyCode) {

    int key = static_cast<int>(keyCode);
    return mPreviousStateKeyboard[key] && !mCurrentStateKeyboard[key];

}

bool Input::GetMouseButton(MouseButton mouseButton) {

    int mouse = static_cast<int>(mouseButton);
    return mCurrentStateMouse[mouse];

}

bool Input::GetMouseDown(MouseButton mouseButton) {

    int mouse = static_cast<int>(mouseButton);
    return mCurrentStateMouse[mouse] && !mPreviousStateMouse[mouse];

}

bool Input::GetMouseUp(MouseButton mouseButton) {

    int mouse = static_cast<int>(mouseButton);
    return mPreviousStateMouse[mouse] && !mCurrentStateMouse[mouse];

}

void Input::SetInputMode(CursorMode mode, CursorState state) {

    glfwSetInputMode(m_pWindow, static_cast<int>(mode), static_cast<int>(state));

}

void Input::SetCursorPos(double x, double y) {

    glfwSetCursorPos(m_pWindow, x, y);

}

float Input::GetMouseDeltaX()
{
    static double lastMousePosX = 0.0;

    double currentMousePosX, deltaX;
    glfwGetCursorPos(m_pWindow, &currentMousePosX, nullptr);
    deltaX = currentMousePosX - lastMousePosX;
    lastMousePosX = currentMousePosX;

    return static_cast<float>(deltaX);
}

float Input::GetMouseDeltaY()
{
    static double lastMousePosY = 0.0;

    double currentMousePosY, deltaY;
    glfwGetCursorPos(m_pWindow, nullptr, &currentMousePosY);
    deltaY = currentMousePosY - lastMousePosY;
    lastMousePosY = currentMousePosY;

    return static_cast<float>(deltaY);
}
