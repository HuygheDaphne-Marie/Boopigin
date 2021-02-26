#pragma once
#include "Component.h"
#include <memory>

#include "LifeDisplayComponent.h"

namespace boop
{
	class Subject;
	class DieCommand;
	
	class PlayerComponent final : public Component
	{
	public:
		PlayerComponent();
		~PlayerComponent();

		void Update() override;
		
		void OnDeath();
		void OnScoreGained(int amount) const; // this would be in some other function obviously
		
		[[nodiscard]] int GetLives() const;

		std::shared_ptr<Subject> m_pSubject;
	private:
		DieCommand* m_pDieCommand;
		int m_Lives;

		bool m_FirstUpdate = true;
	};
}

