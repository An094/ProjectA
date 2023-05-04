#include "Sprite2D.h"
#include "Manager/ResourceManager.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "Application.h"
#include "OrthographicCamera.h"
extern GLint widthScreen;
extern GLint heightScreen;

namespace EngineCore
{
	Sprite2D::Sprite2D(const std::string& textureName, const std::string& modelName, const std::string& shaderName)
	{
		m_Model = ResourceManager::GetInstance()->GetModel(modelName);
		m_Shader = ResourceManager::GetInstance()->GetShader(shaderName);
		m_Texture = ResourceManager::GetInstance()->GetTexture(textureName);
		m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
		m_TransMatrix = identifyMatrix;
		m_RotateMatrix = identifyMatrix;
		m_ScaleMatrix = identifyMatrix;
		isMoveWithCam = true;
	}

	Sprite2D::~Sprite2D()
	{

	}

	void Sprite2D::Init()
	{

	}

	void Sprite2D::Draw()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		std::shared_ptr<VAO> vao = m_Model->getVAO();
		std::shared_ptr<VBO> vbo = m_Model->getVBO();
		std::shared_ptr<EBO> ebo = m_Model->getEBO();
		vao->Bind();
		vbo->Bind();
		ebo->Bind();

		vao->LinkAttrib(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
		vao->LinkAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

		m_Texture->texUnit(m_Shader, "tex0", 0);
		m_Texture->Bind(0);

		glm::mat4 CameraMatrix;
		
		if (isMoveWithCam)
		{
			CameraMatrix = (Application::GetInstance()->GetCamera())->GetViewProjectionMatrix();
		}
		else
		{
			CameraMatrix = identifyMatrix;
		}
		
		m_Shader->SetMatrix4f("cam", CameraMatrix);
		m_Shader->SetMatrix4f("trans", m_TransMatrix);
		m_Shader->SetMatrix4f("rotate", m_RotateMatrix);
		m_Shader->SetMatrix4f("scale", m_ScaleMatrix);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		vao->Unbind();
		vbo->Unbind();
		ebo->Unbind();
	}

	void Sprite2D::SetPosition(float xpos, float ypos, YAxisPlace yAxisPlace)
	{
		////[temp]
		if (yAxisPlace == YAxisPlace::Bottom)
		{
			ypos = heightScreen - ypos;
		}
		m_Position = glm::vec2(xpos, ypos);
		glm::vec2 temp;
		temp.x = (xpos - widthScreen * 0.5f) * 2.0f / widthScreen;
		temp.y = (heightScreen - ypos - heightScreen * 0.5f) * 2.0f / heightScreen;
		m_TransMatrix = glm::translate(identifyMatrix, glm::vec3(temp.x, temp.y, 0.0f));
	}

	void Sprite2D::SetPosition(glm::vec2 pos, YAxisPlace yAxisPlace)
	{
		////[temp]
		if (yAxisPlace == YAxisPlace::Bottom)
		{
			pos.y = heightScreen - pos.y;
		}
		m_Position = pos;
		glm::vec2 temp;
		temp.x = (pos.x - widthScreen * 0.5f) * 2.0f / widthScreen;
		temp.y = (heightScreen - pos.y - heightScreen * 0.5f) * 2.0f / heightScreen;
		m_TransMatrix = glm::translate(identifyMatrix, glm::vec3(temp.x, temp.y, 0.0f));
	}

	void Sprite2D::SetSize(int width, int height)
	{
		m_Width = width;
		m_Height = height;
		glm::vec2 temp;
		temp.x = width * 1.0f / widthScreen;
		temp.y = height * 1.0f / heightScreen;
		m_ScaleMatrix = glm::scale(identifyMatrix, glm::vec3(temp.x, temp.y, 0.0f));
	}

	glm::vec2 Sprite2D::GetPosition()
	{
		/*glm::mat4 CameraMatrix = (Application::GetInstance()->GetCamera())->GetViewProjectionMatrix();
		glm::vec4 temp;
		temp = CameraMatrix * glm::vec4(m_Position[0], m_Position[1], 0.0f, 1.0f);
		return temp;*/
		return m_Position;
	}

	void Sprite2D::ChangeTexture(const std::string& newTexture)
	{
		m_Texture = ResourceManager::GetInstance()->GetTexture(newTexture);
	}

	void Sprite2D::ChangeTexture(std::shared_ptr<Texture> newTexture)
	{
		m_Texture = newTexture;
	}

	void Sprite2D::Rotate(float angle)
	{
		m_RotateMatrix = glm::rotate(identifyMatrix, angle, glm::vec3(0.0f, 0.0f, 0.1f));
	}
}
