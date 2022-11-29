#pragma once
#include "KitObject.h"

namespace Render
{
    class KitComponent
    {
    public:
        KitObject mAttachedObject;
        
    protected:
        KitComponent(const KitComponent&) = default;
        KitComponent(const KitObject& attachedObject) 
            : mAttachedObject(attachedObject) { }

        virtual ~KitComponent() {};
    };
}