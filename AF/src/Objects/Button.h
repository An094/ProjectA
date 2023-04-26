#pragma once

#include "Sprite2D.h"

namespace EngineCore
{

	enum class ButtonType
	{
		RECTANGLE = 0,
		CIRCLE
	};

	class Button : public Sprite2D
	{
	public:
		Button(const std::string& textureName, const std::string& modelName = "Texture", const std::string& shaderName = "Texture", ButtonType type = ButtonType::RECTANGLE)
			: Sprite2D(textureName, modelName, shaderName), m_Type(type)
		{
			isMoveWithCam = false;
		}
		~Button() = default;
		void SetOnClick(void (*)());
		void HandleTouchEvent(int xpos, int ypos, bool isPressed);
	private:
		void (*Callback)();
		ButtonType m_Type;
	};

}
