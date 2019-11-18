#include "CircleState.h"
#include "SquareState.h"
#include "RayState.h"

CircleState::CircleState() : circle(sf::Vector2f(-100, -100),50)
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

int CircleState::colideWithAABB(c2AABB& aabb)
{
	return c2CircletoAABB(circle.getC2Circle(),aabb);
}

int CircleState::colideWithCapsule(Capsule& cap)
{
	return c2CircletoCapsule(circle.getC2Circle(),cap.getC2Capsule());
}

int CircleState::colideWithPolygon(Polygon& pol)
{
	return c2CircletoPoly(circle.getC2Circle(),&(pol.getC2Poly()),NULL);
}

int CircleState::colideWithCircle(Circle& cir)
{
	return c2CircletoCircle(circle.getC2Circle(),cir.getC2Circle());
}

int CircleState::colideWithRay(Ray& ray)
{
	c2Raycast rayCast;
	c2Raycast* ptrRay = &rayCast;
	return c2RaytoCircle(ray.getC2Ray(),circle.getC2Circle(),ptrRay);
}
