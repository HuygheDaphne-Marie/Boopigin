#pragma once
#include <vector>
#include <string>

namespace boop
{
	class Component;
	class GameObject final
	{
	public:
		void Startup();
		void FixedUpdate();
		void Update();
		void LateUpdate();
		
		void Render() const;
		void MarkForDelete();
		[[nodiscard]] bool IsMarkedForDelete() const;

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void AddComponent(Component* pComponentToAdd);
		void RemoveComponent(Component* pComponentToRemove);

		bool HasTag(const std::string& tag);
		void AddTag(const std::string& tag);

		template <typename TypeOfComponent>
		inline TypeOfComponent* GetComponentOfType() const
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
		std::vector<std::string> m_Tags{};
		bool m_IsMarkedForDeletion = false;
		bool m_IsFirstUpdate = true;
	};
}
