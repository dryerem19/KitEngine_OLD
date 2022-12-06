#pragma once
#include "Event.h"
#include <sstream>

namespace LevelEditor
{
    enum class GizmoOperation
    {
        NONE             = 0,
        TRANSLATE_X      = (1u << 0),
        TRANSLATE_Y      = (1u << 1),
        TRANSLATE_Z      = (1u << 2),
        ROTATE_X         = (1u << 3),
        ROTATE_Y         = (1u << 4),
        ROTATE_Z         = (1u << 5),
        ROTATE_SCREEN    = (1u << 6),
        SCALE_X          = (1u << 7),
        SCALE_Y          = (1u << 8),
        SCALE_Z          = (1u << 9),
        BOUNDS           = (1u << 10),
        TRANSLATE = TRANSLATE_X | TRANSLATE_Y | TRANSLATE_Z,
        ROTATE = ROTATE_X | ROTATE_Y | ROTATE_Z | ROTATE_SCREEN,
        SCALE = SCALE_X | SCALE_Y | SCALE_Z
    };

    class SelectGizmoEvent : public Event
    {
    public:
        SelectGizmoEvent(GizmoOperation operation)
            : Event("SelectGizmoEvent", EventType::SelectGizmo), mOperation(operation) { }

        GizmoOperation GetOperation() const { return mOperation; }
        std::string ToString() const override
        {
            std::stringstream format;
            format << "[" << mName << "] : " << "{ SelectOperation: ";

            if(mOperation == GizmoOperation::NONE)
                format << "None";

            else if(mOperation == GizmoOperation::TRANSLATE) 
                format << "Translate";

            else if(mOperation == GizmoOperation::ROTATE)
                format << "Rotate";

            else if(mOperation == GizmoOperation::SCALE)
                format << "Scale";
            format << " }";

            return format.str();
        }
    private:
        GizmoOperation mOperation;
    };
}