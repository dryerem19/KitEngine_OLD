#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <imgui_internal.h>
#include <imgui_stdlib.h>
#include <ImGuizmo.h>

#include <ImGuiFileDialog.h>

#include "3rdparty/IconsFontAwesome6.h"

#include "ImGuiLayer.h"

#include <Renderer.h>
#include <KitTransform.h>


namespace LevelEditor
{
    class IController;

    class KitUI
    {
    protected:
        IController* mController { nullptr };
        KitUI(IController* controller = nullptr) : mController(controller) { }
    public:
        void SetController(IController* controller) { mController = controller; }
        virtual void Draw() = 0;
    };
}