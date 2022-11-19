#pragma once

namespace Render
{
    class KitTransform
    {
	public:
		/*
		Локальная информация о трансформации
		*/
        glm::vec3 Translation   = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation      = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale         = { 1.0f, 1.0f, 1.0f };

		/*
		Мировая информация о трансформации получаемая путём перемножения всех дочерних трансформаций
		*/
		glm::mat4 WorldTransformMatrix = glm::mat4(1.0f);
		
		/* Указатель на родительский компонент трансформации */
		KitTransform* pParent = { nullptr };

		/* Список указателей на дочерние компоненты трансформации */
		std::list<KitTransform*> mChildren;

        KitTransform() = default;
		KitTransform(const KitTransform&) = default;
		explicit KitTransform(const glm::vec3& translation)
			: Translation(translation) {}
        KitTransform(const glm::vec3& translation, const glm::vec3& rotation)
            : Translation(translation), Rotation(rotation) {}
        KitTransform(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
            : Translation(translation), Rotation(rotation), Scale(scale) {}

		/*
		@brief Возвращает матрицу с локальной трансформацией объекта
		@return локальная матрица трансформации 
		*/
        glm::mat4 GetLocalTransform() const
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Translation)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
		}

		/*
		Обновляет информацию о мировой трансформации объекта
		*/
		void UpdateWorldTransform()
		{
			if (nullptr != pParent)
			{
				WorldTransformMatrix = pParent->WorldTransformMatrix * this->GetLocalTransform();
			} 
			else 
			{
				WorldTransformMatrix = this->GetLocalTransform();
			}

			for (auto&& child : mChildren)
			{
				child->UpdateWorldTransform();
			}
		}
    };
}