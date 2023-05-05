#pragma once
#include "GameEngine.h"
#include "GameConfig.h"
#include "GameObjects/Cloud.h"
#include "GameObjects/Platformer.h"
#include "GameObjects/Frog.h"
#include "GameObjects/Fly.h"
#include "NetCommon.h"
#include <unordered_map>

struct Point
{
	float x;
	float y;
};

class GameController : olc::net::client_interface<GameMsg>
{
public:
	GameController(const std::string&);

	void UpdateScene(float);
	void Render();
	uint32_t m_tileMatrix[16][30];
	void Keyboard_Down(int key);
	void Keyboard_Up(int key);

	std::vector<std::shared_ptr<Fly>>& GetFlies()
	{
		return m_flies;
	}
private:
	

private:
	std::string m_mapFileName;
	uint32_t m_numbHorizontalTile, m_numbVerticalTile;
	std::vector<std::pair<uint32_t, uint32_t>> m_platformMapping;

	std::vector<Point> spawnPoints = { {100.0f,300.0f}, {620.0f, 300.0f}, {360.0f, 280.0f}, {360.0f, 130.0f}, {100.0f, 120.0f}, {620.0f, 120.0f} };
	std::shared_ptr<Sprite2D> m_background;
	std::shared_ptr<Sprite2D> m_ground;
	std::vector<std::shared_ptr<Sprite2D>> m_borders;
	std::vector<std::shared_ptr<Cloud>> m_clouds;
	std::vector<std::shared_ptr<Platformer>> m_platformers;
	std::vector<std::shared_ptr<Frog>> m_frogs;
	std::vector<std::shared_ptr<Fly>> m_flies;
	uint32_t timerCount{};

	///networking
	std::unordered_map<uint32_t, sPlayerDescription> mapObjects;
	uint32_t nPlayerID = 0;
	sPlayerDescription descPlayer;

	bool bWaitingForConnection = true;

};