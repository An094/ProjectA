#pragma once
#include "GameEngine.h"
#include "GameConfig.h"

using namespace std::placeholders;
class GameController;
enum class FaceTo
{
	Left = 0,
	Right
};

class Frog
{
public:
	Frog(int, /*std::shared_ptr<MapManager>*/ GameController*);
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
	void Prepare_Start();
	void Prepare_End();

private:
	bool Check_Boundary_Left(float x) { return x < BOUNDARY_LEFT; }
	bool Check_Boundary_Right(float x) { return x > BOUNDARY_RIGHT; }
	typedef bool (Frog::* Check_Boundary)(float);
	Check_Boundary Check_Boundary_Pointer[2] = { &Frog::Check_Boundary_Left, &Frog::Check_Boundary_Right };

	bool Check_Angle_Left_Decrease(float i_angle) { return i_angle <= 110.0f; }
	bool Check_Angle_Left_Increase(float i_angle) { return i_angle >= 160.0f; }
	bool Check_Angle_Right_Decrease(float i_angle) { return i_angle <= 20.0f; }
	bool Check_Angle_Right_Increase(float i_angle) { return i_angle >= 70.0f; }
	typedef bool (Frog::* Check_Angle)(float);
	Check_Angle Check_Angle_Pointer[2][2] = { {&Frog::Check_Angle_Left_Decrease, &Frog::Check_Angle_Left_Increase}, {&Frog::Check_Angle_Right_Decrease, &Frog::Check_Angle_Right_Increase} };
private:
	//std::shared_ptr<MapManager> m_mapManager;
	GameController* m_controller;
	std::shared_ptr<Sprite2D> m_sprite;
	static inline float Map_offset[2]{ -1.0f, 1.0f };
	static inline float Map_Base_Angle[2]{ 160.0f, 20.0f };

	float x, y, vx, vy;
	int Player;
	
	//FaceTo dir;
	int dir;
	int Anim;
	int Prepare_stt;
	bool isJumping;
	bool isJumpPressed;
	float Angle;
	int Angle_Drt;
	int Score;


	class Line
	{
	public:
		Line(int i_player, float i_x, float i_y, float i_Angle)
		{
			m_player = i_player;
			m_x = i_x;
			m_y = i_y;
			m_angle = i_Angle;
			char textureFile[30];
			sprintf(textureFile, "CatchFlies/Line_%d.png", i_player);
			m_sprite = std::make_shared<Sprite2D>(textureFile);
			m_sprite->Rotate(i_Angle);
			m_sprite->SetPosition(i_x, i_y, YAxisPlace::Bottom);
			m_sprite->SetSize(24, 12);
		}

		void Draw()
		{
			m_sprite->Draw();
		}
	private:
		std::shared_ptr<Sprite2D> m_sprite;
		int m_player;
		float m_x, m_y, m_angle;
	};

	std::vector<Line> m_lines;
};