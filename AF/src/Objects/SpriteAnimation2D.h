#pragma once
#include "Sprite2D.h"

namespace EngineCore
{
	class SpriteAnimation2D : public Sprite2D
	{
	public:
		SpriteAnimation2D(const std::string&, const std::string&, const std::string&, int, float);
		~SpriteAnimation2D() = default;

		void Init();
		void Draw() override;
		void Update(float) override;
	private:
		int m_CurrentFrame;
		float m_CurrentTime;
		int m_NumberFrame;
		float m_FrameTime;
	};


}
