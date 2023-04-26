#include "GSCredit.h"

extern GLint widthScreen;
extern GLint heightScreen;

void GSCredit::Init()
{
	m_Background = std::make_shared<EngineCore::Sprite2D>("bg_credit.tga");
	m_Background->SetPosition(widthScreen/2, heightScreen/2);
	m_Background->SetSize(widthScreen, heightScreen);

	m_BackButton = std::make_shared<EngineCore::Button>("back_play.tga", "Texture", "Texture", EngineCore::ButtonType::CIRCLE);
	m_BackButton->SetPosition(40, 60);
	m_BackButton->SetSize(50, 50);
	m_BackButton->SetOnClick([]()
		{
			EngineCore::GameStateMachine::GetInstance()->PopState();
		});

	m_Line1 = std::make_shared<EngineCore::Text>("arial.ttf", "Programmer", 30 , glm::vec3(1.0f, 0.0f, 1.0f));
	m_Line1->SetPosition(widthScreen / 2 - 85, 700);
	m_Line2 = std::make_shared<EngineCore::Text>("arial.ttf", "Ngo Thai An", 50, glm::vec3(1.0f, 0.0f, 1.0f));
	m_Line2->SetPosition(widthScreen / 2 - 150, 600);

	m_Line3 = std::make_shared<EngineCore::Text>("arial.ttf", "Instructor", 30, glm::vec3(1.0f, 0.0f, 1.0f));
	m_Line3->SetPosition(widthScreen / 2 - 85, 400);
	m_Line4 = std::make_shared<EngineCore::Text>("arial.ttf", "Do Cong Thuan", 50, glm::vec3(1.0f, 0.0f, 1.0f));
	m_Line4->SetPosition(widthScreen / 2 - 190, 300);
}

void GSCredit::Update(float deltaTime)
{

}

void GSCredit::Draw()
{
	m_Background->Draw();
	m_BackButton->Draw();
	m_Line1->Draw();
	m_Line2->Draw();
	m_Line3->Draw();
	m_Line4->Draw();
}

void GSCredit::HandleTouchEvents(int x, int y, bool isPressed)
{
	m_BackButton->HandleTouchEvent(x, y, isPressed);
}