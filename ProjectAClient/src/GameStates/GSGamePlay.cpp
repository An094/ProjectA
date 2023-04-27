#include "GSGamePlay.h"
#include "GameObjects/Platformer.h"
#include "GameObjects/Cloud.h"

void GSGamePlay::Init()
{

	//Background
	m_background = std::make_shared<Sprite2D>("CatchFlies/Background.tga");
	m_background->SetPosition(440, 192);
	m_background->SetSize(720, 384);


	m_platformers.reserve(6);
	m_clouds.reserve(2);
	m_borders.reserve(2);
	//30,16
	const int cellSize = 24;
	const int marginX = 80;
	const int marginY = 80;
	const int plfmPosition[12] = { 10, 4
							, 20, 4
							, 5 , 8
							, 25, 8
							, 8,  12
							, 22, 12 };

	const int clP[4] = { 5,4,22,6 };
	for (int i = 0; i < 6; i++)
	{
		std::shared_ptr<Platformer> platformer = std::make_shared<Platformer>("CatchFlies/Platformer.png", plfmPosition[2 * i] * cellSize + marginX, plfmPosition[2 * i + 1] * cellSize, 102, 24);
		m_platformers.push_back(std::move(platformer));
	}

	for (int i = 0; i < 2; i++)
	{
		std::shared_ptr<Cloud> cloud = std::make_shared<Cloud>("CatchFlies/Cloud.png", clP[2 + i] * cellSize + marginX, clP[2 * i + 1] * cellSize, 150, 36);
		m_clouds.push_back(std::move(cloud));
	}

	//Border
	
	std::shared_ptr<Sprite2D> Leftborder = std::make_shared<Sprite2D>("CatchFlies/Border.png");
	Leftborder->SetPosition(40, 192);
	Leftborder->SetSize(70, 384);
	
	std::shared_ptr<Sprite2D> Rightborder = std::make_shared<Sprite2D>("CatchFlies/Border.png");
	Rightborder->SetPosition(840, 192);
	Rightborder->SetSize(70, 384);

	std::shared_ptr<Sprite2D> Downborder = std::make_shared<Sprite2D>("CatchFlies/Border1.png");
	Downborder->SetPosition(440, 424);
	Downborder->SetSize(880, 70);
	m_borders.push_back(std::move(Leftborder));
	m_borders.push_back(std::move(Rightborder));
	m_borders.push_back(std::move(Downborder));
	
}

void GSGamePlay::Draw()
{
	m_background->Draw();
	for (auto it : m_clouds)
	{
		it->Render();
	}
	for (auto it : m_platformers)
	{
		it->Render();
	}
	for (auto it : m_borders)
	{
		it->Draw();
	}
}

void GSGamePlay::Update(float i_delta)
{
	for(auto it:m_clouds)
	{
		it->Update(i_delta);
	}
}
