#pragma once
#include "Manager/GameStateBase.h"
#include "Manager/GameStateMachine.h"
#include "Objects/SpriteAnimation2D.h"
#include "Objects/Sprite2D.h"
#include "Objects/Button.h"
#include <vector>
class GSCustom : public EngineCore::GameStateBase
{
public:
	GSCustom() {};
	~GSCustom() {};
	void Init() override;
	void Update(float) override;
	void Draw() override;
	void Pause() override {};
	void Exit() override {};

	void HandleKeyEvents(int key, bool bIsPressed) override;
	void HandleTouchEvents(int x, int y, bool bIsPressed) override;
private:
	std::shared_ptr<EngineCore::Sprite2D> m_Background;
	std::shared_ptr<EngineCore::SpriteAnimation2D> m_PlayerAvatar;
	std::shared_ptr<EngineCore::Button> m_BackButton;
	std::shared_ptr<EngineCore::Button> m_LeftPlayerAvatarButton;
	std::shared_ptr<EngineCore::Button> m_RightPlayerAvatarButton;
	std::shared_ptr<EngineCore::Button> m_LeftLevelButton;
	std::shared_ptr<EngineCore::Button> m_RightLevelButton;
	std::shared_ptr<EngineCore::Sprite2D> m_TensLevel;
	std::shared_ptr<EngineCore::Sprite2D> m_UnitsLevel;
	std::shared_ptr<EngineCore::Sprite2D> m_LevelSprite;
	std::vector<std::shared_ptr<EngineCore::SpriteAnimation2D>> m_ListPlayerAvatar;
	std::shared_ptr<EngineCore::Button> m_PlayButton;
};

