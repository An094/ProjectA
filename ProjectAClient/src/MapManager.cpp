#include "MapManager.h"

MapManager::MapManager(const std::string& i_fileName)
{
	const std::string mapPath = "../Data/Maps/" + i_fileName;
	std::fstream input(mapPath);
	if (input.fail())
	{
		CLIENT_ERROR("Opening Map file failed");
	}

	uint32_t index = 0, tmp, dataInFile[MAX_SIZE];
	while (input >> tmp)
	{
		dataInFile[index++] = tmp;
	}

	index = 0;

	m_numbHorizontalTile = dataInFile[index++];
	m_numbVerticalTile = dataInFile[index++];
	m_tileMatrix = new uint32_t[m_numbHorizontalTile * m_numbVerticalTile];
	
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 30; ++j)
		{
			m_tileMatrix[i * 30 + j] = 0;
		}
	}
	uint32_t numberOfPlatformer = dataInFile[index++];

	m_platformMapping.reserve(numberOfPlatformer);

	for (int i = 0; i < numberOfPlatformer; ++i)
	{
		uint32_t first = dataInFile[index++];
		uint32_t second = dataInFile[index++];
	
		m_tileMatrix[first * m_numbHorizontalTile + second] = 1;
		m_tileMatrix[first * m_numbHorizontalTile + second - 1] = 1;
		m_tileMatrix[first * m_numbHorizontalTile + second + 1] = 1;
		m_tileMatrix[first * m_numbHorizontalTile + second + 2] = 1;

		m_platformMapping.emplace_back(std::make_pair(first, second));
	}

	for (size_t i = 0; i < HEIGHT_OF_GROUND; ++i)
	{
		for (size_t j = 0; j < m_numbHorizontalTile; ++j)
		{
			m_tileMatrix[(m_numbVerticalTile - i - 1) * m_numbHorizontalTile + j] = 1;
		}
	}

	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 30; ++j)
		{
			std::cout << m_tileMatrix[i * 30 + j];
		}
		std::cout << std::endl;
	}

	//Background
	m_background = std::make_shared<Sprite2D>("CatchFlies/Background.png");
	m_background->SetPosition(440, 168);
	m_background->SetSize(720, 336);
	//Ground
	m_ground = std::make_shared<Sprite2D>("CatchFlies/Ground.png");
	m_ground->SetPosition(440, 360);
	m_ground->SetSize(720, 48);

	m_platformers.reserve(numberOfPlatformer);
	m_clouds.reserve(2);
	m_borders.reserve(2);
	//30,16
	const int cellSize = 24;
	const int marginX = 80;
	const int marginY = 80;

	const int clP[4] = { 5,4,22,6 };
	for (size_t i = 0; i < numberOfPlatformer; i++)
	{
		std::shared_ptr<Platformer> platformer = std::make_shared<Platformer>("CatchFlies/Platformer.png", m_platformMapping[i].second * CELL_SIZE + MARGIN_SIZE, m_platformMapping[i].first * CELL_SIZE, 102, 24);
		m_platformers.push_back(std::move(platformer));
	}

	for (int i = 0; i < 2; i++)
	{
		std::shared_ptr<Cloud> cloud = std::make_shared<Cloud>("CatchFlies/Cloud.png", clP[2 + i] * CELL_SIZE + MARGIN_SIZE, clP[2 * i + 1] * CELL_SIZE, 150, 36);
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

void MapManager::UpdateScene(float i_delaTime)
{
	for (auto it : m_clouds)
	{
		it->Update(i_delaTime);
	}
}

void MapManager::Render()
{
	m_background->Draw();
	m_ground->Draw();
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