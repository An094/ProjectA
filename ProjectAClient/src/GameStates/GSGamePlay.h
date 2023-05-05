#pragma once
#include "GameController.h"

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

	void HandleKeyEvents(int key, bool bIsPressed) override;
	void HandleTouchEvents(int x, int y, bool bIsPressed) override;

private:
	std::shared_ptr<GameController> m_controller;
	std::shared_ptr<Button> m_leftButton;
	std::shared_ptr<Button> m_rightButton;
};