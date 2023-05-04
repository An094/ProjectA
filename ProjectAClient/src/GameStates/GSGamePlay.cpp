#include "GSGamePlay.h"
#include "GameObjects/Platformer.h"
#include "GameObjects/Cloud.h"

void GSGamePlay::Init()
{
	m_mapManager = std::make_shared<MapManager>("CatchFlies.txt");
	
	
}

void GSGamePlay::Draw()
{
	m_mapManager->Render();
}

void GSGamePlay::Update(float i_delta)
{
	m_mapManager->UpdateScene(i_delta);
}

void GSGamePlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed)
	{
		m_mapManager->Keyboard_Down(key);
	}
	else
	{
		m_mapManager->Keyboard_Up(key);
	}
}
void GSGamePlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{}