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

struct sFrogDescription
{
	uint32_t nUniqueID = 0;
	uint32_t nIndex = 0;
	float nX = 0.0f;
	float nY = 0.0f;
	float nVx = 0.0f;
	float nVy = 0.0f;

	uint32_t nDrt = 0;
	uint32_t nAnim = 0;
	uint32_t nPrepare_stt = 0;
	bool nIsJumping = false;
	bool nIsJumpPressed = false;
	float nAngle = 0.0f;
	uint32_t nAngle_Drt = 0;
	uint32_t nScore = 0;
};