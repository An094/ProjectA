#pragma once
#include <iostream>
namespace EngineCore
{
	class GameStateBase
	{
	public:
		GameStateBase() {}
		virtual ~GameStateBase() {}

		virtual void Init() = 0;
		virtual void Exit() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Draw() = 0;
		virtual void Pause() = 0;

		virtual void HandleKeyEvents(int key, bool bIsPressed) = 0;
		virtual void HandleTouchEvents(int x, int y, bool bIsPressed) = 0;
	};
}
