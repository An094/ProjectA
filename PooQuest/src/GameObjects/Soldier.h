#pragma once
#include "Enemy.h"
#include "Objects/Texture.h"
#include <vector>
class Soldier : public Enemy
{
public:
	Soldier(DIRECTION dir, float maxD, float speed);
	void Update(float deltaTime) override;
	void Draw() override;
private:
	float m_MaxDistance;
	std::vector<std::shared_ptr<EngineCore::Texture>> m_ListTexture;
	float m_Distance;
};

