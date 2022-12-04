#include "pch.h"
#include "GameObject.h"

GameObject::GameObject(const std::string& name /* = Root */)
{
    mName = name;
}

void GameObject::LinkChild(GameObject* pChild)
{
    this->UnlinkParent(pChild);
    mChildren.emplace_back(pChild);
    pChild->SetParent(this);
}

void GameObject::LinkChildByIndex(uint32_t index, GameObject* pChild)
{
    assert(pChild);

    this->UnlinkParent(pChild);
    mChildren.insert(mChildren.begin() + index, pChild);
    pChild->SetParent(this);
}

void GameObject::UnlinkParent(GameObject* pChild)
{
    assert(pChild);
    
    GameObject* pParent = pChild->GetParent();
    if (pParent)
    {
        pParent->UnlinkChild(pChild);
    }
}

void GameObject::UnlinkChild(GameObject* pChild)
{
    assert(pChild);

    size_t index = this->GetChildIndex(pChild);
    if (index != -1)
    {
        this->UnlinkChildByIndex(index);
    }
}

void GameObject::UnlinkChildByIndex(size_t index)
{
    assert(index > 0);
    assert(index < mChildren.size());

    mChildren.erase(mChildren.begin() + index);
}

size_t GameObject::GetChildIndex(GameObject* pChild)
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

GameObject* GameObject::FindChildByName(const std::string& name)
{
    GameObject* find = nullptr;

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

GameObject* GameObject::GetChildByIndex(size_t index) const
{
    if (index >= 0 && index < mChildren.size())
    {
        return mChildren[index];
    }

    return nullptr;
}

glm::mat4 GameObject::GetLocalMatrix() const
{
    glm::mat4 rotation = glm::toMat4(glm::quat(mRotation));
    
    return glm::translate(glm::mat4(1.0f), mTranslation)
        * rotation
        * glm::scale(glm::mat4(1.0f), mScale);
}

void GameObject::UpdateWorldMatrix()
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

void GameObject::DrawMesh(Render::Shader* pShader, const float* view_matrix, float* proj_matrix) const
{
    assert(view_matrix && "view_matrix can't be nullptr");
    assert(proj_matrix && "proj_matrix can't be nullptr");

    // Если назначен меш
    if (mMesh)
    {
        mMesh->mMaterial->mShader->Enable();
        mMesh->mMaterial->Use();
        mMesh->mMaterial->mShader->SetUniformMatrix4fv("uView"      , 1, GL_FALSE, view_matrix);
        mMesh->mMaterial->mShader->SetUniformMatrix4fv("uProjection", 1, GL_FALSE, proj_matrix);            
        mMesh->mMaterial->mShader->SetUniformMatrix4fv("uTransform", 1, GL_FALSE, glm::value_ptr(mWorldMatrix));
        mMesh->Draw();
    }

    // Рисуем меши дочерних объектов
    for (auto&& child : mChildren)
    {
        child->DrawMesh(pShader, view_matrix, proj_matrix);
    }
}