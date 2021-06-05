#pragma once
#include <Component.h>
#include <IEventListener.h>

class PlayerDataComponent final : public boop::Component, public IEventListener
{
public:
	explicit PlayerDataComponent(const unsigned int lives = 3);

	unsigned int GetLives() const;
	void LoseLife();
	void Reset();
	
	void Update() override;
	
	bool OnEvent(const Event& event) override;

private:
	const unsigned int m_LivesStartAmount;
	unsigned int m_Lives;
};
