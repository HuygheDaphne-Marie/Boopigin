#include "EnemyFactory.h"

#include <TextureComponent.h>
#include <TransformComponent.h>
#include "StateComponent.h"
#include "BehaviorMovementComponent.h"
#include "TumbleBehavior.h"
#include "CollisionComponent.h"
#include "ScoreGainCollision.h"

float EnemyFactory::m_LeapTime = 0.7f;
unsigned int EnemyFactory::m_Depth = 1;

float EnemyFactory::m_SlickSamSize = 32.f;
std::string EnemyFactory::m_SlickTexturePath = "textures/slickFrame.png"; // Todo: this must become an animation
std::string EnemyFactory::m_SamTexturePath = "textures/samFrame.png";

std::shared_ptr<boop::GameObject> EnemyFactory::MakeSlick(boop::Scene& scene, LevelComponent* pLevel,
	const glm::ivec2& startCoordinate)
{
	auto slick = MakeTumbler(scene, pLevel, m_SlickTexturePath, startCoordinate);
	slick->AddComponent(new CollisionComponent(new ScoreGainCollision(300)));
	slick->AddTag("slick");
	slick->AddTag("green");
	return slick;
}

std::shared_ptr<boop::GameObject> EnemyFactory::MakeSam(boop::Scene& scene, LevelComponent* pLevel,
	const glm::ivec2& startCoordinate)
{
	auto sam = MakeTumbler(scene, pLevel, m_SamTexturePath, startCoordinate);
	sam->AddComponent(new CollisionComponent(new ScoreGainCollision(300)));
	sam->AddTag("sam");
	sam->AddTag("green");
	return sam;
}

std::shared_ptr<boop::GameObject> EnemyFactory::MakeTumbler(boop::Scene& scene, LevelComponent* pLevel, const std::string& texturePath,
	const glm::ivec2& startCoordinate)
{
	auto go = std::make_shared<boop::GameObject>();
	go->AddComponent(new boop::TextureComponent(texturePath, m_SlickSamSize, m_SlickSamSize));
	auto* transform = new boop::TransformComponent();
	go->AddComponent(transform);

	auto* state = new StateComponent();
	go->AddComponent(state);

	auto* jumper = new JumpComponent(transform, state, m_LeapTime);
	go->AddComponent(jumper);
	auto* tumbleBehavior = new TumbleBehavior();
	go->AddComponent(new BehaviorMovementComponent(pLevel->GetTileWithCoordinate(startCoordinate), pLevel, jumper, state, tumbleBehavior));
	go->AddTag("enemy");
	
	scene.Add(go, m_Depth);
	return go;
}
