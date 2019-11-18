#include "RayState.h"
#include "CircleState.h"
#include "SquareState.h"

RayState::RayState() : ray(sf::Vector2f(0,0),150,-20)
{
}

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
	ray.setColor(sf::Color::Green);
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
	ray.setColor(sf::Color::Red);
}

void RayState::move(sf::Vector2i position)
{
	ray.move(position);
}

void RayState::render(sf::RenderWindow& window)
{
	std::cout << "Ray" << std::endl;
	ray.render(window);
}
