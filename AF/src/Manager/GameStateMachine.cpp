#include "GameStateMachine.h"
#include "GameStateBase.h"

namespace EngineCore
{

	std::shared_ptr<GameStateMachine> GameStateMachine::s_Instance = nullptr;

	std::shared_ptr<GameStateMachine> GameStateMachine::GetInstance()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = std::make_shared<GameStateMachine>();
		}
		return s_Instance;
	}

	GameStateMachine::GameStateMachine()
	{

	}

	GameStateMachine::~GameStateMachine()
	{

	}

	void GameStateMachine::AddState(std::shared_ptr<GameStateBase> state)
	{
		m_ListState.push_back(state);
		//m_StackState.push(state);
	}

	bool GameStateMachine::IsValidState(int index)
	{
		return (m_ListState[index] != nullptr ? true : false);
	}

	void GameStateMachine::ChangeState(int index)
	{
		if (!IsValidState(index))
		{
			return;
		}
		if (HasState())
		{
			m_CurrentState->Pause();
		}
		m_CurrentState = m_ListState[index];
		m_CurrentState->Init();
		m_StackState.push(m_CurrentState);
	}

	bool GameStateMachine::HasState()
	{
		return !m_StackState.empty();
	}

	void GameStateMachine::PopState()
	{
		if (HasState())
		{
			m_StackState.pop();
			m_CurrentState = m_StackState.top();
		}
	}
}