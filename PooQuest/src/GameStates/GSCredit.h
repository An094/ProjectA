#pragma once
#include "Manager/GameStateBase.h"
#include "Manager/GameStateMachine.h"
#include "Objects/SpriteAnimation2D.h"
#include "Objects/Sprite2D.h"
#include "Objects/Button.h"
#include "Objects/Text.h"
#include <vector>
class GSCredit : public EngineCore::GameStateBase
{
public:
	GSCredit() {};
	~GSCredit() {};
	void Init() override;
	void Update(float) override;
	void Draw() override;
	void Pause() override {};
	void Exit() override {};

	void HandleKeyEvents(int key, bool bIsPressed) override {};
	void HandleTouchEvents(int x, int y, bool bIsPressed) override;
private:
	std::shared_ptr<EngineCore::Sprite2D> m_Background;
	std::shared_ptr<EngineCore::Button> m_BackButton;
	std::shared_ptr<EngineCore::Text> m_Line1;
	std::shared_ptr<EngineCore::Text> m_Line2;
	std::shared_ptr<EngineCore::Text> m_Line3;
	std::shared_ptr<EngineCore::Text> m_Line4;
};

