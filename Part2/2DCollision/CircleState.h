#ifndef CIRCLESTATE_H
#define CIRCLESTATE_H

#include <State.h>
#include "Circle.h"

class CircleState : public State
{
	Circle circle;
public:
	CircleState();

	void handleInput(Input in, PlayerFSM* a) override;

	void update(PlayerFSM* a) override;

	void square(PlayerFSM* a) override;

	void ray(PlayerFSM* a) override;

	void impact() override;

	void move(sf::Vector2i newPosition) override;

	void render(sf::RenderWindow& window) override;

	int colideWithAABB(c2AABB& aabb) override;

	int colideWithCapsule(Capsule& cap) override;

	int colideWithPolygon(Polygon& pol) override;

	int colideWithCircle(Circle& cir) override;

	int colideWithRay(Ray& ray) override;
};

#endif // !CIRCLESTATE_H



