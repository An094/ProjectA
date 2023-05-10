#include "GSMainMenu.h"

void GSMainMenu::Init()
{
	m_background = std::make_shared<Sprite2D>("CatchFlies/Background.jpg");
	m_background->SetPosition(440, 232);
	m_background->SetSize(880, 464);

	m_playerButton = std::make_shared<Button>("CatchFlies/Play.tga");
	m_playerButton->SetPosition(200, 232);
	m_playerButton->SetSize(240, 80);
	m_playerButton->SetOnClick([]()
		{
			EngineCore::GameStateMachine::GetInstance()->ChangeState(1);
		});
}

void GSMainMenu::Update(float deltaTime)
{

}

void GSMainMenu::Draw()
{
	m_background->Draw();
	m_playerButton->Draw();
}

void GSMainMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	m_playerButton->HandleTouchEvent(x, y, bIsPressed);
}