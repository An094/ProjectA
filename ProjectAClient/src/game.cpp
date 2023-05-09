#include "GameEngine.h"
#include "GameStates/GSGamePlay.h"

//TO DO: move global variable to another position
GLint widthScreen = 880;
GLint heightScreen = 464;

int main()
{
	GameStateMachine::GetInstance()->AddState(std::make_shared<GSGamePlay>());
	std::unique_ptr<Window> window = std::make_unique<Window>(widthScreen, heightScreen, "CatchFlies");
	window->Run();
	return 0;
}