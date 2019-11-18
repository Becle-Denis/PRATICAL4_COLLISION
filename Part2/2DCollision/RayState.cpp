#include "RayState.h"
#include "CircleState.h"
#include "SquareState.h"

void RayState::handleInput(Input in, PlayerFSM* a)
{
	if (in.getCurrent() == Input::LEFT)
	{
		square(a);
	}
	else if (in.getCurrent() == Input::RIGHT)
	{
		cirle(a);
	}
}

void RayState::update(PlayerFSM* a)
{
}

void RayState::cirle(PlayerFSM* a)
{
	delete a->getPrevious();
	a->setPrevious(this);
	a->setCurrent(new CircleState());
}

void RayState::square(PlayerFSM* a)
{
	delete a->getPrevious();
	a->setPrevious(this);
	a->setCurrent(new SquareState());
}

void RayState::impact()
{
}

void RayState::render(sf::RenderWindow& window)
{
	std::cout << "Ray" << std::endl;
}
