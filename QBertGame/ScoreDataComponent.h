#pragma once
#include <Component.h>
#include <IEventListener.h>

class ScoreDataComponent final : public boop::Component, IEventListener
{
public:
	ScoreDataComponent();

	bool OnEvent(const Event& event) override;

	unsigned int GetScore() const;

	void Reset();

private:
	unsigned int m_Score;
};

