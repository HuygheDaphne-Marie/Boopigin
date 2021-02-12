#pragma once
#include "Component.h"

namespace boop
{
	class TextComponent;
	class FpsComponent final : public Component
	{
	public:
		explicit FpsComponent(TextComponent* linkedTextComp = nullptr);
		
		void Update() override;

	private:
		TextComponent* m_pLinkedTextComponent;
		float m_MilliPassed;
		int m_TotalFrameCount;
	};

}

