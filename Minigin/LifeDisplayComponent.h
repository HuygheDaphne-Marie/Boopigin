#pragma once
#include "Component.h"
#include "Observer.h"

namespace boop
{
	class TextComponent;
	class PlayerComponent;
	
	class LifeDisplayComponent final : public Component
	{
	public:
		explicit LifeDisplayComponent(PlayerComponent* pLinkedPlayer, TextComponent* pLinkedTextComponent = nullptr);
		~LifeDisplayComponent();
		
		[[nodiscard]] Observer* GetObserver() const;
		void OnDeath(const Event& event);
		
		void Update() override;
	
	private:
		TextComponent* m_pTextComponent;
		PlayerComponent* m_PlayerComponent;
		bool m_LivesChanged;
		int m_LivesLeft;

		Observer* m_pObserver;
	};
}

