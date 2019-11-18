#include "CircleState.h"
#include "SquareState.h"
#include "RayState.h"

void CircleState::handleInput(Input in, PlayerFSM* a)
{
	if (in.getCurrent() == Input::LEFT)
	{
		ray(a);
	}
	else if (in.getCurrent() == Input::RIGHT)
	{
		square(a);
	}
}

void CircleState::update(PlayerFSM* a)
{

}

void CircleState::square(PlayerFSM* a)
{
	delete a->getPrevious();
	a->setPrevious(this);
	a->setCurrent(new SquareState());
}

void CircleState::ray(PlayerFSM* a)
{
	delete a->getPrevious();
	a->setPrevious(this);
	a->setCurrent(new RayState());
}

void CircleState::impact()
{
}

void CircleState::render(sf::RenderWindow& window)
{
	std::cout << "Circle" << std::endl;
}
