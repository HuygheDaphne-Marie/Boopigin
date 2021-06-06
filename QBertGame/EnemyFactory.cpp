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
#include "QuadDirectionalJumpAnimationComponent.h"
#include "BiDirectionalJumpAnimationComponent.h"

float EnemyFactory::m_LeapTime = 1.0f;
float EnemyFactory::m_LeapCooldownTime = 0.5f;
unsigned int EnemyFactory::m_Depth = 1;

int EnemyFactory::m_SlickSamScoreGain = 300;
int EnemyFactory::m_SquareSrcSize = 16;
int EnemyFactory::m_SquareEnemyDstSize = 24;
std::string EnemyFactory::m_SlickTexturePath = "textures/slick.png";
std::string EnemyFactory::m_SamTexturePath = "textures/sam.png";

int EnemyFactory::m_CoilySrcWidth = 16;
int EnemyFactory::m_CoilySrcHeight = 32;
int EnemyFactory::m_CoilyDstWidth = 24;
int EnemyFactory::m_CoilyDstHeight = m_CoilyDstWidth * 2;
std::string EnemyFactory::m_CoilyTexturePath = "textures/coily.png";

std::string EnemyFactory::m_UggTexturePath = "textures/uggFrame.png";
std::string EnemyFactory::m_WrongwayTexturePath = "textures/wrongwayFrame.png";

std::shared_ptr<boop::GameObject> EnemyFactory::MakeSlick(boop::Scene& scene, LevelComponent* pLevel,
	const glm::ivec2& startCoordinate)
{
	auto slick = MakeTumbler(scene, pLevel, m_SlickTexturePath, startCoordinate);
	slick->GetComponentOfType<MovementComponent>()->m_DoUnFlip = true;
	slick->AddComponent(new CollisionComponent(new ScoreGainCollision(m_SlickSamScoreGain)));
	slick->AddTag("slick");
	slick->AddTag("green");
	return slick;
}

std::shared_ptr<boop::GameObject> EnemyFactory::MakeSam(boop::Scene& scene, LevelComponent* pLevel,
	const glm::ivec2& startCoordinate)
{
	auto sam = MakeTumbler(scene, pLevel, m_SamTexturePath, startCoordinate);
	sam->GetComponentOfType<MovementComponent>()->m_DoUnFlip = true;
	sam->AddComponent(new CollisionComponent(new ScoreGainCollision(m_SlickSamScoreGain)));
	sam->AddTag("sam");
	sam->AddTag("green");
	return sam;
}

std::shared_ptr<boop::GameObject> EnemyFactory::MakeCoily(boop::Scene& scene, LevelComponent* pLevel,
	const glm::ivec2& startCoordinate)
{
	auto go = std::make_shared<boop::GameObject>();
	auto* transform = new boop::TransformComponent();
	go->AddComponent(transform);

	go->AddComponent(new QuadDirectionalJumpAnimationComponent(m_CoilyTexturePath, m_CoilySrcWidth, m_CoilySrcHeight,
		m_CoilyDstWidth, m_CoilyDstHeight));
	
	auto* state = new StateComponent();
	state->m_JumpCooldownTime = m_LeapCooldownTime;
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
	//go->AddComponent(new boop::TextureComponent(texturePath, m_SquareEnemyDstSize, m_SquareEnemyDstSize));
	auto* transform = new boop::TransformComponent();
	go->AddComponent(transform);

	go->AddComponent(new BiDirectionalJumpAnimationComponent(texturePath, m_SquareSrcSize, m_SquareSrcSize,
		m_SquareEnemyDstSize, m_SquareEnemyDstSize));

	auto* state = new StateComponent();
	state->m_JumpCooldownTime = m_LeapCooldownTime;
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
	go->AddComponent(new boop::TextureComponent(texturePath, static_cast<float>(m_SquareEnemyDstSize),
	                                            static_cast<float>(m_SquareEnemyDstSize)));
	auto* transform = new boop::TransformComponent();
	go->AddComponent(transform);

	auto* state = new StateComponent();
	state->m_JumpCooldownTime = m_LeapCooldownTime;
	go->AddComponent(state);

	auto* jumper = new JumpComponent(transform, state, m_LeapTime);
	go->AddComponent(jumper);
	auto* escheresqueTumble = new EscheresqueTumbleBehavior(standOnLeftSideOfTile);
	go->AddComponent(new BehaviorMovementComponent(pLevel->GetTileWithCoordinate(startCoordinate), pLevel, jumper, state, escheresqueTumble));
	go->AddTag("enemy");

	scene.Add(go, m_Depth);
	return go;
}
