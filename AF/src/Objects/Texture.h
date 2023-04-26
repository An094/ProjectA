#pragma once

#include<glad/glad.h>
#include"Objects/stb_image.h"

#include"shaderClass.h"

namespace EngineCore
{
	class Texture
	{
	public:
		GLuint ID;
		GLenum type;
		Texture(const char* image);

		// Assigns a texture unit to a texture
		void texUnit(std::shared_ptr<Shader> shader, const char* uniform, GLuint unit);
		// Binds a texture
		void Bind(GLuint slot);
		// Unbinds a texture
		void Unbind();
		// Deletes a texture
		void Delete();
	};

}