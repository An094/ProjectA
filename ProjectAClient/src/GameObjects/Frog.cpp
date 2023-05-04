#include "Frog.h"
#include "MapManager.h"
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

Frog::Frog(int i_player, /*std::shared_ptr<MapManager> i_mapManager*/MapManager* i_mapManager)
	:m_mapManager(i_mapManager)
{
	Player = i_player;
	dir = static_cast<FaceTo>(1 - i_player);
	Anim = 0;// 0 - sit, 1 - jump
	float Offset = 11.0f * CELL_SIZE * (Player == 0 ? -1 : 1);
	x = WIDTH / 2 + Offset;
	y = 2 * CELL_SIZE;
	Prepare_stt = 0;
	isJumping = false;
	isJumpPressed = false;
	vx = vy = 0.0f;
	UpdateImage();
	UpdatePosition();
}

void Frog::UpdateImage()
{
	m_sprite = m_sprites[Player][static_cast<int>(dir)][Anim];
	//m_sprite->SetSize(54, 48);
}

void Frog::UpdatePosition()
{
	//m_sprites[Player][static_cast<int>(dir)][Anim]->Draw();
	m_sprite->SetPosition(x + 24, y + 24, YAxisPlace::Bottom);
}

void Frog::Draw()
{
	m_sprite->Draw();
}

void Frog::Update(float i_deltaTime)
{

	if (isJumping)
	{
		float y_old = y;
		x += vx;
		y += vy;
		vy += GRAVITY;
		if (vy < -24.0f)
		{
			vy = -24.0f;
		}
		if (vy <= 0.0f)
		{
			int col1 = (x - 9.0f) / CELL_SIZE;
			int col2 = (x + 9.0f) / CELL_SIZE;
			int row_old = (y_old) / CELL_SIZE;
			int row = (y) / CELL_SIZE;
			if (!m_mapManager->m_tileMatrix[row_old][col1]
				&& !m_mapManager->m_tileMatrix[row_old][col2]
				&& (m_mapManager->m_tileMatrix[row][col1] || m_mapManager->m_tileMatrix[row][col2]))
			{
				isJumping = false;
				y = (row + 1) * CELL_SIZE;
				vx = 0.0f;
				vy = 0.0f;
				Anim = 0;
				UpdateImage();
			}
		}
		UpdatePosition();
	}
}

void Frog::Jump()
{
	if (!isJumping)
	{
		isJumping = true;
		Anim = 1;
		UpdateImage();
	}
}

void Frog::Keyboard_Down(int key)
{
	switch (key)
	{
	case GLFW_KEY_BACKSPACE:
	{
		if (!Player)
		{

		}
		break;
	}
	case GLFW_KEY_KP_ENTER:
	{
		if (Player)
		{

		}
		break;
	}
	default:
		break;
	}
}

void Frog::Keyboard_Up(int key)
{

}

void Frog::Key_Down()
{
	isJumping = true;
}

void Frog::Key_Up()
{
	isJumping = false;
	vx = 10.0f;
	vy = 15.0f;
	Jump();
}