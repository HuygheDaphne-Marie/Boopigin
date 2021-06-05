#pragma once
#include <Component.h>
#include <memory>
#include "ICollisionBehavior.h"
class CollisionComponent final : public boop::Component
{
public:
	explicit CollisionComponent(ICollisionBehavior* collisionBehavior);
	CollisionComponent(const CollisionComponent& other) = delete;
	CollisionComponent(CollisionComponent&& other) = delete;
	CollisionComponent& operator=(const CollisionComponent& other) = delete;
	CollisionComponent& operator=(CollisionComponent&& other) = delete;
	~CollisionComponent() override;

	void OnCollision(const std::shared_ptr<boop::GameObject>& other);

private:
	ICollisionBehavior* m_pCollisionBehavior;
};

