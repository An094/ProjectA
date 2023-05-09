#include "Frog.h"
#include "GameController.h"
#include "Fly.h"
void Frog::InitializeSprites()
{
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			for (int k = 0; k < 2; ++k)
			{
				char textureFile[30];
				sprintf(textureFile, "CatchFlies/Frog_%d_%d_%d.png", i, j, k);
				m_sprites[i][j][k] = std::make_shared<Sprite2D>(textureFile);
				m_sprites[i][j][k]->SetSize(54, 48);
			}
		}
	}
}

Frog::Frog(const sFrogDescription& i_desc, GameController* i_controller)
	:m_controller(i_controller)
{

	m_desc = i_desc;

	UpdateImage();
	UpdatePosition();
	m_score = std::make_shared<Score>(m_desc.nIndex);
}


void Frog::UpdateImage()
{
	m_sprite = m_sprites[m_desc.nIndex][static_cast<int>(m_desc.nDrt)][m_desc.nAnim];
}

void Frog::UpdatePosition()
{
	m_sprite->SetPosition(m_desc.nX + CELL_SIZE, m_desc.nY + CELL_SIZE, YAxisPlace::Bottom);
}

void Frog::Draw()
{
	m_sprite->Draw();
	if (!m_lines.empty() && m_desc.nUniqueID == m_controller->GetPlayerID())
	{
		for (auto it : m_lines)
		{
			it->Draw();
		}
	}
	m_score->Draw();
}

void Frog::Update(float i_deltaTime)
{
	m_lines.clear();
	if (!m_desc.nIsJumping)
	{
		if (m_desc.nIsJumpPressed)
		{
			Prepare_Start();
		}
		else
		{
			Prepare_End();
		}
	}
	if (!m_desc.nIsJumping)
	{
		if (m_desc.nPrepare_stt > 0)
		{
			if (m_desc.nPrepare_stt == 2)
			{
				m_desc.nPrepare_stt = 0;
				Jump();
			}
			else
			{
				m_desc.nAngle += Map_offset[m_desc.nAngle_Drt];
				Check_Angle func = Check_Angle_Pointer[m_desc.nDrt][m_desc.nAngle_Drt];

				if ((this->*func)(m_desc.nAngle))
				{
					m_desc.nAngle_Drt = 1 - m_desc.nAngle_Drt;
				}

				float Angle2 = m_desc.nAngle / RAD;
				float x2 = m_desc.nX, y2 = m_desc.nY + 4.0f, vx2, vy2;
				vx2 =
					cos(Angle2) * 4 + (m_desc.nDrt == 0 ? Angle2 - PI : Angle2) * 9;
				vy2 = sin(Angle2) * 21;
				m_desc.nVx = vx2;
				m_desc.nVy = vy2;

				for (int i = 0; i < 18; i++) {
					x2 += vx2;
					y2 += vy2;
					if (i % 3 == 2) {
						Angle2 = atan2(vy2, vx2) * RAD;
						m_lines.push_back(std::make_shared<Line>(m_desc.nIndex, x2, y2, Angle2));
					}
     				vy2 += GRAVITY;
				}
			}
		}
	}
	else
	{
		float y_old = m_desc.nY;
		m_desc.nX += m_desc.nVx;
		m_desc.nY += m_desc.nVy;
		m_desc.nVy += GRAVITY;
		if (m_desc.nVy < -24.0f)
		{
			m_desc.nVy = -24.0f;
		}
		if (m_desc.nVy <= 0.0f)
		{
			int col1 = (m_desc.nX - MARGIN_SIZE- 9.0f) / CELL_SIZE;
			int col2 = (m_desc.nX - MARGIN_SIZE + 9.0f) / CELL_SIZE;
			int row_old = (y_old - MARGIN_SIZE) / CELL_SIZE;
			int row = ( m_desc.nY - MARGIN_SIZE )/ CELL_SIZE;
			if (!m_controller->m_tileMatrix[row_old][col1]
				&& !m_controller->m_tileMatrix[row_old][col2]
				&& (m_controller->m_tileMatrix[row][col1] || m_controller->m_tileMatrix[row][col2]))
			{
				m_desc.nIsJumping = false;
				m_desc.nY = (row + 1) * CELL_SIZE + MARGIN_SIZE;
				m_desc.nVx = 0.0f;
				m_desc.nVy = 0.0f;
				m_desc.nAnim = 0;
				UpdateImage();
			}
		}

		Check_Boundary func = Check_Boundary_Pointer[m_desc.nDrt];

		if ((this->*func)(m_desc.nX))
		{
			m_desc.nDrt = 1 - m_desc.nDrt;
			m_desc.nVx = -m_desc.nVx;
			UpdateImage();
		}

		std::vector<std::shared_ptr<Fly>>& flies = m_controller->GetFlies();
	
		auto condition = [&, this](const std::shared_ptr<Fly>& i_fly)
		{
			return i_fly->IsCaught(m_desc.nX, m_desc.nY);
		};
		auto result = std::find_if(flies.begin(), flies.end(), condition);
		if(result != flies.end())
		{
			std::cout << "IsCaught" << std::endl;
			int region = result->get()->m_desc.nRegion;
			if (m_desc.nUniqueID == m_controller->GetPlayerID())
			{
				olc::net::message<GameMsg> msg;
				msg.header.id = GameMsg::Client_CatchFly;
				msg << m_desc.nUniqueID << region;

				m_controller->Send(msg);
			}
			flies.erase(result);
		}


		UpdatePosition();
	}
}

void Frog::Jump()
{
	if (!m_desc.nIsJumping)
	{
		m_desc.nIsJumping = true;
		m_desc.nAnim = 1;
		UpdateImage();
	}
}


void Frog::Key_Down()
{
	m_desc.nIsJumpPressed = true;
}

void Frog::Key_Up()
{
	m_desc.nIsJumpPressed = false;

	Jump();
}

void Frog::Prepare_Start()
{
	if (m_desc.nPrepare_stt == 0)
	{
		m_desc.nPrepare_stt = 1;
		m_desc.nAngle_Drt = m_desc.nDrt;
		m_desc.nAngle = Map_Base_Angle[m_desc.nDrt];
	}
}

void Frog::Prepare_End()
{
	if (m_desc.nPrepare_stt == 1)
	{
		m_desc.nPrepare_stt = 2;
	}
}

void Frog::UpdateDescription(const sFrogDescription& i_desc)
{
	m_desc = i_desc;
}