#pragma once
#include "Core/IController.h"
#include "UITopBarTools.h"
#include "UIViewport.h"


namespace LevelEditor
{
    class UIController : public IController
    {
    private:
        UITopBarTools* mUITopBarTools { nullptr };
        UIViewport* mUIViewport       { nullptr };
    public:
        UIController(UITopBarTools* uiTopBarTools, UIViewport* uiViewport)
            : mUITopBarTools(uiTopBarTools), mUIViewport(uiViewport) { }

        void OnNotify(KitUI* sender, const Event& event) override;
    };
}