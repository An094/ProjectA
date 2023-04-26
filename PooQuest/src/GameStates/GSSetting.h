#pragma once
#include "Manager/GameStateBase.h"
#include "Manager/GameStateMachine.h"
#include "Objects/SpriteAnimation2D.h"
#include "Objects/Sprite2D.h"
#include "Objects/Button.h"
#include <vector>
class GSSetting : public EngineCore::GameStateBase
{
public:
	GSSetting() {};
	~GSSetting() {};
	void Init() override;
	void Update(float) override;
	void Draw() override;
	void Pause() override {};
	void Exit() override {};

	void HandleKeyEvents(int key, bool bIsPressed) override {};
	void HandleTouchEvents(int x, int y, bool bIsPressed) override;
private:
	std::shared_ptr<EngineCore::Sprite2D> m_Backgroud;
	std::shared_ptr<EngineCore::Button> m_BackButton;
	std::shared_ptr<EngineCore::Button> m_MusicButton;
	std::shared_ptr<EngineCore::Button> m_SoundButton;
	bool MusicTurnOn;
	bool SoundTurnOn;
};

