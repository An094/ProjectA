#pragma once
#include <iostream>
#include <glad/glad.h>


namespace EngineCore
{
	class VAO;
	class VBO;
	class EBO;
	class Model
	{
	private:
		std::shared_ptr<VAO> m_VAO;
		std::shared_ptr<VBO> m_VBO;
		std::shared_ptr<EBO> m_EBO;
	public:
		Model() = delete;
		Model(const std::string& fileName);
		inline std::shared_ptr<VAO> getVAO() { return m_VAO; }
		inline std::shared_ptr<VBO> getVBO() { return m_VBO; }
		inline std::shared_ptr<EBO> getEBO() { return m_EBO; }
	};
}
