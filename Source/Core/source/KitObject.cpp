#include "KitObject.h"
#include "GameLevel.h"

void KitObject::SetVisualPath(const std::string &path)
{
    if (!std::filesystem::exists(path))
        return;
}

bool KitObject::IsPhysicObject() const
{
    // if (m_pPhysicObject)
    //     return true;

    return false;
}

void KitObject::OnPicked()
{
    GameLevel::Get().SetSelectedObject(this);    
}
