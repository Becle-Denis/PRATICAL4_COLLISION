#include "CircleState.h"
#include "SquareState.h"
#include "RayState.h"

CircleState::CircleState() : circle(sf::Vector2f(0, 0),50)
{
}

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
	circle.setColor(sf::Color::Green);
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
	circle.setColor(sf::Color::Red);
}

void CircleState::move(sf::Vector2i newPosition)
{
	circle.move(newPosition);
}

void CircleState::render(sf::RenderWindow& window)
{
	std::cout << "Circle" << std::endl;
	circle.render(window);
}
