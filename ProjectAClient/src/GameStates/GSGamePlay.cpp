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
