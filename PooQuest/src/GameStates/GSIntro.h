#pragma once
#include "Manager/GameStateBase.h"
#include "Manager/GameStateMachine.h"
#include "Objects/Sprite2D.h"
#include "Objects/SpriteAnimation2D.h"
#include "Objects/Button.h"
#include "Objects/Text.h"
#include "Manager/ResourceManager.h"
#include "Utils/Log.h"
class GSIntro : public EngineCore::GameStateBase
{
public:
	GSIntro();
	~GSIntro();
	void Init();
	void Exit();
	void Update(float deltaTime);
	void Draw();
	void Pause();

	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPressed);
private:
	std::shared_ptr<EngineCore::Sprite2D> m_logo;
	float m_Time;
};

