#pragma once
#include <vector>

namespace boop
{
	class Component;
	class GameObject final
	{
	public:
		void FixedUpdate();
		void Update();
		void LateUpdate();
		
		void Render() const;

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void AddComponent(Component* pComponentToAdd);
		void RemoveComponent(Component* pComponentToRemove);

		template <typename TypeOfComponent>
		inline TypeOfComponent* GetComponentOfType()
		{
			for (Component* component : m_Components)
			{
				if(typeid(TypeOfComponent).name() == typeid(*component).name())
				{
					return static_cast<TypeOfComponent*>(component);
				}
			}
			return nullptr;
		}

	private:
		std::vector<Component*> m_Components{};
	};
}
