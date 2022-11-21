#pragma once
#include "Events/Event.h"
#include "KitUI.h"

namespace LevelEditor
{
    class KitUI;

    class IController
    {
    public:
        virtual void OnNotify(KitUI* sender, const Event& event) = 0;
        virtual ~IController() = default;
    };
}