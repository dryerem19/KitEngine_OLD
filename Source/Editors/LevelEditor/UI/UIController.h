#pragma once
#include "Core/IController.h"
#include "UITopBarTools.h"
#include "UIViewport.h"

namespace LevelEditor
{
    class UIController : public IController
    {
    private:
        UITopBarTools* mUITopBarTools;
        UIViewport* mUIViewport;
    public:
        UIController(UITopBarTools* uiTopBarTools, UIViewport* uiViewport);
        void OnNotify(KitUI* sender, const Event& event) override;
    };
}