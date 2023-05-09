#include <iostream>
#include <unordered_map>

#include "NetCommon.h"
#include "GameConfig.h"

class GameServer : public olc::net::server_interface<GameMsg>
{
public:
	GameServer(uint16_t nPort) : olc::net::server_interface<GameMsg>(nPort)
	{
		// Providing a seed value
		srand((unsigned)time(NULL));
		currentTime = lastTime = std::chrono::system_clock::now();
	}

	std::chrono::system_clock::time_point lastTime, currentTime;
	const uint32_t m_playersInRoom = 2;
	const uint32_t timeToSpawn = 1;
	int turn = 0;
	std::vector<uint32_t> playerId;
	uint32_t lastJumpingPlayerId;

	std::unordered_map<uint32_t, sFrogDescription> m_frogRoster;
	//std::unordered_map<uint32_t, sFlyDescription> m_flyRoster;//first is channel Id;
	std::vector<sFlyDescription> m_flyRoster;//first is channel Id;
	std::vector<uint32_t> m_vGarbageIDs;
	std::vector<std::pair<float, float>> spawnPoints = { {100.0f,300.0f}, {620.0f, 300.0f}, {360.0f, 280.0f}, {360.0f, 130.0f}, {100.0f, 120.0f}, {620.0f, 120.0f} };
protected:
	bool OnClientConnect(std::shared_ptr<olc::net::connection<GameMsg>> client) override
	{
		// For now we will allow all 
		return true;
	}

	void OnClientValidated(std::shared_ptr<olc::net::connection<GameMsg>> client) override
	{
		// Client passed validation check, so send them a message informing
		// them they can continue to communicate
		olc::net::message<GameMsg> msg;
		msg.header.id = GameMsg::Client_Accepted;
		client->Send(msg);
	}

	void OnClientDisconnect(std::shared_ptr<olc::net::connection<GameMsg>> client) override
	{
		if (client)
		{
			if (m_frogRoster.find(client->GetID()) == m_frogRoster.end())
			{
				// client never added to roster, so just let it disappear
			}
			else
			{
				auto& pd = m_frogRoster[client->GetID()];
				std::cout << "[UNGRACEFUL REMOVAL]:" + std::to_string(pd.nUniqueID) + "\n";
				m_frogRoster.erase(client->GetID());
				m_vGarbageIDs.push_back(client->GetID());
			}
		}

	}

	void OnMessage(std::shared_ptr<olc::net::connection<GameMsg>> client, olc::net::message<GameMsg>& msg) override
	{
		if (!m_vGarbageIDs.empty())
		{
			for (auto pid : m_vGarbageIDs)
			{
				olc::net::message<GameMsg> m;
				m.header.id = GameMsg::Game_RemovePlayer;
				m << pid;
				std::cout << "Removing " << pid << "\n";
				MessageAllClients(m);
			}
			m_vGarbageIDs.clear();
		}



		switch (msg.header.id)
		{
		case GameMsg::Client_RegisterWithServer:
		{
			sFrogDescription desc;
			msg >> desc;
			desc.nUniqueID = client->GetID();

			desc.nIndex = desc.nUniqueID % 2 == 0 ? 0 : 1;
			float Offset = 11.0f * CELL_SIZE * (desc.nIndex == 0 ? -1 : 1);
			desc.nX = WIDTH / 2 + Offset + MARGIN_SIZE;
			desc.nY = 2 * CELL_SIZE + MARGIN_SIZE;
			desc.nDrt = 1 - desc.nIndex;
			m_frogRoster.insert_or_assign(desc.nUniqueID, desc);

			olc::net::message<GameMsg> msgSendID;
			msgSendID.header.id = GameMsg::Client_AssignID;
			msgSendID << desc.nUniqueID;
			MessageClient(client, msgSendID);

			olc::net::message<GameMsg> msgAddPlayer;
			msgAddPlayer.header.id = GameMsg::Game_AddPlayer;
			msgAddPlayer << desc;
			MessageAllClients(msgAddPlayer);
			playerId.push_back(desc.nUniqueID);



			for (const auto& player : m_frogRoster)
			{
				olc::net::message<GameMsg> msgAddOtherPlayers;
				msgAddOtherPlayers.header.id = GameMsg::Game_AddPlayer;
				msgAddOtherPlayers << player.second;
				MessageClient(client, msgAddOtherPlayers);
			}

			if (playerId.size() == m_playersInRoom)
			{
				lastJumpingPlayerId = playerId[0];
				olc::net::message<GameMsg> msgStartGame;
				msgStartGame.header.id = GameMsg::Game_StartGame;
				msgStartGame << playerId[0];
				MessageAllClients(msgStartGame);
			}

			break;
		}

		case GameMsg::Client_UnregisterWithServer:
		{
			break;
		}

		case GameMsg::Game_UpdatePlayer:
		{
			// Simply bounce update to everyone except incoming client
			MessageAllClients(msg, client);
			break;
		}

		case GameMsg::Client_UpdateFly:
		{
			MessageAllClients(msg, client);
			break;
		}

		case GameMsg::Client_CatchFly:
		{
			std::cout << "Client_CatchFly" << std::endl;
			uint32_t region, uniqueID;
			msg >> region >> uniqueID;
			std::cout << "region:" << region << "uniqueID" << uniqueID << std::endl;
			m_flyRoster.erase(std::remove_if(
				m_flyRoster.begin(), m_flyRoster.end(),
				[region](const sFlyDescription& x) {
					return x.nRegion == region;
				}), m_flyRoster.end());
			m_frogRoster[uniqueID].nScore++;

			olc::net::message<GameMsg> msgCatchFly;
			msgCatchFly.header.id = GameMsg::Client_CatchFly;
			msgCatchFly << uniqueID;
			MessageAllClients(msgCatchFly);
			break;
		}


		case GameMsg::Client_Jump:
		{
			turn++;
			std::cout << "Turn: " << turn;
			uint32_t index = turn % 2;
			olc::net::message<GameMsg> msgJump;
			msgJump.header.id = GameMsg::Client_Jump;
			msgJump << playerId[index];
			MessageAllClients(msgJump);
			break;
		}

		}

	}

public:
	void Update(size_t nMaxMessages = -1, bool bWait = false) override
	{
		//if (bWait) m_qMessagesIn.wait();

		// Process as many messages as you can up to the value
		// specified
		size_t nMessageCount = 0;
		while (nMessageCount < nMaxMessages && !m_qMessagesIn.empty())
		{
			// Grab the front message
			auto msg = m_qMessagesIn.pop_front();

			// Pass to message handler
			OnMessage(msg.remote, msg.msg);

			nMessageCount++;
		}
		currentTime = std::chrono::system_clock::now();
		bool spwaningCondition = (currentTime - lastTime) >= std::chrono::seconds{ timeToSpawn };
		//Spawn flies
		if (spwaningCondition && m_flyRoster.size() < MAX_FLIES && m_frogRoster.size() == m_playersInRoom)
		{
			bool check;
			int Region;
			do
			{
				check = false;
				Region = rand() % 6;
				for (auto fly : m_flyRoster)
				{
					if (fly.nRegion == Region)
					{
						check = true;
						break;
					}
				}
			} while (check);
			sFlyDescription desc;

			olc::net::message<GameMsg> msgSpawnFly;
			msgSpawnFly.header.id = GameMsg::Server_SpawnFly;


			desc.isAlive = false;
			desc.nRegion = Region;
			desc.nX = spawnPoints[Region].first + MARGIN_SIZE + rand() % 41 - 20;
			desc.nY = spawnPoints[Region].second + MARGIN_SIZE + rand() % 41 - 20;
			msgSpawnFly << desc;

			MessageAllClients(msgSpawnFly);

			m_flyRoster.push_back(std::move(desc));

		}
	}
};



int main()
{
	GameServer server(60000);
	server.Start();

	while (1)
	{
		server.Update(-1, true);
	}
	return 0;
}