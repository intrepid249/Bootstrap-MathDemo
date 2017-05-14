#pragma once
#include <vector>

class State;
class StateMachine {
public:
	StateMachine();
	~StateMachine();

	void addState(State* state);

protected:
	std::vector<State*> m_states;
};

