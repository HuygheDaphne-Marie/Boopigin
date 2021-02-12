#include "MiniginPCH.h"
#include  "GameObject.h"
#include "Component.h"

void boop::GameObject::FixedUpdate()
{
	for (Component* pElement : m_Components)
	{
		pElement->FixedUpdate();
	}
}

void boop::GameObject::Update()
{
	for (Component* pElement : m_Components)
	{
		pElement->Update();
	}
}

void boop::GameObject::LateUpdate()
{
	for (Component* pElement : m_Components)
	{
		pElement->LateUpdate();
	}
}

void boop::GameObject::Render() const
{
	for (const Component* pElement : m_Components)
	{
		pElement->Render();
	}
}

void boop::GameObject::AddComponent(Component* pComponentToAdd)
{
	const auto findItrResult = std::find_if(m_Components.begin(), m_Components.end(), 
		[pComponentToAdd](Component* pComponent) { return pComponent == pComponentToAdd; } );
	
	if (findItrResult == m_Components.end())
	{
		m_Components.push_back(pComponentToAdd);
		pComponentToAdd->SetOwner(this);
	}
}

void boop::GameObject::RemoveComponent(Component* pComponentToRemove)
{
	for (int index = static_cast<int>(m_Components.size()) - 1; index >= 0; index--)
	{
		if (m_Components[index] == pComponentToRemove)
		{
			m_Components[index] = m_Components[m_Components.size() - 1];
			m_Components.pop_back();
			return;
		}
	}
}
