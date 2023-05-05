#include "GSGamePlay.h"
#include "GameObjects/Platformer.h"
#include "GameObjects/Cloud.h"

void GSGamePlay::Init()
{
	m_controller = std::make_shared<GameController>("CatchFlies.txt");
	
	
}

void GSGamePlay::Draw()
{
	m_controller->Render();
}

void GSGamePlay::Update(float i_delta)
{
	m_controller->UpdateScene(i_delta);
}

void GSGamePlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed)
	{
		m_controller->Keyboard_Down(key);
	}
	else
	{
		m_controller->Keyboard_Up(key);
	}
}
void GSGamePlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{}