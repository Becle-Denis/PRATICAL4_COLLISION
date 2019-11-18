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
	ray.render(window);
}

int RayState::colideWithAABB(c2AABB& aabb)
{
	c2Raycast rayCast;
	c2Raycast* ptrRay = &rayCast;
	return c2RaytoAABB(ray.getC2Ray(), aabb, ptrRay);
}

int RayState::colideWithCapsule(Capsule& cap)
{
	c2Raycast rayCast;
	c2Raycast* ptrRay = &rayCast;
	return c2RaytoCapsule(ray.getC2Ray(), cap.getC2Capsule(), ptrRay);
}

int RayState::colideWithPolygon(Polygon& pol)
{
	c2Raycast rayCast;
	c2Raycast* ptrRay = &rayCast;
	return 0;
}

int RayState::colideWithCircle(Circle& cir)
{
	c2Raycast rayCast;
	c2Raycast* ptrRay = &rayCast;
	return c2RaytoCircle(ray.getC2Ray(), cir.getC2Circle(), ptrRay);
}

int RayState::colideWithRay(Ray& ray)
{
	c2Raycast rayCast;
	c2Raycast* ptrRay = &rayCast;
	return 0;
}
