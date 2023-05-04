#pragma once
#include "GameEngine.h"
class Fly
{
public:
	Fly(float _x, float _y, int _Region);

	void Draw();
	void Update(float i_deltaTime);
	bool IsCaught(float i_x, float i_y);

	int Region;
private:
	void UpdatePosition();
private:
	std::shared_ptr<SpriteAnimation2D> m_sprite;
	const float ax_Base = 0.015f;
	const float ay_Base = 0.02f;
	const float vx_Max = 0.3f;
	const float vy_Max = 0.8f;

	float x, y, vx, vy, ax, ay;
	bool isAlive;
};