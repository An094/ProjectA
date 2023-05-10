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

		SetMaximumPlayerInARomm(m_maximumPlayerInARoom);
	}

	struct Room
	{
		Room()
		{
			currentTime = lastTime = std::chrono::system_clock::now();
		}
		uint32_t roomId = 0;
		std::chrono::system_clock::time_point lastTime, currentTime;
		int turn = 0;
		std::vector<uint32_t> playerId;
		const float countdownTime = 60.0f;
		std::vector<float> remainingTime{ countdownTime, countdownTime };
		std::unordered_map<uint32_t, sFrogDescription> m_frogRoster;
		std::vector<sFlyDescription> m_flyRoster;
	};

	std::unordered_map<uint32_t, std::shared_ptr<Room>> m_rooms;
	std::vector<uint32_t> m_vGarbageIDs;
	const uint32_t timeToSpawn = 1;
	const uint32_t m_maximumPlayersInRoom = 2;
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
			auto& room = m_rooms.at(client->GetRoomID());
			if (room->m_frogRoster.find(client->GetID()) == room->m_frogRoster.end())
			{
				// client never added to roster, so just let it disappear
			}
			else
			{
				auto& pd = room->m_frogRoster[client->GetID()];
				std::cout << "[UNGRACEFUL REMOVAL]:" + std::to_string(pd.nUniqueID) + "\n";
				room->m_frogRoster.erase(client->GetID());
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
			desc.nRoomID = client->GetRoomID();
			desc.nIndex = desc.nUniqueID % m_maximumPlayersInRoom;
			float Offset = 11.0f * CELL_SIZE * (desc.nIndex == 0 ? -1 : 1);
			desc.nX = WIDTH / 2 + Offset + MARGIN_SIZE;
			desc.nY = 2 * CELL_SIZE + MARGIN_SIZE;
			desc.nDrt = 1 - desc.nIndex;
			if (m_rooms.find(desc.nRoomID) == m_rooms.end())
			{
				m_rooms.insert_or_assign(desc.nRoomID, std::make_shared<Room>());
			}
			auto& room = m_rooms.at(desc.nRoomID);
			room->roomId = desc.nRoomID;
			room->m_frogRoster.insert_or_assign(desc.nUniqueID, desc);

			olc::net::message<GameMsg> msgSendID;
			msgSendID.header.id = GameMsg::Client_AssignID;
			msgSendID << desc.nUniqueID;
			MessageClient(client, msgSendID);

			olc::net::message<GameMsg> msgAddPlayer;
			msgAddPlayer.header.id = GameMsg::Game_AddPlayer;
			msgAddPlayer << desc;
			MessageRoom(msgAddPlayer, room->roomId);
			room->playerId.push_back(desc.nUniqueID);



			for (const auto& player : room->m_frogRoster)
			{
				olc::net::message<GameMsg> msgAddOtherPlayers;
				msgAddOtherPlayers.header.id = GameMsg::Game_AddPlayer;
				msgAddOtherPlayers << player.second;
				MessageClient(client, msgAddOtherPlayers);
			}

			if (room->playerId.size() == m_maximumPlayersInRoom)
			{
				olc::net::message<GameMsg> msgStartGame;
				msgStartGame.header.id = GameMsg::Game_StartGame;
				msgStartGame << room->playerId[0];
				MessageRoom(msgStartGame, room->roomId);
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
			MessageRoom(msg, client->GetRoomID(), client);
			break;
		}

		case GameMsg::Client_UpdateFly:
		{
			MessageRoom(msg, client->GetRoomID(), client);
			break;
		}

		case GameMsg::Client_CatchFly:
		{
			std::cout << "Client_CatchFly" << std::endl;
			uint32_t region, uniqueID;
			msg >> region >> uniqueID;
			std::cout << "region:" << region << "uniqueID" << uniqueID << std::endl;
			auto& room = m_rooms[client->GetRoomID()];
			room->m_flyRoster.erase(std::remove_if(
				room->m_flyRoster.begin(), room->m_flyRoster.end(),
				[region](const sFlyDescription& x) {
					return x.nRegion == region;
				}), room->m_flyRoster.end());
			room->m_frogRoster[uniqueID].nScore++;

			olc::net::message<GameMsg> msgCatchFly;
			msgCatchFly.header.id = GameMsg::Client_CatchFly;
			msgCatchFly << uniqueID;
			MessageRoom(msgCatchFly, client->GetRoomID());
			break;
		}


		case GameMsg::Client_Jump:
		{
			auto& room = m_rooms[client->GetRoomID()];
			room->turn++;
			std::cout << "Turn: " << room->turn;
			uint32_t index = room->turn % 2;
			olc::net::message<GameMsg> msgJump;
			msgJump.header.id = GameMsg::Client_Jump;
			msgJump << room->playerId[index];
			MessageRoom(msgJump, client->GetRoomID());
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
		for (auto& it : m_rooms)
		{
			it.second->currentTime = std::chrono::system_clock::now();
			//Spawn flies
			if ((it.second->currentTime - it.second->lastTime) >= std::chrono::seconds{ timeToSpawn })
			{
				it.second->lastTime = it.second->currentTime;
				if (it.second->m_flyRoster.size() < MAX_FLIES && it.second->m_frogRoster.size() == m_maximumPlayersInRoom)
				{
					bool check;
					int Region;
					do
					{
						check = false;
						Region = rand() % 6;
						for (auto fly : it.second->m_flyRoster)
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

					MessageRoom(msgSpawnFly, it.first);

					it.second->m_flyRoster.push_back(std::move(desc));

				}

			}
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