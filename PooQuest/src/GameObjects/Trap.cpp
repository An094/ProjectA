#include "Trap.h"
#include "Manager/ResourceManager.h"
Trap::Trap(int state, int current, int timestate0, int timestate1) : Enemy(), isInRaise(false), m_State(state)
	, m_CurrentTimeInState(0.05f * current)
{
	m_TimeInState[0] = 0.05f * timestate0;
	m_TimeInState[1] = 0.05f * timestate1;

	m_ListTexture.push_back(EngineCore::ResourceManager::GetInstance()->GetTexture("Enemy/trap0.tga"));
	m_ListTexture.push_back(EngineCore::ResourceManager::GetInstance()->GetTexture("Enemy/trap1.tga"));
	m_ListTexture.push_back(EngineCore::ResourceManager::GetInstance()->GetTexture("Enemy/trap2.tga"));
	
	SetSprite(std::make_shared<EngineCore::Sprite2D>("Enemy/trap0.tga"));
	SetCurrentTexture(m_ListTexture[state]);
}

void Trap::Update(float deltaTime)
{
	if (m_State == 1)
	{
		SetActivate(true);
	}
	else
	{
		SetActivate(false);
	}
	m_CurrentTimeInState += deltaTime;
	if (m_CurrentTimeInState >= m_TimeInState[m_State])
	{
		isInRaise = true;
		m_State = 1 - m_State;
		m_CurrentTimeInState = 0.0f;
		SetCurrentTexture(m_ListTexture[m_State]);
	}
}

void Trap::Draw()
{
	GetSprite()->Draw();
}
