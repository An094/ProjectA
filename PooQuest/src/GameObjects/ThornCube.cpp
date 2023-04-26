#include "ThornCube.h"
#include "Objects/SpriteAnimation2D.h"
#include "Manager/ResourceManager.h"

ThornCube::ThornCube(DIRECTION dir, float maxdis0, float maxdis1, float speed) : Enemy(ENEMY_TYPE::THORN_CUBE, dir, speed)
	, m_CurrentDistance(0.0f)
{
	SetSprite(std::make_shared<EngineCore::SpriteAnimation2D>("Enemy/enemy2.tga", "Texture", "Animation", 6, 0.1));
	m_MaxDistance[0] = maxdis0;
	m_MaxDistance[1] = maxdis1;
	m_MaxDistance[2] = maxdis0;
	m_MaxDistance[3] = maxdis1;
}

void ThornCube::Update(float deltaTime)
{
	int direction = static_cast<int>(GetDirection());
	if (m_CurrentDistance >= m_MaxDistance[direction])
	{
		direction = (direction + 3) % 4;
		SetDirection(static_cast<DIRECTION>(direction));
		m_CurrentDistance = 0.0f;
	}
	else
	{
		glm::vec2 pos = GetPosition();
		float deltaDistance = GetSpeed() * deltaTime;
		m_CurrentDistance += deltaDistance;
		switch (static_cast<DIRECTION>(direction))
		{
			case DIRECTION::UP:
			{
				pos.y -= deltaDistance;
				break;
			}
			case DIRECTION::RIGHT:
			{
				pos.x += deltaDistance;
				break;
			}
			case DIRECTION::DOWN:
			{
				pos.y += deltaDistance;
				break;
			}
			case DIRECTION::LEFT:
			{
				pos.x -= deltaDistance;
				break;
			}
		}
		SetPosition(pos);
	}
}

void ThornCube::Draw()
{
	GetSprite()->Draw();
}