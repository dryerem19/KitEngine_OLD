#pragma once
#include "BaseEntity.h"

namespace Render
{
    class World : public Core::BaseEntity
    {
    private:
        World() = default;
        World(const World&) = delete;
        World& operator=(World&) = delete;
        ~World() = default;
    public:
        static World& Get();
    };
}