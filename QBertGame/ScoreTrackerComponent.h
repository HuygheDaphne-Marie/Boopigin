#pragma once
#include <Component.h>
#include <TextComponent.h>
#include "ScoreDataComponent.h"

class ScoreTrackerComponent final : public boop::Component
{
public:
	explicit ScoreTrackerComponent(ScoreDataComponent* scoreData, boop::TextComponent* textDisplay = nullptr);

	void Startup() override;
	void Update() override;

private:
	ScoreDataComponent* m_pScoreData;
	boop::TextComponent* m_pTextDisplay;
	unsigned int m_Score;
};

