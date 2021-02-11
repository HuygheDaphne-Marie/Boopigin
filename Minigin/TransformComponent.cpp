#include "MiniginPCH.h"
#include "TransformComponent.h"



#include "GameObject.h"
#include "GameObject.h"
#include "GameObject.h"
#include "GameObject.h"

void boop::TransformComponent::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void boop::TransformComponent::ChangePosition(const float deltaX, const float deltaY, const float deltaZ)
{
	m_Position.x += deltaX;
	m_Position.y += deltaY;
	m_Position.z += deltaZ;
}

void boop::TransformComponent::ChangePosition(const glm::vec3& delta)
{
	ChangePosition(delta.x, delta.y, delta.z);
}
