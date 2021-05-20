#pragma once
#include <Scene.h>

class LevelFactory final
{
public:
	static void MakeLevel(boop::Scene& scene, int levelNumber, int size, bool isTriangle = true);
};

