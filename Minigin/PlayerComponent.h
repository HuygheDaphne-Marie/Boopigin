#pragma once
#include "Component.h"
#include <memory>

#include "LifeDisplayComponent.h"
#include "Key.h"

namespace boop
{
	class Subject;
	class DieCommand;
	class ScoreCommand;
	
	class PlayerComponent final : public Component
	{
	public:
		PlayerComponent(ControllerButton dieButton, ControllerButton scoreButton);
		~PlayerComponent();

		void Update() override;
		
		void OnDeath();
		void ScoreGained(int amount) const; // this would be in some other function obviously
		
		[[nodiscard]] int GetLives() const;

		std::shared_ptr<Subject> m_pSubject;
	private:
		DieCommand* m_pDieCommand;
		ScoreCommand* m_pScoreCommand;
		int m_Lives;

		bool m_FirstUpdate = true;
	};
}

