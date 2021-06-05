#include "MiniginPCH.h"
#include  "GameObject.h"
#include "Component.h"

boop::GameObject::~GameObject()
{
	for (int index = static_cast<int>(m_Components.size()) - 1; index >= 0; index--)
	{
		delete m_Components[index];
		m_Components.pop_back();
	}
}

void boop::GameObject::Startup()
{
	if (m_IsMarkedForDeletion)
		return;

	for (Component* pElement : m_Components)
	{
		pElement->Startup();
	}
}

void boop::GameObject::FixedUpdate()
{
	if (m_IsMarkedForDeletion)
		return;
	
	for (Component* pElement : m_Components)
	{
		pElement->FixedUpdate();
	}
}

void boop::GameObject::Update()
{
	if (m_IsMarkedForDeletion)
		return;

	if (m_IsFirstUpdate)
	{
		for (Component* pElement : m_Components)
		{
			pElement->Startup();
		}
		m_IsFirstUpdate = false;
	}
	
	for (Component* pElement : m_Components)
	{
		pElement->Update();
	}
}

void boop::GameObject::LateUpdate()
{
	if (m_IsMarkedForDeletion)
		return;

	for (Component* pElement : m_Components)
	{
		pElement->LateUpdate();
	}
}

void boop::GameObject::Render() const
{
	if (m_IsMarkedForDeletion)
		return;

	for (const Component* pElement : m_Components)
	{
		pElement->Render();
	}
}

void boop::GameObject::MarkForDelete()
{
	m_IsMarkedForDeletion = true;
}

bool boop::GameObject::IsMarkedForDelete() const
{
	return m_IsMarkedForDeletion;
}

void boop::GameObject::AddComponent(Component* pComponentToAdd)
{
	if (m_IsMarkedForDeletion)
		return;

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

bool boop::GameObject::HasTag(const std::string& tag)
{
	const auto tagItr = std::find(m_Tags.begin(), m_Tags.end(), tag);
	return tagItr != m_Tags.end();
}
void boop::GameObject::AddTag(const std::string& tag)
{
	if (!HasTag(tag))
	{
		m_Tags.push_back(tag);
	}
}
