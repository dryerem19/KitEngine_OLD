#include "UIController.h"

namespace LevelEditor
{
    UIController::UIController(UITopBarTools* uiTopBarTools, UIViewport* uiViewport)
        : mUITopBarTools(uiTopBarTools), mUIViewport(uiViewport)
    {
        mUITopBarTools->SetController(this);
        mUIViewport->SetController(this);
    }

    void UIController::OnNotify(KitUI* sender, const Event& event)
    {
        EventType type = event.GetType();
        switch (type)
        {
            case EventType::SelectGizmo:
            {
                const SelectGizmoEvent& e = (SelectGizmoEvent&)event;
                mUIViewport->SetGizmoOperation(e.GetOperation());
            }
            break;
            
            default:
                break;
        }

        std::cout << event.ToString() << std::endl;
    }
}