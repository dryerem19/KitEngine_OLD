#pragma once
#include "KitComponent.h"

namespace Render
{
    /*
    Нода сцены
    */
    class KitSceneNode : public KitComponent
    {
    protected:
        /* Имя ноды */
        std::string mName;

        /* Иконка ноды в окне иерархии */
        std::string mHierarchyIcon;

        /* Родительская нода */
        KitSceneNode* mParent = nullptr;

        /* Дочерние ноды */
        std::vector<KitSceneNode*> mChildren;

    public:
        /* Конструктор ноды с именем ноды, иконка не устанавливается*/
        KitSceneNode(const KitObject& attachedObject) : KitComponent(attachedObject) { }
        /*
        @brief Устанавливает имя ноды
        @param name Новое имя ноды
        */
        void SetName(const std::string& name) { mName = name; }

        /*
        @brief Возвращает имя ноды
        @return Имя ноды
        */
        std::string GetName() const { return mName; }

        /*
        @brief Устанавливает родительскую ноду
        @param parent Указатель на родительскую ноду
        */
        void SetParent(KitSceneNode* parent) { mParent = parent; }

        /*
        @brief Возвращает указатель на родительскую ноду
        @return Указатель на родительскую ноду
        */
        KitSceneNode* GetParent() const { return mParent; }    

        /*
        @brief Добавить дочернюю ноду
        @param child Дочерняя нода
        */
        void AddChild(KitSceneNode* child) { mChildren.emplace_back(child); }

        /*
        @brief Устанавливает FontAwesome иконку для отображения в панели иерархии
        @param Код иконки
        */
        void SetHierarchyIcon(const std::string& icon) { mHierarchyIcon = icon; }

        /*
        @brief Проверяет наличие иконки у ноды
        @return True, если иконка установлена, иначе False
        */
        bool HasIcon() const { return mHierarchyIcon.empty(); }

        /*
        @brief Возвращает FontAwesome иконку
        */
        std::string GetHierarchyIcon() const { return mHierarchyIcon; }    

        /*
        @brief Возвращает итератор на первый дочерний меш
        @return Итератор на дочерний меш
        */
        constexpr std::vector<Render::KitSceneNode*>::iterator begin() noexcept
        { return mChildren.begin(); }

        /*
        @brief Возвращает итератор на последний дочерний меш
        @return Итератор на последний меш
        */
        constexpr std::vector<Render::KitSceneNode *>::iterator end() noexcept
        { return mChildren.end(); }

        /*
        @brief Возвращает константный итератор на первый дочерний меш
        @return Итератор на дочерний меш
        */
        constexpr std::vector<Render::KitSceneNode*>::const_iterator cbegin() noexcept
        { return mChildren.cbegin(); }

        /*
        @brief Возвращает константный итератор на последний дочерний меш
        @return Итератор на дочрений меш
        */
        constexpr std::vector<Render::KitSceneNode*>::const_iterator cend() noexcept
        { return mChildren.cend(); }             
    };
}