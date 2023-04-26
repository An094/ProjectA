#include "Button.h"
#include <glad/glad.h>

namespace EngineCore
{
	void Button::HandleTouchEvent(int xpos, int ypos, bool isPressed)
	{
		int width, height;
		GetSize(width, height);
		bool condition;
		if (m_Type == ButtonType::RECTANGLE)
		{
			bool firstCondition = xpos >= GetPosition()[0] - width * 0.5f && xpos <= GetPosition()[0] + width * 0.5f;
			bool secondCondition = ypos >= GetPosition()[1] - height * 0.5f && ypos <= GetPosition()[1] + height * 0.5f;
			condition = firstCondition && secondCondition;
		}
		else if (m_Type == ButtonType::CIRCLE)
		{
			condition = pow(GetPosition()[0] - xpos, 2) + pow(GetPosition()[1] - ypos, 2) <= pow(width * 0.5, 2);
		}
		if (condition && !isPressed)
		{
			Callback();
		}
	}

	void Button::SetOnClick(void (*callback)())
	{
		Callback = callback;
	}
}