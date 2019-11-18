#include "SquareState.h"
#include "RayState.h"
#include "CircleState.h"

SquareState::SquareState() : shape(sf::Vector2f(70,70))
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
	shape.setFillColor(sf::Color::Green);
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

void SquareState::move(sf::Vector2i position)
{
	shape.setPosition(sf::Vector2f(position.x,position.y));
}

void SquareState::impact()
{
	shape.setFillColor(sf::Color::Red);
}

void SquareState::render(sf::RenderWindow& window)
{
	window.draw(shape);
	std::cout << "Square" << std::endl;
}
