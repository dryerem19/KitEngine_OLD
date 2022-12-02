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
    private:
        Core::BaseEntity* m_pSelectedEntity { nullptr };
    public:
        static World& Get();

        inline void SetSelectedEntity(Core::BaseEntity* pSelectedEntity)
        {
            m_pSelectedEntity = pSelectedEntity;
        }

        inline Core::BaseEntity* GetSelectedEntity() const
        {
            return m_pSelectedEntity;
        }
    };
}