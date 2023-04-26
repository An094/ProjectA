#include "GSIntro.h"


extern GLint widthScreen;
extern GLint heightScreen;

GSIntro::GSIntro()
{
	
}

GSIntro::~GSIntro()
{

}

void GSIntro::Init()
{
	m_Time = 0.0f;
	m_logo = std::make_shared<EngineCore::Sprite2D>("logo.tga");
	m_logo->SetPosition(widthScreen / 2, heightScreen / 2);
	m_logo->SetSize(150, 150);
}

void GSIntro::Update(float deltaTime)
{
	m_Time += deltaTime;
	if (m_Time >= 2.0f)
	{
		EngineCore::GameStateMachine::GetInstance()->ChangeState(1);
	}
}

void GSIntro::Draw()
{
	m_logo->Draw();
}

void GSIntro::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSIntro::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	
}

void GSIntro::Pause()
{

}

void GSIntro::Exit()
{

}