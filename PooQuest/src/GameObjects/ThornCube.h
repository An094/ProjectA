#pragma once
#include "Enemy.h"

class ThornCube : public Enemy
{
public:
	ThornCube(DIRECTION, float, float, float);
	~ThornCube() = default;
	void Update(float deltaTime);
	void Draw();
private:
	float m_MaxDistance[4];
	float m_CurrentDistance;
};

