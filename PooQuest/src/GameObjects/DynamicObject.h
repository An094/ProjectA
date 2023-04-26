#pragma once
#include "Objects/Sprite2D.h"
#include "Objects/Texture.h"

enum  class DIRECTION
{
	UP = 0,
	RIGHT,
	DOWN,
	LEFT
};

typedef struct TILEMAP_COOR
{
	int x, y;
};

class DynamicObject
{
public:
	DynamicObject() = default;
	DynamicObject(DIRECTION dir, int speed);
	virtual ~DynamicObject() = default;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;


	inline void SetDirection(DIRECTION dir) { m_Dir = dir; }
	DIRECTION GetDirection() const { return m_Dir; }

	void SetPosition(const glm::vec2& pos) { m_Sprite->SetPosition(pos); }
	void SetPosition(int x, int y) { m_Sprite->SetPosition(x, y); }
	glm::vec2 GetPosition() const { return m_Sprite->GetPosition(); }

	void SetSize(int widthSprite, int heightSprite) { m_Sprite->SetSize(widthSprite, heightSprite); }
	void GetSize(int& width, int& height) { m_Sprite->GetSize(width, height); }

	void SetSprite(const std::shared_ptr<EngineCore::Sprite2D>& sprite);
	std::shared_ptr<EngineCore::Sprite2D> GetSprite();

	void SetCurrentTexture(std::shared_ptr<EngineCore::Texture> newTexture);
	std::shared_ptr<EngineCore::Texture> GetCurrentTexture();

	void SetStartPoint(TILEMAP_COOR coor);
	TILEMAP_COOR GetStartPoint();

	void SetSpeed(float speed) { m_Speed = speed; }
	float GetSpeed() { return m_Speed; }
private:
	DIRECTION m_Dir;
	TILEMAP_COOR m_StartPoint;
	std::shared_ptr<EngineCore::Sprite2D> m_Sprite;
	float m_Speed;
};

