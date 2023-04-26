#include "Soldier.h"
#include "Manager/ResourceManager.h"
#include "Objects/SpriteAnimation2D.h"
Soldier::Soldier(DIRECTION dir, float maxD, float speed) 
	: Enemy(ENEMY_TYPE::SOLDIER, dir, speed), m_MaxDistance(maxD), m_Distance(0.0f)
{
	std::shared_ptr<EngineCore::Texture> tmpTexture = EngineCore::ResourceManager::GetInstance()->GetTexture("Enemy/enemy0_up.tga");
	m_ListTexture.push_back(tmpTexture);
	tmpTexture = EngineCore::ResourceManager::GetInstance()->GetTexture("Enemy/enemy0_right.tga");
	m_ListTexture.push_back(tmpTexture);
	tmpTexture = EngineCore::ResourceManager::GetInstance()->GetTexture("Enemy/enemy0_down.tga");
	m_ListTexture.push_back(tmpTexture);
	tmpTexture = EngineCore::ResourceManager::GetInstance()->GetTexture("Enemy/enemy0_left.tga");
	m_ListTexture.push_back(tmpTexture);

	SetSprite(std::make_shared<EngineCore::SpriteAnimation2D>("Enemy/enemy0_up.tga", "Texture", "Animation", 8, 0.1f));
	SetCurrentTexture(m_ListTexture[static_cast<int>(dir)]);
}

void Soldier::Update(float deltaTime)
{
	if (m_Distance >= m_MaxDistance)
	{
		int reverseDir = (static_cast<int>(GetDirection()) + 2) % 4;
		SetDirection(static_cast<DIRECTION>(reverseDir));
		SetCurrentTexture(m_ListTexture[reverseDir]);
		m_Distance = m_MaxDistance - m_Distance;
	}
	else
	{
		glm::vec2 currentPos = GetPosition();
		float deltaDistance = GetSpeed() * deltaTime;
		m_Distance += deltaDistance;
		switch (GetDirection())
		{
			case DIRECTION::UP:
			{
				currentPos[1] -= deltaDistance;	
				break;
			}
			case DIRECTION::RIGHT:
			{
				currentPos[0] += deltaDistance;
				break;
			}
			case DIRECTION::DOWN:
			{
				currentPos[1] += deltaDistance;
				break;
			}
			case DIRECTION::LEFT:
			{
				currentPos[0] -= deltaDistance;
				break;
			}
		}
		SetPosition(currentPos);
	}
	GetSprite()->Update(deltaTime);
}

void Soldier::Draw()
{
	GetSprite()->Draw();
}
