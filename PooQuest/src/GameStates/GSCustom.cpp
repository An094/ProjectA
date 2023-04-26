#include "GSCustom.h"
#include "GLAD/glad.h"
#include "Manager/GameStateMachine.h"
#include "Manager/ResourceManager.h"
#include "GSPlay.h"
#include "Application.h"
extern GLint widthScreen;
extern GLint heightScreen;
int avatar;
int level;
bool isChangeLevel;

void GSCustom::Init()
{
	level = 1;
	avatar = 0;
	isChangeLevel = false;

	m_Background = std::make_shared<EngineCore::Sprite2D>("background.tga");
	m_Background->SetPosition(widthScreen / 2, heightScreen / 2);
	m_Background->SetSize(widthScreen, heightScreen);

	m_BackButton = std::make_shared<EngineCore::Button>("back_play.tga", "Texture", "Texture", EngineCore::ButtonType::CIRCLE);
	m_BackButton->SetPosition(40, 60);
	m_BackButton->SetSize(50, 50);
	m_BackButton->SetOnClick([]()
		{
			EngineCore::GameStateMachine::GetInstance()->PopState();
		});

	std::shared_ptr<EngineCore::SpriteAnimation2D> tmp = std::make_shared<EngineCore::SpriteAnimation2D>("Poo/poo_down.tga", "Texture", "Animation", 6, 0.1f);
	tmp->SetPosition(widthScreen / 2, 150);
	tmp->SetSize(80, 80);
	m_ListPlayerAvatar.push_back(tmp);

	tmp = std::make_shared<EngineCore::SpriteAnimation2D>("Poo/poo3_down.tga", "Texture", "Animation", 6, 0.1f);
	tmp->SetPosition(widthScreen / 2, 150);
	tmp->SetSize(80, 80);
	m_ListPlayerAvatar.push_back(tmp);

	m_PlayerAvatar = m_ListPlayerAvatar[0];

	m_LeftPlayerAvatarButton = std::make_shared<EngineCore::Button>("Num/L.tga");
	m_LeftPlayerAvatarButton->SetPosition(200, 150);
	m_LeftPlayerAvatarButton->SetSize(50, 80);
	m_LeftPlayerAvatarButton->SetOnClick([]()
		{
			avatar = 1 - avatar;
		});

	m_RightPlayerAvatarButton = std::make_shared<EngineCore::Button>("Num/R.tga");
	m_RightPlayerAvatarButton->SetPosition(400, 150);
	m_RightPlayerAvatarButton->SetSize(50, 80);
	m_RightPlayerAvatarButton->SetOnClick([]()
		{
			avatar = 1 - avatar;
		});

	m_PlayButton = std::make_shared<EngineCore::Button>("Menu/Play.tga");
	m_PlayButton->SetPosition(widthScreen / 2, 700);
	m_PlayButton->SetSize(200, 100);
	m_PlayButton->SetOnClick([]()
		{
			bool condition = EngineCore::Application::GetInstance()->IsPlayMusic();
			if (condition)
			{
				EngineCore::ResourceManager::GetInstance()->PauseSound("menu.mp3");
				//EngineCore::ResourceManager::GetInstance()->PlaySound(EngineCore::AUDIO_TYPE::MUSIC, "music_game.wav", true);
				EngineCore::ResourceManager::GetInstance()->PlaySound(EngineCore::AUDIO_TYPE::MUSIC, "Fluffing-a-Duck.mp3", true);
			}
			EngineCore::GameStateMachine::GetInstance()->ChangeState(3);
		});

	m_LeftLevelButton = std::make_shared<EngineCore::Button>("Num/L.tga");
	m_LeftLevelButton->SetPosition(200, 300);
	m_LeftLevelButton->SetSize(50, 80);
	m_LeftLevelButton->SetOnClick([]()
		{
			if(level > 1) level--;
			isChangeLevel = true;
		});
	m_RightLevelButton = std::make_shared<EngineCore::Button>("Num/R.tga");
	m_RightLevelButton->SetPosition(400, 300);
	m_RightLevelButton->SetSize(50, 80);
	m_RightLevelButton->SetOnClick([]()
		{
			if(level <8) level++;
			isChangeLevel = true;
		});


	m_TensLevel = std::make_shared<EngineCore::Button>("Num/B0.tga");
	m_TensLevel->SetPosition(270, 300);
	m_TensLevel->SetSize(50, 80);

	m_UnitsLevel = std::make_shared<EngineCore::Button>("Num/B1.tga");
	m_UnitsLevel->SetPosition(330, 300);
	m_UnitsLevel->SetSize(50, 80);

	m_LevelSprite = std::make_shared<EngineCore::Sprite2D>("Level/level1.png");
	m_LevelSprite->SetPosition(widthScreen / 2, 500);
	m_LevelSprite->SetSize(360, 240);
}

void GSCustom::Update(float deltaTime)
{
	m_PlayerAvatar = m_ListPlayerAvatar[avatar];
	m_PlayerAvatar->Update(deltaTime);

	if (isChangeLevel)
	{
		int tens = level / 10;
		int units = level % 10;

		m_TensLevel->ChangeTexture(EngineCore::ResourceManager::GetInstance()->GetTexture("Num/B" + std::to_string(tens) + ".tga"));
		m_UnitsLevel->ChangeTexture(EngineCore::ResourceManager::GetInstance()->GetTexture("Num/B" + std::to_string(units) + ".tga"));
		m_LevelSprite->ChangeTexture(EngineCore::ResourceManager::GetInstance()->GetTexture("Level/level" + std::to_string(level) + ".png"));
		isChangeLevel = false;
	}
	
}

void GSCustom::Draw()
{
	m_Background->Draw();
	m_PlayerAvatar->Draw();
	m_LeftPlayerAvatarButton->Draw();
	m_RightPlayerAvatarButton->Draw();
	m_PlayButton->Draw();
	m_BackButton->Draw();
	m_TensLevel->Draw();
	m_UnitsLevel->Draw();
	m_LeftLevelButton->Draw();
	m_RightLevelButton->Draw();
	m_LevelSprite->Draw();
}

void GSCustom::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	m_LeftPlayerAvatarButton->HandleTouchEvent(x, y, bIsPressed);
	m_RightPlayerAvatarButton->HandleTouchEvent(x, y, bIsPressed);
	m_PlayButton->HandleTouchEvent(x, y, bIsPressed);
	m_BackButton->HandleTouchEvent(x, y, bIsPressed);
	m_LeftLevelButton->HandleTouchEvent(x, y, bIsPressed);
	m_RightLevelButton->HandleTouchEvent(x, y, bIsPressed);
}

void GSCustom::HandleKeyEvents(int key, bool isPressed)
{

}