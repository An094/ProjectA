#pragma once
#include <cstdint>
#include <olc_Network.h>
enum class GameMsg : uint32_t
{
	Server_GetStatus,
	Server_GetPing,
	Server_SpawnFly,

	Client_Accepted,
	Client_AssignID,
	Client_RegisterWithServer,
	Client_UnregisterWithServer,
	Client_UpdateFly,
	Client_CatchFly,
	Client_Jump,

	Game_AddPlayer,
	Game_StartGame,
	Game_RemovePlayer,
	Game_UpdatePlayer
};

struct sFrogDescription
{
	uint32_t nUniqueID = 0;
	uint32_t nRoomID = 0;
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

struct sFlyDescription
{
	float nAxBase = 0.015f;
	float nAyBase = 0.02f;
	float nVxMax = 0.3f;
	float nVyMax = 0.8f;

	float nX = 0.0f;
	float nY = 0.0f;
	float nVx = nVxMax;
	float nVy = 0.0f;
	float nAx = nAxBase;
	float nAy = nAyBase;
	bool isAlive = true;
	uint32_t nRegion;
};