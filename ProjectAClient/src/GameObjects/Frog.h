#pragma once
#include "GameEngine.h"
#include "GameConfig.h"
#include "NetCommon.h"

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
	Frog(const sFrogDescription&, /*std::shared_ptr<MapManager>*/ GameController*);
	~Frog() = default;
	void UpdateImage();
	void UpdatePosition();
	static inline std::shared_ptr<Sprite2D> m_sprites[2][2][2];
	static void InitializeSprites();

	void Draw();
	void Update(float);
	void UpdateDescription(const sFrogDescription&);
	void Key_Down();
	void Key_Up();
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
public:
	sFrogDescription m_desc;
private:
	GameController* m_controller;
	std::shared_ptr<Sprite2D> m_sprite;
	static inline float Map_offset[2]{ -1.0f, 1.0f };
	static inline float Map_Base_Angle[2]{ 160.0f, 20.0f };
	bool isLanding = false;
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
			sprintf(textureFile, "CatchFlies/circle_%d.png", i_player);
			m_sprite = std::make_shared<Sprite2D>(textureFile);
			m_sprite->Rotate(i_Angle);
			m_sprite->SetPosition(i_x, i_y, YAxisPlace::Bottom);
			m_sprite->SetSize(12, 6);
		}

		void Draw()
		{
			if (!this->Check_Boundary_Left(m_x) && !this->Check_Boundary_Right(m_x))
			{
				m_sprite->Draw();
			}
		}
	private:
		bool Check_Boundary_Left(float x) { return x < BOUNDARY_LEFT + MARGIN_SIZE; }
		bool Check_Boundary_Right(float x) { return x > BOUNDARY_RIGHT + MARGIN_SIZE; }
	private:
		std::shared_ptr<Sprite2D> m_sprite;
		int m_player;
		float m_x, m_y, m_angle;
	};
	std::vector<std::shared_ptr<Line>> m_lines;
public:
	struct Score
	{
		Score(uint32_t i_side)
		{
			side = i_side;
			m_sprites.reserve(10);
			for (int i = 0; i < 10; i++)
			{
				char textureFile[30];
				sprintf(textureFile, "CatchFlies/Number_%d.png", i);
				auto sprite = std::make_shared<Sprite2D>(textureFile);
				uint32_t xPos = 440 + 60 * (side == 0 ? -1 : 1);
				sprite->SetPosition(xPos, 40, YAxisPlace::Bottom);
				sprite->SetSize(36, 42);
				m_sprites.emplace_back(std::move(sprite));
			}
			m_currentSprite = m_sprites[0];
		}


		void Draw()
		{
			m_currentSprite->Draw();
		}

		void UpdateSprite()
		{
			m_currentSprite = m_sprites[score];
		}

		std::vector<std::shared_ptr<Sprite2D>> m_sprites;
		std::shared_ptr<Sprite2D> m_currentSprite;
		uint32_t score{};
		uint32_t side;
	};

	std::shared_ptr<Score> m_score;
};