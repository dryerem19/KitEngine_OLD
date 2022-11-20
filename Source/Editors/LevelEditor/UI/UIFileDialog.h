#pragma once
#include "Core/KitUI.h"
#include <string>

namespace LevelEditor
{
    class UIFileDialog : public KitUI
    {
    public:
        UIFileDialog() = default;
        UIFileDialog(IController* controller) : KitUI(controller) { }
        void Draw() override = 0;
        static std::string OpenFile(const std::string& filters, bool* isCheckFileDialog);
    };
}