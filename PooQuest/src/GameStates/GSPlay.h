#pragma once
#include "Manager/GameStateBase.h"
#include "Manager/GameStateMachine.h"
#include "Objects/Sprite2D.h"
#include "Objects/SpriteAnimation2D.h"
#include "Objects/Button.h"
#include "Objects/Text.h"
#include "Manager/ResourceManager.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/MapController.h"

class GSPlay : public EngineCore::GameStateBase
{
public:
	GSPlay();
	~GSPlay();
	void Init();
	void Exit();
	void Update(float deltaTime);
	void Draw();
	void Pause();

	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void SetLevel(int level) { m_Level = level; }
private:
	int m_Level;
	std::shared_ptr<EngineCore::Sprite2D> m_Background;
	std::shared_ptr<MapController> m_MapController;
};