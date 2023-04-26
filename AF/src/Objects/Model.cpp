#include "Model.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Common.h"

namespace EngineCore
{
	Model::Model(const std::string& fileName)
	{
		std::string buffer = Common::get_file_contents(fileName.c_str());
		float vertices[20];
		GLuint indices[6];
		std::stringstream ss(buffer);
		std::string strtmp;
		std::getline(ss, strtmp, '\n');
		int rs = sscanf_s(strtmp.c_str(), "#Vertices");

		for (int i = 0; i < 4; i++)
		{
			std::getline(ss, strtmp, '\n');
			rs = sscanf_s(strtmp.c_str(), "%f, %f, %f, %f, %f",
				&vertices[5 * i], &vertices[5 * i + 1], &vertices[5 * i + 2], &vertices[5 * i + 3], &vertices[5 * i + 4]);
		}
		std::getline(ss, strtmp, '\n');
		rs = sscanf_s(strtmp.c_str(), "#Indices");
		for (int i = 0; i < 2; i++)
		{
			std::getline(ss, strtmp, '\n');
			rs = sscanf_s(strtmp.c_str(), "%d, %d, %d", &indices[3 * i], &indices[3 * i + 1], &indices[3 * i + 2]);
		}
		m_VAO = std::make_shared<VAO>();
		m_VBO = std::make_shared<VBO>(vertices, sizeof(vertices));
		m_EBO = std::make_shared<EBO>(indices, sizeof(indices));

		m_VAO->Unbind();
		m_VBO->Unbind();
		m_EBO->Unbind();
	}
}