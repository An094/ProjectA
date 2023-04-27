#include "Platformer.h"

using namespace EngineCore;

Platformer::Platformer(const std::string& i_textureFile)
	:Platformer(i_textureFile, 0, 0, 0, 0)
{
}

Platformer::Platformer(const std::string& i_textureFile, int i_xPos, int i_yPos, int i_width, int i_height)
	: m_textureFile(i_textureFile)
	, m_position(i_xPos, i_yPos)
	, m_width(i_width)
	, m_height(i_height)
{
	LoadResource();
}

Platformer::Platformer(const std::string& i_textureFile, glm::vec2 i_pos, int i_width, int i_height)
	: Platformer(i_textureFile, i_pos.x, i_pos.y, i_width, i_height)
{

}

void Platformer::LoadResource()
{
	m_sprite = std::make_shared<Sprite2D>(m_textureFile);
	m_sprite->SetPosition(m_position);
	m_sprite->SetSize(m_width, m_height);
}

void Platformer::SetPosition(int i_xPos, int i_yPos)
{
	m_position.x = i_xPos;
	m_position.y = i_xPos;
	m_sprite->SetPosition(i_xPos, i_xPos);
}

void Platformer::SetPosition(glm::vec2 i_position)
{
	SetPosition(i_position.x, i_position.y);
}

void Platformer::Render()
{
	m_sprite->Draw();
}

bool Platformer::IsCollision()
{
	return false;
}