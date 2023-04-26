#include"OrthographicCamera.h"

namespace EngineCore
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(glm::mat4(1.0f)), KEY(0)
		, CanMoveUp(true), CanMoveRight(true), CanMoveLeft(true), CanMoveDown(true)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::ResetMatrix()
	{
		m_ViewMatrix = glm::mat4(1.0f);
		m_Position = { 0.0f, 0.0f, 0.0f };
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::MoveUp(float deltaTime)
	{
		glm::vec3 m_CameraPosition = GetPosition();
		m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraHorizontalTranslationSpeed * deltaTime;
		m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraVerticalTranslationSpeed * deltaTime;
		SetPosition(m_CameraPosition);
	}

	void OrthographicCamera::MoveDown(float deltaTime)
	{
		glm::vec3 m_CameraPosition = GetPosition();
		m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraHorizontalTranslationSpeed * deltaTime;
		m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraVerticalTranslationSpeed * deltaTime;
		SetPosition(m_CameraPosition);
	}

	void OrthographicCamera::MoveLeft(float deltaTime)
	{
		glm::vec3 m_CameraPosition = GetPosition();
		m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraHorizontalTranslationSpeed * deltaTime;
		m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraVerticalTranslationSpeed * deltaTime;
		SetPosition(m_CameraPosition);
	}

	void OrthographicCamera::MoveRight(float deltaTime)
	{
		glm::vec3 m_CameraPosition = GetPosition();
		m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraHorizontalTranslationSpeed * deltaTime;
		m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraVerticalTranslationSpeed * deltaTime;
		SetPosition(m_CameraPosition);
	}

	void OrthographicCamera::HandleKeyEvents(int key, bool isPress)
	{
		if (isPress)
		{
			KEY = key;
		}
		else
		{
			KEY = 0;
		}

	}

	void OrthographicCamera::Update(float deltaTime)
	{
		if (KEY == GLFW_KEY_W && CanMoveUp && CanMove)
		{
			MoveUp(deltaTime);
		}
		else if (KEY == GLFW_KEY_D && CanMoveRight && CanMove)
		{
			MoveRight(deltaTime);
		}
		else if (KEY == GLFW_KEY_S && CanMoveDown && CanMove)
		{
			MoveDown(deltaTime);
		}
		else if (KEY == GLFW_KEY_A && CanMoveLeft && CanMove)
		{
			MoveLeft(deltaTime);
		}

	}
}