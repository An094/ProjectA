#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"

namespace EngineCore
{

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void ResetMatrix();

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		void HandleKeyEvents(int key, bool isPressed);
		void Update(float deltaTime);

		void MoveUp(float);
		void MoveDown(float);
		void MoveLeft(float);
		void MoveRight(float);

		bool CanMoveUp;
		bool CanMoveDown;
		bool CanMoveLeft;
		bool CanMoveRight;
		bool CanMove;
	private:
		void RecalculateViewMatrix();
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
		float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
		float m_CameraHorizontalTranslationSpeed = 0.5;
		float m_CameraVerticalTranslationSpeed = 0.25;
		int KEY;
	};
}