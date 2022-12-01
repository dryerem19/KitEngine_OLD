#include "pch.h"
#include "SceneManager.h"

namespace Render
{
    World& World::Get()
    {
        static World instance;
        return instance;
    }
}