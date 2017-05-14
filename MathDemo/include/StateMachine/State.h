#pragma once
#include <string>

class State {
public:
	State();
	State(std::string name);
	virtual ~State();

	/** Perform actions upon entering this state*/
	virtual void doEntryActions() = 0;
	/** Perform this state's behaviour*/
	virtual void doActions() = 0;
	/** Perform actions upon leaving this state*/
	virtual void doExitActions() = 0;

protected:
	std::string m_name;
};

