#include "GameEngine.h"
#include "GameStates/GSGamePlay.h"
#include "GameStates/GSMainMenu.h"
#include "GameStates/GSGameOver.h"
//TO DO: move global variable to another position
GLint widthScreen = 880;
GLint heightScreen = 464;
char* address = nullptr;
int main(int argc, char* argv[])
{
	if (argc >= 2)
	{
		address = argv[1];
	}
	else
	{
		address = "127.0.0.1";
	}

	GameStateMachine::GetInstance()->AddState(std::make_shared<GSMainMenu>());
	GameStateMachine::GetInstance()->AddState(std::make_shared<GSGamePlay>());
	GameStateMachine::GetInstance()->AddState(std::make_shared<GSGameOver>());
	std::unique_ptr<Window> window = std::make_unique<Window>(widthScreen, heightScreen, "CatchFlies");
	window->Run();
	return 0;
}