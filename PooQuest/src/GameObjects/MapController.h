#pragma once
#include <vector>
#include "Objects/Sprite2D.h"
#include "DynamicObject.h"
#include "Enemy.h"
#include "Player.h"
#include "Gold.h"
#include "Objects/Button.h"
#include "Objects/OrthographicCamera.h"
#define TILEMAP_SIZE 48

typedef struct Point 
{
	int x, y;
};

typedef struct DynamicObjectData
{
	Point StartPoint, EndPoint;
	DIRECTION Direction;
};

typedef struct TileMap
{
	int ID;
	bool isWall;
	Point point;
	int width, height;
	int xPos, yPos;
	std::shared_ptr<EngineCore::Sprite2D> sprite;
};

class MapController
{
public:
	MapController(int level);
	~MapController();
	void DrawMap();
	void Update(float deltaTime);
	void Draw();
	void HandleKeyEvent(int key, bool isPressed);
	void HandleTouchEvents(int x, int y, bool isPressed);
	DynamicObjectData GetPlayerData();
	std::shared_ptr<Player> GetPlayer() { return m_Player; }
	bool CheckCollision(std::shared_ptr<DynamicObject> obj1, std::shared_ptr<DynamicObject> obj2);
	int CheckCollisionWithWall(std::shared_ptr<TileMap>& tileMap);
	void CheckCollectGold();
	bool WinGame();
	void ResetMap();
	bool isWinGame;
private:
	int m_Level;
	std::vector<std::shared_ptr<TileMap>> m_ListTileMap;
	DynamicObjectData m_PlayerData;
	std::shared_ptr<Player> m_Player;
	std::vector<std::shared_ptr<Enemy>> m_ListEnemies;
	std::vector<std::shared_ptr<Gold>> m_ListGolds;
	std::shared_ptr<EngineCore::OrthographicCamera> m_Camera;
	int m_KeyPressed;
	int** TileMapMatrix;
	int length, height;
	int remainingGold;
	std::shared_ptr<EngineCore::Sprite2D> m_Canvas;
	std::shared_ptr<EngineCore::Sprite2D> m_StageSprite;
	std::shared_ptr<EngineCore::Sprite2D> m_DeathSprite;
	std::shared_ptr<EngineCore::Sprite2D> m_D0;
	std::shared_ptr<EngineCore::Sprite2D> m_D1;
	std::shared_ptr<EngineCore::Sprite2D> m_S0;
	std::shared_ptr<EngineCore::Sprite2D> m_S1;
	std::shared_ptr<EngineCore::Button> m_BackButton;
	std::shared_ptr<EngineCore::Button> m_PauseButton;
	std::shared_ptr<EngineCore::Button> m_PlayButton;
	std::shared_ptr<EngineCore::Button> m_ButtonPausePlay;
	std::shared_ptr<EngineCore::Sprite2D> m_Switch;
	static int numberDeaths;
	int numberGolds;
	bool isInIntro;
	float timeStopSwitch;
	float timeDie;
};
