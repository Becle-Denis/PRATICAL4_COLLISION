#include "SquareState.h"
#include "RayState.h"
#include "CircleState.h"



SquareState::SquareState() : shape(sf::Vector2f(70,70))
{
	shape.setPosition(-100, -100);
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
	c2.min = c2V(position.x, position.y);
	c2.max = c2V(position.x + 70, position.y + 70);
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

int SquareState::colideWithAABB(c2AABB& aabb)
{
	return c2AABBtoAABB(c2,aabb);
}

int SquareState::colideWithCapsule(Capsule& cap)
{
	return c2AABBtoCapsule(c2,cap.getC2Capsule());
}

int SquareState::colideWithPolygon(Polygon& pol)
{
	return c2AABBtoPoly(c2,&pol.getC2Poly(),NULL);
}

int SquareState::colideWithCircle(Circle& cir)
{
	return c2CircletoAABB(cir.getC2Circle(),c2);
}

int SquareState::colideWithRay(Ray& ray)
{
	c2Raycast rayCast;
	c2Raycast* ptrRay = &rayCast;
	return c2RaytoAABB(ray.getC2Ray(), c2, ptrRay);
}
