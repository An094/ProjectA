#pragma once

#include "GameController.h"

using namespace EngineCore;
class GSMainMenu : public GameStateBase
{
public:
	GSMainMenu() = default;
	~GSMainMenu() = default;
	void Init() override;
	void Exit() override {};
	void Update(float deltaTime) override;
	void Draw() override;
	void Pause() override {};

	void HandleKeyEvents(int key, bool bIsPressed) override {};
	void HandleTouchEvents(int x, int y, bool bIsPressed) override;

private:
	std::shared_ptr<Sprite2D> m_background;
	std::shared_ptr<Button> m_playerButton;
};

