#pragma once
#include "KitUI.h"

#include <string>
namespace UI
{
    class UIFileDialog : public KitUI
    {
    public:
        UIFileDialog() = default;
        void Draw() override = 0;
        static std::string OpenFile(const std::string& filters, bool* isCheckFileDialog);
    };
}