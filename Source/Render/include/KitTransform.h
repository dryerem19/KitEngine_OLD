#pragma once

namespace Render
{
    class KitTransform
    {
	public:
        glm::vec3 Translation   = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation      = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale         = { 1.0f, 1.0f, 1.0f };

        KitTransform() = default;
		KitTransform(const KitTransform&) = default;
		explicit KitTransform(const glm::vec3& translation)
			: Translation(translation) {}
        KitTransform(const glm::vec3& translation, const glm::vec3& rotation)
            : Translation(translation), Rotation(rotation) {}
        KitTransform(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
            : Translation(translation), Rotation(rotation), Scale(scale) {}

        [[nodiscard]] glm::mat4 GetTransform() const
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Translation)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
		}
    };
}