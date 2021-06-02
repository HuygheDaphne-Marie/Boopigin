#include "MiniginPCH.h"
#include "Component.h"

// These have empty implementation so that subclasses aren't forced to make these all the time.
void boop::Component::FixedUpdate()
{
}
void boop::Component::Update()
{
}
void boop::Component::LateUpdate()
{
}
void boop::Component::Render() const
{
}

void boop::Component::SetOwner(GameObject* newOwner)
{
	if (m_pOwner != nullptr)
	{
		m_pOwner->RemoveComponent(this);
	}
	m_pOwner = newOwner;
}

const boop::GameObject* boop::Component::GetOwner() const
{
	return m_pOwner;
}
