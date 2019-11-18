#include "SquareState.h"
#include "RayState.h"
#include "CircleState.h"

SquareState::SquareState()
{
}

void SquareState::handleInput(Input in, PlayerFSM* a)
{
	if (in.getCurrent() == Input::LEFT)
	{
		cirle(a);
	}
	else if (in.getCurrent() == Input::RIGHT)
	{
		ray(a);
	}
}

void SquareState::update(PlayerFSM* a)
{
}


void SquareState::cirle(PlayerFSM* a)
{
	delete a->getPrevious();
	a->setPrevious(this);
	a->setCurrent(new CircleState());
}

void SquareState::ray(PlayerFSM* a)
{
	delete a->getPrevious();
	a->setPrevious(this);
	a->setCurrent(new RayState());
}

void SquareState::impact()
{
}

void SquareState::render(sf::RenderWindow& window)
{
	std::cout << "Square" << std::endl;
}
