#include "pch.h"
#include "BaseEntity.h"

namespace Core
{
    BaseEntity::BaseEntity(const std::string& name /* = Root */)
    {
        mName = name;
    }

    void BaseEntity::LinkChild(BaseEntity* pChild)
    {
        this->UnlinkParent(pChild);
        mChildren.emplace_back(pChild);
        pChild->SetParent(this);
    }

    void BaseEntity::LinkChildByIndex(uint32_t index, BaseEntity* pChild)
    {
        assert(pChild);

        this->UnlinkParent(pChild);
        mChildren.insert(mChildren.begin() + index, pChild);
        pChild->SetParent(this);
    }

    void BaseEntity::UnlinkParent(BaseEntity* pChild)
    {
        assert(pChild);
        
        BaseEntity* pParent = pChild->GetParent();
        if (pParent)
        {
            pParent->UnlinkChild(pChild);
        }
    }

    void BaseEntity::UnlinkChild(BaseEntity* pChild)
    {
        assert(pChild);

        size_t index = this->GetChildIndex(pChild);
        if (index != -1)
        {
            this->UnlinkChildByIndex(index);
        }
    }

    void BaseEntity::UnlinkChildByIndex(size_t index)
    {
        assert(index > 0);
        assert(index < mChildren.size());

        mChildren.erase(mChildren.begin() + index);
    }

    size_t BaseEntity::GetChildIndex(BaseEntity* pChild)
    {
        assert(pChild);

        size_t index = -1;
        for (size_t iEntity = 0; iEntity < mChildren.size(); iEntity++)
        {
            if (pChild == mChildren[iEntity])
            {
                index = iEntity;
                break;
            }
        }

        return index;
    }

    BaseEntity* BaseEntity::FindChildByName(const std::string& name)
    {
        BaseEntity* find = nullptr;

        for (auto&& child : mChildren)
        {
            if (child->GetName() == name)
            {
                find = child;
                break;
            }
        }

        return find;
    }

    BaseEntity* BaseEntity::FindChildByIndex(size_t index) const
    {
        if (index > 0 && index < mChildren.size())
        {
            return mChildren[index];
        }

        return nullptr;
    }

    glm::mat4 BaseEntity::GetLocalMatrix() const
    {
        glm::mat4 rotation = glm::toMat4(glm::quat(mRotation));
        
        return glm::translate(glm::mat4(1.0f), mTranslation)
            * rotation
            * glm::scale(glm::mat4(1.0f), mScale);
    }

    void BaseEntity::UpdateWorldMatrix()
    {
        // Если сущность не была изменена, нет смысла обновлять её позицию, выходим
        if (!mIsDirty)
        {
            return;
        }

        // Если у сущности есть родитель, перемножаем его мировую матрицу с текущей локальной
        if (mParent)
        {
            mWorldMatrix = mParent->GetWorldMatrix() * this->GetLocalMatrix();
        }
        else
        {
            // Иначе устанавливаем в качестве мировой локальную матрицу сущности
            mWorldMatrix = this->GetLocalMatrix();
        }

        // Проходим по всем дочерним сущностям и делаем то же самое
        for (auto&& child : mChildren)
        {
            child->UpdateWorldMatrix();
        }
    }

    void BaseEntity::DrawMesh(Render::Shader* pShader) const
    {
        // Если назначен меш
        if (mMesh)
        {
            pShader->SetUniformMatrix4fv("uTransform", 1, GL_FALSE, glm::value_ptr(mWorldMatrix));
            mMesh->Draw();
        }

        // Рисуем меши дочерних объектов
        for (auto&& child : mChildren)
        {
            child->DrawMesh(pShader);
        }
    }
}