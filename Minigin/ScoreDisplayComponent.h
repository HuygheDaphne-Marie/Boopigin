#pragma once
#include "Component.h"
#include "Event.h"

namespace boop
{
	class Observer;
	class TextComponent;

	class ScoreDisplayComponent final : public Component
	{
	public:
		explicit ScoreDisplayComponent(TextComponent* pLinkedTextComponent = nullptr);
		~ScoreDisplayComponent();
		
		void OnScoreGained(const Event& event);

		void Update() override;

		[[nodiscard]] Observer* GetObserver() const;
	
	private:
		TextComponent* m_pTextComponent;
		
		bool m_ScoreChanged;
		int m_Score;

		Observer* m_pObserver;
	};
}

