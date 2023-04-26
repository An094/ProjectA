#include "SpriteAnimation2D.h"
#include "Manager/ResourceManager.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "Application.h"
#include "OrthographicCamera.h"

namespace EngineCore
{

	SpriteAnimation2D::SpriteAnimation2D(const std::string& textureName, const std::string& modelName, const std::string& shaderName,
		int numberFrame, float frameTime)
		:Sprite2D(textureName, modelName, shaderName), m_NumberFrame(numberFrame), m_FrameTime(frameTime), m_CurrentFrame(0), m_CurrentTime(0.0f)
	{

	}

	void SpriteAnimation2D::Init()
	{

	}

	void SpriteAnimation2D::Draw()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		std::shared_ptr<VAO> vao = GetModel()->getVAO();
		std::shared_ptr<VBO> vbo = GetModel()->getVBO();
		std::shared_ptr<EBO> ebo = GetModel()->getEBO();
		vao->Bind();
		vbo->Bind();
		ebo->Bind();

		vao->LinkAttrib(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
		vao->LinkAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

		GetTexture()->texUnit(GetShader(), "tex0", 0);
		GetTexture()->Bind(0);

		GetShader()->SetMatrix4f("cam", (Application::GetInstance()->GetCamera())->GetViewProjectionMatrix());
		GetShader()->SetMatrix4f("trans", GetTransMatrix());
		GetShader()->SetMatrix4f("rotate", GetRotateMatrix());
		GetShader()->SetMatrix4f("scale", GetScaleMatrix());
		GetShader()->SetFloat("currentFrame", m_CurrentFrame);
		GetShader()->SetFloat("numberFrame", m_NumberFrame);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		vao->Unbind();
		vbo->Unbind();
		ebo->Unbind();
	}

	void SpriteAnimation2D::Update(float deltaTime)
	{
		m_CurrentTime += deltaTime;
		if (m_CurrentTime >= m_FrameTime)
		{
			m_CurrentFrame++;
			if (m_CurrentFrame >= m_NumberFrame)
				m_CurrentFrame = 0;
			m_CurrentTime -= m_FrameTime;
		}
	}
}