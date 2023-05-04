#include "Fly.h"

Fly::Fly(float i_x, float i_y, int i_Region)
{
	x = i_x + rand() % 41 - 20;
	y = i_y + rand() % 41 - 20;

	vx = vx_Max;
	vy = 0.0f;

	ax = ax_Base;
	ay = ay_Base;

	Region = i_Region;
	isAlive = false;

	m_sprite = std::make_shared<SpriteAnimation2D>("CatchFlies/FlyAni.png", "Texture", "Animation", 2, 0.1f);
	//m_sprite = std::make_shared<SpriteAnimation2D>("gold.tga", "Texture", "Animation", 8, 0.1f);
	m_sprite->SetPosition(x, y);
	m_sprite->SetSize(30, 18);
}

void Fly::Draw()
{
	m_sprite->Draw();
}

void Fly::Update(float i_deltaTime)
{
	m_sprite->Update(i_deltaTime);

	x += vx;
	y += vy;
	vx += ax;
	vy += ay;

	if (vx >= vx_Max || vx <= -vx_Max)
		ax = vx < 0 ? ax_Base : -ax_Base;
	if (vy >= vy_Max || vy <= -vy_Max)
		ay = vy < 0 ? ay_Base : -ay_Base;

	UpdatePosition();
}

bool Fly::IsCaught(float i_x, float i_y)
{
	if (i_x - 20.0f < x && i_x + 20.0f > x && i_y - 6.0f < y && i_y + 34.0f > y)
	{
		return true;
	}
	return false;
}

void Fly::UpdatePosition()
{
	m_sprite->SetPosition(x, y);
}