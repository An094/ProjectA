#pragma once
#include "GameEngine.h"
#include "NetCommon.h"
class Fly
{
public:
	Fly(const sFlyDescription&);
	void Draw();
	void Update(float i_deltaTime);
	bool IsCaught(float i_x, float i_y);
	void UpdateDescription(const sFlyDescription&);
	sFlyDescription m_desc;
private:
	void UpdatePosition();
private:
	std::shared_ptr<SpriteAnimation2D> m_sprite;
};