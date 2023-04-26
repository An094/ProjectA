#include "Gold.h"

Gold::Gold() :isActive(true)
{
	m_Sprite = std::make_shared<EngineCore::SpriteAnimation2D>("gold.tga", "Texture", "Animation", 8, 0.1f);
}

void Gold::SetPosition(int x, int y)
{
	m_Sprite->SetPosition(x, y);
}

glm::vec2 Gold::GetPosition()
{
	return m_Sprite->GetPosition();
}

void Gold::SetSize(int size)
{
	m_Sprite->SetSize(size, size);
}

void Gold::Draw()
{
	if(isActive) m_Sprite->Draw();
}

void Gold::Update(float deltaTime)
{
	if(isActive) m_Sprite->Update(deltaTime);
}

void Gold::Disable()
{
	isActive = false;
	//m_Sprite->ChangeTexture("blank.tga");
}