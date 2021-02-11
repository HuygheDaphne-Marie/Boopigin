#pragma once
#include "Component.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace boop
{
	class TransformComponent final : public Component
	{
	public:
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
		void ChangePosition(const float deltaX, const float deltaY, const float deltaZ);
		void ChangePosition(const glm::vec3& delta);
	private:
		glm::vec3 m_Position;
	};
}

