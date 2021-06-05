#pragma once
#include <memory>
#include <GameObject.h>

class ICollisionBehavior
{
public:
	virtual ~ICollisionBehavior() = default;
	virtual void OnCollision(const std::shared_ptr<boop::GameObject>& other, boop::GameObject* self) = 0;
};

