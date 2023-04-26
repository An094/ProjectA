#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

namespace EngineCore
{
	class Window
	{
	private:
		GLFWwindow* m_window;
		GLint m_width;
		GLint m_height;
		std::string m_name;
		double mx, my;
	public:
		Window(GLint, GLint, std::string);
		~Window();
		void Init();
		void Update(GLfloat deltaTime);
		void Draw();
		void Clear();
		void Run();

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void HandleKeyEvent(int key, bool isPressed);

		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

		void HandleTouchEvent(double xpos, double ypos, bool isPressed);
	};

}
