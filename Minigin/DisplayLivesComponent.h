#pragma once
#include "Component.h"
#include "Observer.h"

namespace boop
{
	class TextComponent;
	class PlayerComponent;
	
	class DisplayLivesComponent final : public Component
	{
	public:
		explicit DisplayLivesComponent(PlayerComponent* pLinkedPlayer, TextComponent* pLinkedTextComponent = nullptr);
		~DisplayLivesComponent();
		
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

