#pragma once
#include<iostream>
#include <glad/glad.h>

namespace EngineCore
{
	class Sprite2D;
	class SpriteAnimation2D;
	class Button;
	class OrthographicCamera;
	class Application
	{
	private:
		static std::shared_ptr<Application> s_Instance;
		std::shared_ptr<OrthographicCamera> m_Camera;
		float m_CurrentTime;
		int m_FpsCount;
		bool isPlayMusic;
		bool isPlaySound;
	public:
		static std::shared_ptr<Application> GetInstance()
		{
			if (s_Instance == nullptr)
				s_Instance = std::make_shared<Application>();
			return s_Instance;
		}
		Application();
		~Application();
		std::shared_ptr<OrthographicCamera> GetCamera();

		void Init();
		void Update(GLfloat deltaTime);
		void Draw();
		void HandleKeyEvent(int key, bool isPressed);
		void HandleTouchEvent(double xpos, double ypos, bool isPressed);
		void Exit();
		void TurnOnMusic() { isPlayMusic = true; }
		void TurnOffMusic() { isPlayMusic = false; }
		bool IsPlayMusic() { return isPlayMusic; }
	};
}