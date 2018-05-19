#include "StateMachine.hpp"

StateMachine::StateMachine
()
{
	for(auto& i: this->states)
		i = false;
}

bool StateMachine::isPressed(Keys k)
{
	return this->states[k];
}

void StateMachine::debug_print() const
{
	int32_t a = 0;
	for(auto& i: this->states)
		printf("%i %d\n", a, i);
}
