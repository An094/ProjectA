#pragma once
#include <iostream>
#include <vector>
#include <stack>


namespace EngineCore
{
	class GameStateBase;
	class GameStateMachine
	{
	private:
		static std::shared_ptr<GameStateMachine> s_Instance;
		std::vector<std::shared_ptr<GameStateBase>> m_ListState;
		std::stack<std::shared_ptr<GameStateBase>> m_StackState;
		std::shared_ptr<GameStateBase> m_CurrentState;

	public:
		static std::shared_ptr<GameStateMachine> GetInstance();
		GameStateMachine();
		~GameStateMachine();
		//Add new state to list of state
		void AddState(std::shared_ptr<GameStateBase>);
		//push state to stack
		//void PushState(int index);
		void ChangeState(int index);
		bool IsValidState(int index);
		bool HasState();
		void PopState();

		inline std::shared_ptr<GameStateBase> GetCurrentState() const { return m_CurrentState; }
	};

}
