#include "DynamicObject.h"

DynamicObject::DynamicObject(DIRECTION dir, int speed)
	:m_Dir(dir), m_Speed(speed), m_Sprite(nullptr), m_StartPoint({0,0})
{

}

void DynamicObject::SetSprite(const std::shared_ptr<EngineCore::Sprite2D>& sprite)
{
	m_Sprite = sprite;
}

std::shared_ptr<EngineCore::Sprite2D> DynamicObject::GetSprite()
{
	return m_Sprite;
}

void DynamicObject::SetCurrentTexture(std::shared_ptr<EngineCore::Texture> newTexture)
{
	m_Sprite->ChangeTexture(newTexture);
}

std::shared_ptr<EngineCore::Texture> DynamicObject::GetCurrentTexture()
{
	return m_Sprite->GetTexture();
}

void DynamicObject::SetStartPoint(TILEMAP_COOR coor)
{
	m_StartPoint = coor;
}

TILEMAP_COOR DynamicObject::GetStartPoint()
{
	return m_StartPoint;
}