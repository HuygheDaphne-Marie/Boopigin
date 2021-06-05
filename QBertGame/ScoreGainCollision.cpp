#include "ScoreGainCollision.h"
#include <EventQueue.h>

ScoreGainCollision::ScoreGainCollision(int amountGained)
	: m_ScoreGainAmount(amountGained)
{
}

void ScoreGainCollision::OnCollision(const std::shared_ptr<boop::GameObject>& other, boop::GameObject* self)
{
	if (other->HasTag("qbert"))
	{
		EventQueue::GetInstance().Broadcast(new Event("ScoreGained", m_ScoreGainAmount));
		self->MarkForDelete();
	}
}
