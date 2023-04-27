#pragma once
#include "Manager/GameStateBase.h"
#include "Manager/GameStateMachine.h"
#include "Objects/Sprite2D.h"
#include "Objects/Button.h"
#include "Manager/ResourceManager.h"

using namespace EngineCore;

class Platformer;
class Cloud;

class GSGamePlay : public EngineCore::GameStateBase
{
public:
	GSGamePlay() = default;
	~GSGamePlay() = default;

	void Init() override;
	void Exit() override {};
	void Update(float deltaTime) override;
	void Draw() override;
	void Pause() override {};

	void HandleKeyEvents(int key, bool bIsPressed) override {};
	void HandleTouchEvents(int x, int y, bool bIsPressed) override {};

private:
	std::shared_ptr<Sprite2D> m_background;
	std::vector<std::shared_ptr<Sprite2D>> m_borders;
	std::vector<std::shared_ptr<Cloud>> m_clouds;
	std::vector<std::shared_ptr<Platformer>> m_platformers;
};