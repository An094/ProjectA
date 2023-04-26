#pragma once
#include "DynamicObject.h"
#include "GameEngine.h"
#include <vector>
#include <queue>
#include "Objects/Sprite2D.h"
#include "Objects/SpriteAnimation2D.h"
class Player : public DynamicObject
{
public:
	Player(DIRECTION);
	bool IsAlive() { return isAlive; }
	void SetIsAlive(bool isA) { isAlive = isA; }

	void Update(float deltaTime);
	void Draw();
	void HandleKeyEvents(int key, bool bIsPressed);

	void Die();
	void Reborn();

	void MoveUp(float);
	void MoveRight(float);
	void MoveDown(float);
	void MoveLeft(float);
	bool CanUp;
	bool CanDown;
	bool CanLeft;
	bool CanRight;
private:
	bool isAlive;
	int m_WidthSize, m_HeightSize;
	std::vector<std::shared_ptr<EngineCore::Texture>> m_ListTexture;
	std::queue<int> m_QueueKeyEvent; //Use in future
	float m_Speed;
	int KEY;
	DIRECTION m_DefaultDir;
};

