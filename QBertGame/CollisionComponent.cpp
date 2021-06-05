#include "CollisionComponent.h"

CollisionComponent::CollisionComponent(ICollisionBehavior* collisionBehavior)
	: m_pCollisionBehavior(collisionBehavior)
{
}

CollisionComponent::~CollisionComponent()
{
	delete m_pCollisionBehavior;
}

void CollisionComponent::OnCollision(const std::shared_ptr<boop::GameObject>& other)
{
	m_pCollisionBehavior->OnCollision(other, m_pOwner);
}
