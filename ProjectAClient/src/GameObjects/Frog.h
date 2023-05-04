#pragma once
#include "GameEngine.h"
#include "GameConfig.h"
class MapManager;
enum class FaceTo
{
	Left = 0,
	Right
};

class Frog
{
public:
	Frog(int, /*std::shared_ptr<MapManager>*/ MapManager*);
	~Frog() = default;

	void UpdateImage();
	void UpdatePosition();
	static inline std::shared_ptr<Sprite2D> m_sprites[2][2][2];
	static void InitializeSprites();

	void Draw();
	void Update(float);
	void Key_Down();
	void Key_Up();
	void Keyboard_Down(int key);
	void Keyboard_Up(int key);
public:
	void Jump();
private:
	//std::shared_ptr<MapManager> m_mapManager;
	MapManager* m_mapManager;
	std::shared_ptr<Sprite2D> m_sprite;
	static inline float Map_offset[2]{ -1.0f, 1.0f };
	static inline float Map_Base_Angle[2]{ 160.0f, 20.0f };

	float x, y, vx, vy;
	int Player;
	
	FaceTo dir;
	int Anim;
	int Prepare_stt;
	bool isJumping;
	bool isJumpPressed;
	float Angle;
	int Angle_Drt;
	int Score;
};