#pragma once
#include "ICollisionBehavior.h"
class KillPlayerCollision : public ICollisionBehavior
{
public:
	void OnCollision(const std::shared_ptr<boop::GameObject>& other, boop::GameObject* self) override;
};

