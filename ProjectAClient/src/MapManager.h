#pragma once
#include "GameEngine.h"
#include "GameConfig.h"
#include "GameObjects/Cloud.h"
#include "GameObjects/Platformer.h"

class MapManager
{
public:
	MapManager(const std::string&);

	void UpdateScene(float);
	void Render();

private:
	

private:
	std::string m_mapFileName;
	uint32_t m_numbHorizontalTile, m_numbVerticalTile;
	uint32_t* m_tileMatrix;
	std::vector<std::pair<uint32_t, uint32_t>> m_platformMapping;

	std::shared_ptr<Sprite2D> m_background;
	std::shared_ptr<Sprite2D> m_ground;
	std::vector<std::shared_ptr<Sprite2D>> m_borders;
	std::vector<std::shared_ptr<Cloud>> m_clouds;
	std::vector<std::shared_ptr<Platformer>> m_platformers;
};
