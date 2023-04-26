#pragma once
#include "DynamicObject.h"
enum class ENEMY_TYPE
{
	SOLDIER = 0,
	TRAP,
	THORN_CUBE
};
class Enemy : public DynamicObject
{
public:
	Enemy() : DynamicObject(){}
	Enemy(ENEMY_TYPE type, DIRECTION dir, float speed) : DynamicObject(dir, speed), m_Type(type), isActivate(true) {}
	virtual ~Enemy() = default;

	virtual void Update(float) = 0;
	virtual void Draw() = 0;
	void SetType(ENEMY_TYPE type) { m_Type = type; }
	ENEMY_TYPE GetType() { return m_Type; }
	bool IsActivate() { return isActivate; }
	void SetActivate(bool isA) { isActivate = isA; }
private:
	ENEMY_TYPE m_Type;
	bool isActivate;
};

