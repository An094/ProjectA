#include "Window.h"
#include "Application.h"

extern GLint widthScreen;
extern GLint heightScreen;

namespace EngineCore
{

	void window_resize(GLFWwindow* window, int width, int height);
	Window::Window(GLint width, GLint height, std::string name)
		: m_width(width), m_height(height), m_name(name)
	{
		m_window = NULL;
		Init();
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	void Window::Init()
	{
		// Initialize GLFW
		glfwInit();

		// Tell GLFW what version of OpenGL we are using 
		// In this case we are using OpenGL 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		// Tell GLFW we are using the CORE profile
		// So that means we only have the modern functions
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



		// Create a GLFWwindow object of m_width by m_height pixels
		m_window = glfwCreateWindow(m_width, m_height, m_name.c_str(), NULL, NULL);
		// Error check if the window fails to create
		if (m_window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return;
		}
		// Introduce the window into the current context
		glfwMakeContextCurrent(m_window);

		//Register callback function
		glfwSetWindowUserPointer(m_window, this);
		glfwSetWindowSizeCallback(m_window, window_resize);
		glfwSetKeyCallback(m_window, key_callback);
		glfwSetMouseButtonCallback(m_window, mouse_button_callback);
		glfwSetCursorPosCallback(m_window, cursor_position_callback);

		//Load GLAD so it configures OpenGL
		gladLoadGL();
		// Specify the viewport of OpenGL in the Window
		// In this case the viewport goes from x = 0, y = 0, to x = width, y = height
		glViewport(0, 0, m_width, m_height);



		// Specify the color of the background
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(m_window);

		Application::GetInstance()->Init();
	}

	void Window::Update(GLfloat deltaTime)
	{
		Application::GetInstance()->Update(deltaTime);

	}

	void Window::Draw()
	{
		//Todo
		Application::GetInstance()->Draw();
		return;
	}

	void Window::Clear()
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::Run()
	{
		GLfloat deltaTime = 0.0f;
		GLfloat lastTime = 0.0f;
		GLfloat currentTime = 0.0f;
		// Main while loop
		while (!glfwWindowShouldClose(m_window))
		{
			currentTime = (float)glfwGetTime();
			deltaTime = currentTime - lastTime;
			lastTime = currentTime;

			Clear();
			Update(deltaTime);
			Draw();

			glfwPollEvents();
			// Swap the back buffer with the front buffer
			glfwSwapBuffers(m_window);
		}

		// Delete window before ending the program
		glfwDestroyWindow(m_window);
		// Terminate GLFW before ending the program
		glfwTerminate();
	}

	void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->HandleKeyEvent(key, action == GLFW_RELEASE ? false : true);
	}

	void Window::HandleKeyEvent(int key, bool isPressed)
	{
		Application::GetInstance()->HandleKeyEvent(key, isPressed);
	}

	void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		if (button == 0)
		{
			win->HandleTouchEvent(win->mx, win->my, action == GLFW_PRESS ? true : false);
		}
	}

	void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->mx = xpos;
		win->my = ypos;
	}

	void Window::HandleTouchEvent(double xpos, double ypos, bool isPressed)
	{
		if (!isPressed)
		{
			//Origin of OpenGL is Top Left corner
			Application::GetInstance()->HandleTouchEvent(xpos, ypos, isPressed);
		}
	}

	void window_resize(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}