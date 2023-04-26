#pragma once
#include <iostream>
#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H  


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace EngineCore
{

	class Shader;

	struct Character {
		unsigned int TextureID; // ID handle of the glyph texture
		glm::ivec2   Size;      // Size of glyph
		glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
		unsigned int Advance;   // Horizontal offset to advance to next glyph
	};

	class Text
	{
	public:
		Text(const std::string& fontFile, const std::string& content, int size, glm::vec3 color);
		~Text();
		void Init();
		void Draw();
		void RenderText(std::string text, float x, float y);
		void SetPosition(int xpos, int ypos);
		void SetSize(int);
		inline glm::vec2 GetPosition() { return m_Position; }
	private:

		glm::vec2 m_Position;

		FT_Face m_face;
		std::shared_ptr<Shader> m_Shader;

		std::string m_Content;
		glm::vec3 m_Color;
		float m_scale;
		std::map<char, Character> m_Characters;
		GLuint m_VAO, m_VBO;

		int m_length;
	};

}
