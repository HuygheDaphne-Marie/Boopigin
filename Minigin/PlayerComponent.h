#pragma once
#include "Component.h"
#include <memory>

#include "DisplayLivesComponent.h"

namespace boop
{
	class Subject;
	class DieCommand;
	
	class PlayerComponent final : public Component
	{
	public:
		PlayerComponent();
		~PlayerComponent();
		
		void OnDeath();
		[[nodiscard]] int GetLives() const;

		std::shared_ptr<Subject> m_pSubject;
	private:
		DieCommand* m_pDieCommand;
		int m_Lives;
	};
}

