#pragma once
#include "GameObject.h"

namespace boop
{
	
	class Component
	{
	public:
		//inline static std::string m_ComponentName{"Component"};

		
		Component() = default;
		virtual ~Component() = default; // probably need to notify owner of our destruction
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		//static const std::string& GetComponentName();

		virtual void FixedUpdate();
		virtual void Update();
		virtual void LateUpdate();

		virtual void Render() const;

		void SetOwner(GameObject* newOwner);

	protected:
		GameObject* m_pOwner = nullptr;
};
}

