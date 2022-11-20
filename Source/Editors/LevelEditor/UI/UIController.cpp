#include "UIController.h"

namespace LevelEditor
{
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