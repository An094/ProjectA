#pragma once
#include "Objects/SpriteAnimation2D.h"
class Gold
{
public:
	Gold();
	~Gold() = default;
	void SetPosition(int x, int y);
	glm::vec2 GetPosition();
	void SetSize(int size);
	
	void Update(float deltaTime);
	void Draw();

	void Disable();
	bool isActive;
private:
	std::shared_ptr<EngineCore::SpriteAnimation2D> m_Sprite;
};

