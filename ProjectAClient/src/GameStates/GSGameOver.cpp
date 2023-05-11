#include "GSGameOver.h"

void GSGameOver::UpdateResult(bool i_isWin)
{
	isWin = i_isWin;
	isUpdated = true;
}

void GSGameOver::Init()
{
	m_textures[0] = ResourceManager::GetInstance()->GetTexture("CatchFlies/pepe_angry.jpg");
	m_textures[1] = ResourceManager::GetInstance()->GetTexture("CatchFlies/pepe_happy.jpg");

	m_background = std::make_shared<Sprite2D>("CatchFlies/pepe_angry.jpg");
	m_background->SetPosition(440, 232);
	m_background->SetSize(880, 464);

	m_retryButton = std::make_shared<Button>("CatchFlies/retry.png");
	m_retryButton->SetPosition(670, 232, YAxisPlace::Bottom);
	m_retryButton->SetSize(240, 80);
	m_retryButton->SetOnClick([]() 
		{
			GameStateMachine::GetInstance()->ChangeState(1);
		});
}

void GSGameOver::Draw()
{
	m_background->Draw();
	m_retryButton->Draw();
}

void GSGameOver::Update(float i_deltaTime)
{
	if (isUpdated)
	{
		if (isWin)
		{
			m_background->ChangeTexture(m_textures[1]);
		}
		isUpdated = false;
	}
}

void GSGameOver::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	m_retryButton->HandleTouchEvent(x, y, bIsPressed);
}
