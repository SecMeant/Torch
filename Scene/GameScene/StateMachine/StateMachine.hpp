#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <utility>
#include <array>

#include "../../../utility/stdshared.hpp"

class StateMachine
{
public:
	enum Keys:int32_t
	{
		Right = 0,
		Left  = 1,
		Up    = 2,
		Down  = 3,
		Space = 4,
	};

	typedef std::array<bool, 5> stateMachineType;

private:
	stateMachineType states;

public:
	StateMachine();

	bool isPressed(Keys k);

	void updateState(const sf::Event &kev);

	void debug_print() const;
};

#endif // STATEMACHINE_H
