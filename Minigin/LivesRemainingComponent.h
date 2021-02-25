#pragma once
#include "Component.h"
#include "Observer.h"

namespace boop
{
	class TextComponent;

	class LivesRemainingComponent final : public Component, public Observer
	{
	public:
		explicit LivesRemainingComponent(TextComponent* pLinkedTextComponent = nullptr);

		void Update() override;

		void OnNotify(const std::string& message) override;
		void OnAdd() override;
		void OnRemove() override;
	
	private:
		TextComponent* m_pTextComponent;
		bool m_LivesChanged;
		int m_LivesLeft;
	};
}

