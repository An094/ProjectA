#include "Cloud.h"

using namespace EngineCore;

Cloud::Cloud(const std::string& i_textureFile)
	:Cloud(i_textureFile, 0, 0, 0, 0)
{
}

Cloud::Cloud(const std::string& i_textureFile, int i_xPos, int i_yPos, int i_width, int i_height)
	: m_textureFile(i_textureFile)
	, m_position(i_xPos, i_yPos)
	, m_width(i_width)
	, m_height(i_height)
{
	LoadResource();
}

Cloud::Cloud(const std::string& i_textureFile, glm::vec2 i_pos, int i_width, int i_height)
	: Cloud(i_textureFile, i_pos.x, i_pos.y, i_width, i_height)
{

}

void Cloud::LoadResource()
{
	m_sprite = std::make_shared<Sprite2D>(m_textureFile);
	m_sprite->SetPosition(m_position);
	m_sprite->SetSize(m_width, m_height);
}

void Cloud::SetPosition(float i_xPos, float i_yPos)
{
	m_position.x = i_xPos;
	m_position.y = i_yPos;
	m_sprite->SetPosition(i_xPos, i_yPos);
}

void Cloud::SetPosition(glm::vec2 i_position)
{
	SetPosition(i_position.x, i_position.y);
}

void Cloud::Render()
{
	m_sprite->Draw();
}

void Cloud::Update(float i_deltaTime)
{
	if (m_position.x < -50.0f)
	{
		m_position.x = 1000.0f;
	}
	else
	{
		m_position.x -= 50.0f * i_deltaTime;
	}
	SetPosition(m_position);
}