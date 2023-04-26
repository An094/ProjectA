#include "GSSetting.h"
#include "GLAD/glad.h"
#include "Manager/ResourceManager.h"
#include "Application.h"

extern GLint widthScreen;
extern GLint heightScreen;
bool isChangeMusic;
bool isChangeSound;


void GSSetting::Init()
{
	m_Backgroud = std::make_shared<EngineCore::Sprite2D>("bg_setting.tga");
	m_Backgroud->SetPosition(widthScreen / 2, heightScreen / 2);
	m_Backgroud->SetSize(widthScreen, heightScreen);

	m_BackButton = std::make_shared<EngineCore::Button>("back_play.tga", "Texture", "Texture", EngineCore::ButtonType::CIRCLE);
	m_BackButton->SetPosition(40, 60);
	m_BackButton->SetSize(50, 50);
	m_BackButton->SetOnClick([]()
		{
			EngineCore::GameStateMachine::GetInstance()->PopState();
		});

	m_SoundButton = std::make_shared<EngineCore::Button>("sound_on.tga");
	m_SoundButton->SetPosition(420, 385);
	m_SoundButton->SetSize(80, 80);
	m_SoundButton->SetOnClick([]()
		{
			isChangeSound = true;
		});
	SoundTurnOn = true;

	m_MusicButton = std::make_shared<EngineCore::Button>("sound_on.tga");
	m_MusicButton->SetPosition(420, 490);
	m_MusicButton->SetSize(80, 80);
	m_MusicButton->SetOnClick([]()
		{
			isChangeMusic = true;
		});
	MusicTurnOn = true;
}

void GSSetting::Update(float deltaTime)
{
	if (isChangeSound)
	{
		if (SoundTurnOn)
		{
			m_SoundButton->ChangeTexture(EngineCore::ResourceManager::GetInstance()->GetTexture("sound_off.tga"));
			SoundTurnOn = false;
		}
		else
		{
			m_SoundButton->ChangeTexture(EngineCore::ResourceManager::GetInstance()->GetTexture("sound_on.tga"));
			SoundTurnOn = true;
		}
		isChangeSound = false;
	}
	if (isChangeMusic)
	{
		if (MusicTurnOn)
		{
			m_MusicButton->ChangeTexture(EngineCore::ResourceManager::GetInstance()->GetTexture("sound_off.tga"));
			MusicTurnOn = false;
			EngineCore::Application::GetInstance()->TurnOffMusic();
			EngineCore::ResourceManager::GetInstance()->PauseSound("menu.mp3");
		}
		else
		{
			m_MusicButton->ChangeTexture(EngineCore::ResourceManager::GetInstance()->GetTexture("sound_on.tga"));
			MusicTurnOn = true;
			EngineCore::Application::GetInstance()->TurnOnMusic();
			EngineCore::ResourceManager::GetInstance()->PlaySound(EngineCore::AUDIO_TYPE::MUSIC, "menu.mp3", true);
		}
		isChangeMusic = false;
	}
}

void GSSetting::Draw()
{
	m_Backgroud->Draw();
	m_BackButton->Draw();
	m_MusicButton->Draw();
	m_SoundButton->Draw();
}

void GSSetting::HandleTouchEvents(int x, int y, bool isPressed)
{
	m_BackButton->HandleTouchEvent(x, y, isPressed);
	m_MusicButton->HandleTouchEvent(x, y, isPressed);
	m_SoundButton->HandleTouchEvent(x, y, isPressed);
}