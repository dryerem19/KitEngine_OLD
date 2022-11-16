#pragma once
#include "KitTransform.h"

namespace Render
{
    class KitObject
    {
    public:
        KitTransform mTransform;
        std::string mName;

        KitObject() = default;
        KitObject(const std::string& name)
            : mName(name) { }

        void SetName(const std::string& name) { mName = name; }
        std::string GetName() const { return mName; }
    };
}