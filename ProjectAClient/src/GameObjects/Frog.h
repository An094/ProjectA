#include "GameEngine.h"

class Frog
{
	Frog();
	~Frog();

private:
	std::shared_ptr<Sprite2D> m_sprite;
	bool isJumping;
	float Angle;
	int Drt;
	int Score;
};