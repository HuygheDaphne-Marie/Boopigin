#include "KillPlayerCollision.h"
#include <EventQueue.h>

void KillPlayerCollision::OnCollision(const std::shared_ptr<boop::GameObject>& other, boop::GameObject* self)
{
	if (other->HasTag("qbert") && !self->IsMarkedForDelete())
	{
		EventQueue::GetInstance().Broadcast(new Event("PlayerTakeDamage", other.get()));
	}
}
