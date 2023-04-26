#include "Text.h"


#include "Manager/ResourceManager.h"

extern GLint widthScreen;
extern GLint heightScreen;
namespace EngineCore
{

	Text::Text(const std::string& fontFile, const std::string& content, int size, glm::vec3 color)
		:m_Content(content), m_Color(color), m_scale(1.0f)
	{
		// compile and setup the shader
		// ----------------------------
		m_Shader = ResourceManager::GetInstance()->GetShader("Text");
		m_Shader->Activate();
		glm::mat4 projection = glm::ortho(0.0f, (float)widthScreen, 0.0f, (float)heightScreen);
		glUniformMatrix4fv(glGetUniformLocation(m_Shader->ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// FreeType
		// --------
		FT_Library ft;
		// All functions return a value different than 0 whenever an error occurred
		if (FT_Init_FreeType(&ft))
		{
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
			return;
		}

		// find path to font
		std::string font_name = "../Data/Fonts/" + fontFile;
		if (font_name.empty())
		{
			std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
			return;
		}

		// load font as face
		if (FT_New_Face(ft, font_name.c_str(), 0, &m_face)) {
			std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
			return;
		}
		else {
			// set size to load glyphs as
			FT_Set_Pixel_Sizes(m_face, 0, size);

			// disable byte-alignment restriction
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			m_length = m_Content.size();

			for (int i = 0; i < m_length; i++)
			{
				// Load character glyph 
				if (FT_Load_Char(m_face, m_Content[i], FT_LOAD_RENDER))
				{
					std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
					continue;
				}
				// generate texture
				unsigned int texture;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					m_face->glyph->bitmap.width,
					m_face->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					m_face->glyph->bitmap.buffer
				);
				// set texture options
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				// now store character for later use
				Character character = {
					texture,
					glm::ivec2(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows),
					glm::ivec2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top),
					static_cast<unsigned int>(m_face->glyph->advance.x)
				};
				m_Characters.insert(std::pair<char, Character>(m_Content[i], character));
			}
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		// destroy FreeType once we're finished
		FT_Done_Face(m_face);
		FT_Done_FreeType(ft);


		// configure m_VAO/m_VBO for texture quads
		// -----------------------------------
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	Text::~Text()
	{

	}

	void Text::Init()
	{

	}

	void Text::RenderText(std::string text, float x, float y)
	{
		// activate corresponding render state	
		m_Shader->Activate();
		glUniform3f(glGetUniformLocation(m_Shader->ID, "textColor"), m_Color.x, m_Color.y, m_Color.z);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(m_VAO);

		// iterate through all characters
		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++)
		{
			Character ch = m_Characters[*c];

			float xpos = x + ch.Bearing.x * m_scale;
			float ypos = y - (ch.Size.y - ch.Bearing.y) * m_scale;

			float w = ch.Size.x * m_scale;
			float h = ch.Size.y * m_scale;
			// update m_VBO for each character
			float vertices[6][4] = {
				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos,     ypos,       0.0f, 1.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },

				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },
				{ xpos + w, ypos + h,   1.0f, 0.0f }
			};
			// render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			// update content of m_VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (ch.Advance >> 6) * m_scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Text::Draw()
	{
		RenderText(m_Content, m_Position.x, m_Position.y);
	}

	void Text::SetPosition(int xpos, int ypos)
	{
		m_Position = glm::vec2(xpos, ypos);
	}

	void Text::SetSize(int height)
	{
		m_scale = 1.0f * height / heightScreen;
	}
}