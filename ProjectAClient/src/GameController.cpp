#include "GameController.h"

GameController::GameController(const std::string& i_fileName)
{
	//Try to connect to localhost
	if (!Connect("127.0.0.1", 60000))
	{
		return;
	}
	const std::string mapPath = "../Data/Maps/" + i_fileName;
	std::fstream input(mapPath);
	if (input.fail())
	{
		CLIENT_ERROR("Opening Map file failed");
	}

	uint32_t index = 0, tmp, dataInFile[MAX_SIZE];
	while (input >> tmp)
	{
		dataInFile[index++] = tmp;
	}

	index = 0;

	m_numbHorizontalTile = dataInFile[index++];
	m_numbVerticalTile = dataInFile[index++];

	for (int i = 0; i < m_numbVerticalTile; ++i)
	{
		for (int j = 0; j < m_numbHorizontalTile; ++j)
		{
			m_tileMatrix[i][j] = 0;;
		}
	}
	uint32_t numberOfPlatformer = dataInFile[index++];

	m_platformMapping.reserve(numberOfPlatformer);

	for (int i = 0; i < numberOfPlatformer; ++i)
	{
		uint32_t first = dataInFile[index++];
		uint32_t second = dataInFile[index++];

		m_tileMatrix[first][second] = m_tileMatrix[first][second - 1] = m_tileMatrix[first][second + 1] = m_tileMatrix[first][second + 2] = 1;

		m_platformMapping.emplace_back(std::make_pair(first, second));
	}

	for (size_t i = 0; i < HEIGHT_OF_GROUND; ++i)
	{
		for (size_t j = 0; j < m_numbHorizontalTile; ++j)
		{
			m_tileMatrix[i][j] = 1;
		}
	}

	for (int i = 0; i < m_numbVerticalTile; ++i)
	{
		for (int j = 0; j < m_numbHorizontalTile; ++j)
		{
			std::cout << m_tileMatrix[i][j];
		}
		std::cout << std::endl;
	}

	//Background
	m_background = std::make_shared<Sprite2D>("CatchFlies/Background.png");
	m_background->SetPosition(360, 216, YAxisPlace::Bottom);
	m_background->SetSize(720, 336);
	//Ground
	m_ground = std::make_shared<Sprite2D>("CatchFlies/Ground.png");
	m_ground->SetPosition(360, 24, YAxisPlace::Bottom);
	m_ground->SetSize(720, 48);

	m_platformers.reserve(numberOfPlatformer);
	m_clouds.reserve(3);
	float cloudsPosition[6] = { 570.0f, 210.0f
	,930.0f, 300.0f
	,240.0f, 255.0f };
	m_borders.reserve(2);

	const int clP[4] = { 5,4,22,6 };
	for (size_t i = 0; i < numberOfPlatformer; i++)
	{
		std::shared_ptr<Platformer> platformer = std::make_shared<Platformer>("CatchFlies/Platformer.png", m_platformMapping[i].second * CELL_SIZE, m_platformMapping[i].first * CELL_SIZE, 102, 24);
		m_platformers.push_back(std::move(platformer));
	}

	for (int i = 0; i < 3; i++)
	{
		std::shared_ptr<Cloud> cloud = std::make_shared<Cloud>("CatchFlies/Cloud.png", cloudsPosition[2 * i], cloudsPosition[2 * i + 1], 150, 36);
		m_clouds.push_back(std::move(cloud));
	}


	Frog::InitializeSprites();
	m_frogs.reserve(2);
	for (int i = 0; i < 2; i++)
	{
		auto frog = std::make_shared<Frog>(i,this);
		m_frogs.push_back(std::move(frog));
	}
	
}


void GameController::UpdateScene(float i_delaTime)
{
	//Check for incoming network messages
	if (IsConnected())
	{
		while (!Incoming().empty())
		{
			auto msg = Incoming().pop_front().msg;

			switch (msg.header.id)
			{
			case(GameMsg::Client_Accepted):
			{
				std::cout << "Server accepted client - you're in!\n";
				olc::net::message<GameMsg> msg;
				msg.header.id = GameMsg::Client_RegisterWithServer;
				descPlayer.vPos = { 3.0f, 3.0f };
				msg << descPlayer;
				Send(msg);
				break;
			}

			case(GameMsg::Client_AssignID):
			{
				// Server is assigning us OUR id
				msg >> nPlayerID;
				std::cout << "Assigned Client ID = " << nPlayerID << "\n";
				break;
			}

			case(GameMsg::Game_AddPlayer):
			{
				sPlayerDescription desc;
				msg >> desc;
				mapObjects.insert_or_assign(desc.nUniqueID, desc);

				if (desc.nUniqueID == nPlayerID)
				{
					// Now we exist in game world
					bWaitingForConnection = false;
				}
				break;
			}

			case(GameMsg::Game_RemovePlayer):
			{
				uint32_t nRemovalID = 0;
				msg >> nRemovalID;
				mapObjects.erase(nRemovalID);
				break;
			}

			case(GameMsg::Game_UpdatePlayer):
			{
				sPlayerDescription desc;
				msg >> desc;
				mapObjects.insert_or_assign(desc.nUniqueID, desc);
				break;
			}


			}
		}
	}


	timerCount++;
	if (timerCount == 90)
	{
		timerCount = 0;
		if (m_flies.size() < MAX_FLIES)
		{
			bool check;
			int Region;
			do
			{
				check = false;
				Region = rand() % 6;
				for (auto fly : m_flies)
				{
					if (fly->Region == Region)
					{
						check = true;
						break;
					}
				}
			} while (check);
			m_flies.push_back(std::make_shared<Fly>(spawnPoints[Region].x, spawnPoints[Region].y, Region));
		}
	}


	for (auto it : m_clouds)
	{
		it->Update(i_delaTime);
	}
	for (auto it : m_frogs)
	{
		it->Update(i_delaTime);
	}
	for (auto it : m_flies)
	{
		it->Update(i_delaTime);
	}

	// Send player description
	olc::net::message<GameMsg> msg;
	msg.header.id = GameMsg::Game_UpdatePlayer;
	msg << mapObjects[nPlayerID];
	Send(msg);
}

void GameController::Render()
{
	m_background->Draw();
	m_ground->Draw();
	for (auto it : m_clouds)
	{
		it->Render();
	}
	for (auto it : m_platformers)
	{
		it->Render();
	}
	for (auto it : m_borders)
	{
		//it->Draw();
	}
	for (auto it : m_frogs)
	{
		it->Draw();
	}
	for (auto it : m_flies)
	{
		it->Draw();
	}
}

void GameController::Keyboard_Down(int i_key)
{
	switch (i_key)
	{
	case GLFW_KEY_SPACE:
	{
		m_frogs[0]->Key_Down();
		break;
	}
	case GLFW_KEY_ENTER:
	{
		m_frogs[1]->Key_Down();
		break;
	}
	default:
		break;
	}
}

void GameController::Keyboard_Up(int i_key)
{
	switch (i_key)
	{
	case GLFW_KEY_SPACE:
	{
		m_frogs[0]->Key_Up();
		break;
	}
	case GLFW_KEY_ENTER:
	{
		m_frogs[1]->Key_Up();
		break;
	}
	default:
		break;
	}
}