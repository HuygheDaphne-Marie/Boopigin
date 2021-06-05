#pragma once
#include "ICollisionBehavior.h"


class ScoreGainCollision : public ICollisionBehavior
{
public:
	explicit ScoreGainCollision(int amountGained);
	void OnCollision(const std::shared_ptr<boop::GameObject>& other, boop::GameObject* self) override;

private:
	const int m_ScoreGainAmount;
};

