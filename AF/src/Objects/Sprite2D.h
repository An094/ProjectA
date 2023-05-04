#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum class YAxisPlace
{
	Top = 0,
	Bottom
};

namespace EngineCore
{
	class Model;
	class Shader;
	class Texture;
	class Sprite2D
	{
	private:
		const glm::mat4 identifyMatrix = glm::mat4(1.0f);

		std::shared_ptr<Model> m_Model;
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<Texture> m_Texture;

		glm::vec2 m_Position;
		glm::mat4 m_TransMatrix;
		glm::mat4 m_RotateMatrix;
		glm::mat4 m_ScaleMatrix;
		int m_Width, m_Height;

	public:
		//Default model and texture of Sprite2D is Texture
		Sprite2D(const std::string&, const std::string& model = "Texture", const std::string& shader = "Texture");
		~Sprite2D();
		//Getter
		inline std::shared_ptr<Texture> GetTexture() { return m_Texture; }
		inline std::shared_ptr<Model> GetModel() { return m_Model; }
		inline std::shared_ptr<Shader> GetShader() { return m_Shader; }

		inline glm::mat4 GetTransMatrix() { return m_TransMatrix; }
		inline glm::mat4 GetRotateMatrix() { return m_RotateMatrix; }
		inline glm::mat4 GetScaleMatrix() { return m_ScaleMatrix; }

		glm::vec2 GetPosition();

		inline void GetSize(int& width, int& height) {
			width = m_Width;
			height = m_Height;
		}

		//Setter
		void SetPosition(float xpos, float ypos, YAxisPlace yAxisPlace = YAxisPlace::Top);
		void SetPosition(glm::vec2, YAxisPlace yAxisPlace = YAxisPlace::Top);

		void SetSize(int width, int height);

		void ChangeTexture(const std::string& newTexture);
		void ChangeTexture(std::shared_ptr<Texture> newTexture);

		void Init();
		virtual void Draw();
		virtual void Update(float deltaTime){}
		bool isMoveWithCam;
	};

}
