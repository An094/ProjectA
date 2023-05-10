#include "GameController.h"
#include <algorithm>
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
	m_background->SetPosition(360 + MARGIN_SIZE, 216 + MARGIN_SIZE, YAxisPlace::Bottom);
	m_background->SetSize(720, 336);
	//Ground
	m_ground = std::make_shared<Sprite2D>("CatchFlies/Ground.png");
	m_ground->SetPosition(360 + MARGIN_SIZE, 24 + MARGIN_SIZE, YAxisPlace::Bottom);
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
		std::shared_ptr<Platformer> platformer = std::make_shared<Platformer>("CatchFlies/Platformer.png", m_platformMapping[i].second * CELL_SIZE + MARGIN_SIZE, m_platformMapping[i].first * CELL_SIZE + MARGIN_SIZE, 102, 24);
		m_platformers.push_back(std::move(platformer));
	}

	for (int i = 0; i < 3; i++)
	{
		std::shared_ptr<Cloud> cloud = std::make_shared<Cloud>("CatchFlies/Cloud.png", cloudsPosition[2 * i] + MARGIN_SIZE, cloudsPosition[2 * i + 1] + MARGIN_SIZE, 150, 36);
		m_clouds.push_back(std::move(cloud));
	}

	std::shared_ptr<Sprite2D> Leftborder = std::make_shared<Sprite2D>("CatchFlies/Border.png");
	Leftborder->SetPosition(40, 192);
	Leftborder->SetSize(70, 384);

	std::shared_ptr<Sprite2D> Rightborder = std::make_shared<Sprite2D>("CatchFlies/Border.png");
	Rightborder->SetPosition(840, 192);
	Rightborder->SetSize(70, 384);

	std::shared_ptr<Sprite2D> Downborder = std::make_shared<Sprite2D>("CatchFlies/Border1.png");
	Downborder->SetPosition(440, 424);
	Downborder->SetSize(880, 70);
	m_borders.push_back(std::move(Leftborder));
	m_borders.push_back(std::move(Rightborder));
	m_borders.push_back(std::move(Downborder));

	Frog::InitializeSprites();

	m_hourglass = std::make_shared<SpriteAnimation2D>("CatchFlies/Hourglass.png", "Texture", "Animation", 5, 0.25f);
	//uint32_t offset = m_frogs[uniqueIDofThisTurn]->m_desc.nIndex == 0 ? -400 : 350;
	//m_hourglass->SetPosition(440 + offset, 40);
	m_hourglass->SetSize(28, 35);
	numbers.reserve(10);
	for (int i = 0; i < 10; i++)
	{
		char textureFile[30];
		sprintf(textureFile, "CatchFlies/Number_%d.png", i);
		auto tempTexture = ResourceManager::GetInstance()->GetTexture(textureFile);
		numbers.emplace_back(tempTexture);
	}
	time.reserve(4);
	time.emplace_back(std::make_shared<Sprite2D>("CatchFlies/Number_6.png"));
	time.emplace_back(std::make_shared<Sprite2D>("CatchFlies/Number_0.png"));
	time.emplace_back(std::make_shared<Sprite2D>("CatchFlies/Number_6.png"));
	time.emplace_back(std::make_shared<Sprite2D>("CatchFlies/Number_0.png"));
	time[0]->SetPosition(60, 40, YAxisPlace::Bottom);
	time[0]->SetSize(24, 28);
	time[1]->SetPosition(90, 40, YAxisPlace::Bottom);
	time[1]->SetSize(24, 28);
	time[2]->SetPosition(790, 40, YAxisPlace::Bottom);
	time[2]->SetSize(24, 28);
	time[3]->SetPosition(820, 40, YAxisPlace::Bottom);
	time[3]->SetSize(24, 28);
	
}


void GameController::UpdateScene(float i_deltaTime)
{
	////Check for incoming network messages
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
				sFrogDescription desc;
				msg >> desc;
				m_frogsDesciption.insert_or_assign(desc.nUniqueID, desc);

				auto frog = std::make_shared<Frog>(desc, this);
				m_frogs.insert_or_assign(desc.nUniqueID, std::move(frog));

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
				m_frogsDesciption.erase(nRemovalID);
				break;
			}

			case(GameMsg::Game_UpdatePlayer):
			{
				sFrogDescription desc;
				msg >> desc;
				m_frogsDesciption.insert_or_assign(desc.nUniqueID, desc);
				if (m_frogs.find(desc.nUniqueID) != m_frogs.end())
				{
					m_frogs[desc.nUniqueID]->UpdateDescription(desc);
				}
				else
				{
					auto frog = std::make_shared<Frog>(desc, this);
					m_frogs.insert_or_assign(desc.nUniqueID, std::move(frog));
				}
				break;
			}

			case (GameMsg::Game_StartGame):
			{
				msg >> uniqueIDofThisTurn;
				isStarted = true;
				break;
			}

			case(GameMsg::Server_SpawnFly):
			{
				sFlyDescription desc;
				msg >> desc;
				m_fliesDescription.push_back(desc);
				auto fly = std::make_shared<Fly>(desc);
				m_flies.push_back(std::move(fly));

				break;
			}

			case (GameMsg::Client_UpdateFly):
			{
				sFlyDescription desc;
				msg >> desc;
				for (auto& it : m_fliesDescription)
				{
					if (it.nRegion == desc.nRegion)
					{
						it = desc;
					}
				}

				for (auto& it : m_flies)
				{
					if (it->m_desc.nRegion == desc.nRegion)
					{
						it->UpdateDescription(desc);
					}
				}
				break;
			}

			case (GameMsg::Client_CatchFly):
			{
				uint32_t uniqueID;
				msg >> uniqueID;
				/*auto result = std::find_if(m_frogs.begin(), m_frogs.end(),
					[uniqueID](const std::shared_ptr<Frog>& i_frog)
					{
						i_frog->m_desc.nUniqueID = uniqueID;
					});

				if (result != m_frogs.end())
				{
					result->second->m_desc.nScore++;
				}*/
				//m_frogs[uniqueID]->m_desc.nScore++;
				m_frogsDesciption[uniqueID].nScore++;
				m_frogs[uniqueID]->m_score->score++;
				UpdateScoreSprite();
				break;
			}

			case (GameMsg::Client_Jump):
			{
				msg >> uniqueIDofThisTurn;
				break;
			}

			}
		}
	}

	if (bWaitingForConnection)
	{
		std::cout << "Waiting to Connect" << std::endl;
		return;
	}


	for (auto it : m_clouds)
	{
		it->Update(i_deltaTime);
	}
	for (auto it : m_frogs)
	{
		it.second->Update(i_deltaTime);
	}
	for (auto it : m_flies)
	{
		it->Update(i_deltaTime);
	}


	m_frogsDesciption[nPlayerID] = m_frogs[nPlayerID]->m_desc;
	for (auto& it : m_fliesDescription)
	{
		for (auto& itr : m_flies)
		{
			if (it.nRegion == itr->m_desc.nRegion)
			{
				it = itr->m_desc;
			}
		}
		olc::net::message<GameMsg> msg;
		msg.header.id = GameMsg::Client_UpdateFly;
		msg << it;
		Send(msg);

	}


	// Send player description
	olc::net::message<GameMsg> msg;
	msg.header.id = GameMsg::Game_UpdatePlayer;
	msg << m_frogsDesciption[nPlayerID];
	Send(msg);

	//Timer
	if (isStarted)
	{
		int index = m_frogs[uniqueIDofThisTurn]->m_desc.nIndex;
		int offset = index == 0 ? -410 : 410;
		m_hourglass->SetPosition(440 + offset, 40, YAxisPlace::Bottom);
		m_hourglass->Update(i_deltaTime);
		//if (uniqueIDofThisTurn == nPlayerID)
		{
			remainingTime[index] -= i_deltaTime;
			uint32_t tmp = remainingTime[index];
			uint32_t first = tmp / 10;
			uint32_t second = tmp % 10;
			time[index * 2]->ChangeTexture(numbers[first]);
			time[index * 2 + 1]->ChangeTexture(numbers[second]);
		}

	}
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
		it->Draw();
	}
	for (auto it : m_frogs)
	{
		it.second->Draw();
	}
	for (auto it : m_flies)
	{
		it->Draw();
	}
	m_hourglass->Draw();
	for (auto it : time)
	{
		it->Draw();
	}
}

void GameController::Keyboard_Down(int i_key)
{
	if (uniqueIDofThisTurn != nPlayerID)
	{
		return;
	}
	switch (i_key)
	{
	case GLFW_KEY_SPACE:
	{
		for (auto it : m_frogs)
		{
			if (it.second->m_desc.nUniqueID == nPlayerID)
			{
				it.second->Key_Down();
			}
		}
		break;
	}
	default:
		break;
	}
}

void GameController::Keyboard_Up(int i_key)
{
	if (uniqueIDofThisTurn != nPlayerID)
	{
		return;
	}
	switch (i_key)
	{
	case GLFW_KEY_SPACE:
	{
		for (auto it : m_frogs)
		{
			if (it.second->m_desc.nUniqueID == nPlayerID)
			{
				it.second->Key_Up();
			}
		}
		break;
	}
	default:
		break;
	}
}

void GameController::UpdateScoreSprite()
{
	for (auto& it : m_frogs)
	{
		it.second->m_score->UpdateSprite();
	}
}