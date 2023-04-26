#pragma once
#include "Enemy.h"
#include "Objects/Texture.h"
#include  <vector>
class Trap : public Enemy
{
public:
	Trap(int state, int current, int timestate0, int timestate1);
	~Trap() = default;
	void Update(float) override;
	void Draw() override;
private:
	std::vector<std::shared_ptr<EngineCore::Texture>> m_ListTexture;
	int m_State;
	float m_TimeInState[2];
	float m_CurrentTimeInState;
	bool isInRaise;
};

