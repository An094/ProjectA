#pragma once
#include <cstdint>
#include <olc_Network.h>
enum class GameMsg : uint32_t
{
	Server_GetStatus,
	Server_GetPing,

	Client_Accepted,
	Client_AssignID,
	Client_RegisterWithServer,
	Client_UnregisterWithServer,

	Game_AddPlayer,
	Game_RemovePlayer,
	Game_UpdatePlayer
};

struct sPlayerDescription
{
	uint32_t nUniqueID = 0;
	uint32_t nScore = 0;
	float xPos = 0.0f;
	float yPos = 0.0f;
	uint32_t nDirection;
};