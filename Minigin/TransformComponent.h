#pragma once
#include "Component.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)

namespace boop
{
	class TransformComponent final : public Component
	{
	public:
		explicit TransformComponent(float x = 0.f, float y = 0.f, float z = 0.f);

		[[nodiscard]] const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z = 0.f);
		void ChangePosition(const float deltaX, const float deltaY, const float deltaZ = 0.f);
		void ChangePosition(const glm::vec3& delta);
	private:
		glm::vec3 m_Position;
	};
}

