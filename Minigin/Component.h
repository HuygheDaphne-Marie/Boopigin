#pragma once
#include "SceneObject.h"

namespace boop
{
	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		void FixedUpdate();
		void Update();
		void LateUpdate();

		void Render() const;

	private:
		SceneObject* m_pOwner = nullptr;
};
}

