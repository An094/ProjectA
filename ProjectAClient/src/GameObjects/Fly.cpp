#include "Fly.h"

Fly::Fly(const sFlyDescription& i_desc)
{
	m_desc = i_desc;
	m_sprite = std::make_shared<SpriteAnimation2D>("CatchFlies/FlyAni.png", "Texture", "Animation", 2, 0.1f);
	m_sprite->SetPosition(m_desc.nX, m_desc.nY);
	m_sprite->SetSize(30, 18);
}


void Fly::Draw()
{
	m_sprite->Draw();
}

void Fly::Update(float i_deltaTime)
{
	if (!m_desc.isAlive) {
		m_scale += 0.05f;
		if (m_scale >= 1.0f) {
			m_scale = 1.0f;
			m_desc.isAlive = true;
		}
	}
	m_sprite->Update(i_deltaTime);

	m_desc.nX += m_desc.nVx;
	m_desc.nY += m_desc.nVy;
	m_desc.nVx += m_desc.nAx;
	m_desc.nVy += m_desc.nVy;

	if (m_desc.nVx >= m_desc.nVxMax || m_desc.nVx <= -m_desc.nVxMax)
		m_desc.nAx = m_desc.nVx < 0 ? m_desc.nAxBase : -m_desc.nAxBase;
	if (m_desc.nVy >= m_desc .nVyMax || m_desc.nVy <= -m_desc.nVyMax)
		m_desc.nAy = m_desc.nVy < 0 ? m_desc.nAyBase : -m_desc.nAyBase;

	UpdatePosition();
}

void Fly::UpdateDescription(const sFlyDescription& i_desc)
{
	m_desc = i_desc;
	UpdatePosition();
}

bool Fly::IsCaught(float i_x, float i_y)
{
	if (i_x - 20.0f < m_desc.nX && i_x + 20.0f > m_desc.nX && i_y - 6.0f < m_desc.nY && i_y + 34.0f > m_desc.nY)
	{
		return true;
	}
	return false;
}

void Fly::UpdatePosition()
{
	m_sprite->SetPosition(m_desc.nX, m_desc.nY, YAxisPlace::Bottom);
}