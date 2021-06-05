#include "EnemyFactory.h"

#include <TextureComponent.h>
#include <TransformComponent.h>
#include "StateComponent.h"
#include "BehaviorMovementComponent.h"
#include "TumbleBehavior.h"
#include "CollisionComponent.h"
#include "ScoreGainCollision.h"
#include "KillPlayerCollision.h"
#include "ChaseQbertBehavior.h"
#include "EscheresqueTumbleBehavior.h"

float EnemyFactory::m_LeapTime = 1.0f;
unsigned int EnemyFactory::m_Depth = 1;

int EnemyFactory::m_SlickSamScoreGain = 300;
float EnemyFactory::m_SquareEnemySize = 24.f;
std::string EnemyFactory::m_SlickTexturePath = "textures/slickFrame.png"; // Todo: this must become an animation
std::string EnemyFactory::m_SamTexturePath = "textures/samFrame.png";

float EnemyFactory::m_CoilyWidth = 24.f;
float EnemyFactory::m_CoilyHeight = m_CoilyWidth * 2;
std::string EnemyFactory::m_CoilyTexturePath = "textures/coilyFrame.png";

std::string EnemyFactory::m_UggTexturePath = "textures/uggFrame.png";
std::string EnemyFactory::m_WrongwayTexturePath = "textures/wrongwayFrame.png";

std::shared_ptr<boop::GameObject> EnemyFactory::MakeSlick(boop::Scene& scene, LevelComponent* pLevel,
	const glm::ivec2& startCoordinate)
{
	auto slick = MakeTumbler(scene, pLevel, m_SlickTexturePath, startCoordinate);
	slick->AddComponent(new CollisionComponent(new ScoreGainCollision(m_SlickSamScoreGain)));
	slick->AddTag("slick");
	slick->AddTag("green");
	return slick;
}

std::shared_ptr<boop::GameObject> EnemyFactory::MakeSam(boop::Scene& scene, LevelComponent* pLevel,
	const glm::ivec2& startCoordinate)
{
	auto sam = MakeTumbler(scene, pLevel, m_SamTexturePath, startCoordinate);
	sam->AddComponent(new CollisionComponent(new ScoreGainCollision(m_SlickSamScoreGain)));
	sam->AddTag("sam");
	sam->AddTag("green");
	return sam;
}

std::shared_ptr<boop::GameObject> EnemyFactory::MakeCoily(boop::Scene& scene, LevelComponent* pLevel,
	const glm::ivec2& startCoordinate)
{
	auto go = std::make_shared<boop::GameObject>();
	go->AddComponent(new boop::TextureComponent(m_CoilyTexturePath, m_CoilyWidth, m_CoilyHeight));
	auto* transform = new boop::TransformComponent();
	go->AddComponent(transform);

	auto* state = new StateComponent();
	go->AddComponent(state);

	auto* jumper = new JumpComponent(transform, state, m_LeapTime);
	go->AddComponent(jumper);
	auto* chaseBehavior = new ChaseQbertBehavior(pLevel);
	go->AddComponent(new BehaviorMovementComponent(pLevel->GetTileWithCoordinate(startCoordinate), pLevel, jumper, state, chaseBehavior));
	go->AddComponent(new CollisionComponent(new KillPlayerCollision()));
	go->AddTag("enemy");
	go->AddTag("purple");
	go->AddTag("coily");

	scene.Add(go, m_Depth);
	return go;
}

std::shared_ptr<boop::GameObject> EnemyFactory::MakeUgg(boop::Scene& scene, LevelComponent* pLevel,
	const glm::ivec2& startCoordinate)
{
	auto ugg = MakeEscheresqueTumbler(scene, pLevel, m_UggTexturePath, true, startCoordinate);
	ugg->AddComponent(new CollisionComponent(new KillPlayerCollision()));
	ugg->AddTag("ugg");
	ugg->AddTag("purple");
	return ugg;
}

std::shared_ptr<boop::GameObject> EnemyFactory::MakeWrongway(boop::Scene& scene, LevelComponent* pLevel,
	const glm::ivec2& startCoordinate)
{
	auto wrongway = MakeEscheresqueTumbler(scene, pLevel, m_WrongwayTexturePath, false, startCoordinate);
	wrongway->AddComponent(new CollisionComponent(new KillPlayerCollision()));
	wrongway->AddTag("wrongway");
	wrongway->AddTag("purple");
	return wrongway;
}

std::shared_ptr<boop::GameObject> EnemyFactory::MakeTumbler(boop::Scene& scene, LevelComponent* pLevel, const std::string& texturePath,
                                                            const glm::ivec2& startCoordinate)
{
	auto go = std::make_shared<boop::GameObject>();
	go->AddComponent(new boop::TextureComponent(texturePath, m_SquareEnemySize, m_SquareEnemySize));
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

std::shared_ptr<boop::GameObject> EnemyFactory::MakeEscheresqueTumbler(boop::Scene& scene, LevelComponent* pLevel,
	const std::string& texturePath, bool standOnLeftSideOfTile, const glm::ivec2& startCoordinate)
{
	auto go = std::make_shared<boop::GameObject>();
	go->AddComponent(new boop::TextureComponent(texturePath, m_SquareEnemySize, m_SquareEnemySize));
	auto* transform = new boop::TransformComponent();
	go->AddComponent(transform);

	auto* state = new StateComponent();
	go->AddComponent(state);

	auto* jumper = new JumpComponent(transform, state, m_LeapTime);
	go->AddComponent(jumper);
	auto* escheresqueTumble = new EscheresqueTumbleBehavior(standOnLeftSideOfTile);
	go->AddComponent(new BehaviorMovementComponent(pLevel->GetTileWithCoordinate(startCoordinate), pLevel, jumper, state, escheresqueTumble));
	go->AddTag("enemy");

	scene.Add(go, m_Depth);
	return go;
}
