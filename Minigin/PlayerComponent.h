#pragma once
#include "Component.h"
#include <memory>

namespace boop
{
	class Subject;
	class DieCommand;
	
	class PlayerComponent final : public Component
	{
	public:
		PlayerComponent();
		~PlayerComponent();
		
		void OnDeath() const;
	
		std::shared_ptr<Subject> m_pSubject;
	private:
		DieCommand* m_pDieCommand;
	};
}

