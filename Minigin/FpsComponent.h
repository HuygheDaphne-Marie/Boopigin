#pragma once
#include "Component.h"
#include <chrono>

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
		std::chrono::high_resolution_clock::time_point m_StartTime;
		int m_TotalFrameCount;
	};

}

